#include "MFW3D_InputMgr.h"
#include "Ogre.h"
#include "MFW3D_Input.h"

namespace MFW3D
{
	SDL_SysWMinfo MFW3D_InputMgr::InitWindow(Ogre::String mAppName, Ogre::Root* root)
	{
		mUseSDL = true;
		mRoot = root;
		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();
		Ogre::uint32 w, h;
		std::istringstream mode(ropts["Video Mode"].currentValue);
		Ogre::String token;
		mode >> w; // width
		mode >> token; // 'x' as seperator between width and height
		mode >> h; // height

		if (!SDL_WasInit(SDL_INIT_VIDEO)) {
			SDL_InitSubSystem(SDL_INIT_VIDEO);
		}
		mSDLWindow = SDL_CreateWindow(mAppName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE);
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(mSDLWindow, &wmInfo);
		return wmInfo;
	}

	void MFW3D_InputMgr::init(Ogre::Root* root, Ogre::RenderWindow* window, std::function<void(Ogre::RenderWindow* rw)> onwindowResized)
	{
		mRoot = root;
		mWindow = window;
		OnwindowResized = onwindowResized;
	}
	void MFW3D_InputMgr::SetupWindow(bool _grab)
	{
		if (!mSDLWindow)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_STATE,
				"you must create a SDL window first",
				"SampleContext::setupInput");
		}
		//sdlÊó±êËø¶¨
		SDL_ShowCursor(SDL_TRUE);
		SDL_bool grab = SDL_bool(_grab);
		SDL_SetWindowGrab(mSDLWindow, grab);
		SDL_SetRelativeMouseMode(grab);
	}

	bool MFW3D_InputMgr::PollEvent()
	{
		if (mUseSDL)
		{
			if (!mSDLWindow)
			{
				return false;
			}
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					mRoot->queueEndRendering();
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						mWindow->resize(event.window.data1, event.window.data2);
						OnwindowResized(mWindow);
					}
					break;
				default:
					for (std::set<MFW3D_InputListener*>::iterator it = mInputListeners.begin();
						it != mInputListeners.end(); ++it) {
						MFW3D_InputListener& l = **it;
						switch (event.type)
						{
						case SDL_KEYDOWN:
							// Ignore repeated signals from key being held down.
							if (event.key.repeat) break;
							l.keyPressed(event.key);
							break;
						case SDL_KEYUP:
							l.keyReleased(event.key);
							break;
						case SDL_MOUSEBUTTONDOWN:
							l.mousePressed(event.button);
							break;
						case SDL_MOUSEBUTTONUP:
							l.mouseReleased(event.button);
							break;
						case SDL_MOUSEWHEEL:
							l.mouseWheelRolled(event.wheel);
							break;
						case SDL_MOUSEMOTION:
							l.mouseMoved(event.motion);
							break;
						case SDL_FINGERDOWN:
							// for finger down we have to move the pointer first
							l.touchMoved(event.tfinger);
							l.touchPressed(event.tfinger);
							break;
						case SDL_FINGERUP:
							l.touchReleased(event.tfinger);
							break;
						case SDL_FINGERMOTION:
							l.touchMoved(event.tfinger);
							break;
						}
					}
					break;
				}
			}
			return true;
		}
	}

	void MFW3D_InputMgr::Destroy()
	{
		if (mSDLWindow) {
			SDL_DestroyWindow(mSDLWindow);
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			mSDLWindow = NULL;
		}
	}


	void MFW3D_InputMgr::PushSDL_Event(SDL_Event& event)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			if (mRoot != nullptr)
				mRoot->queueEndRendering();
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				mWindow->resize(event.window.data1, event.window.data2);
				OnwindowResized(mWindow);
			}
			break;
		default:
			for (std::set<MFW3D_InputListener*>::iterator it = mInputListeners.begin();
				it != mInputListeners.end(); ++it) {
				MFW3D_InputListener& l = **it;
				switch (event.type)
				{
				case SDL_KEYDOWN:
					// Ignore repeated signals from key being held down.
					l.keyPressed(event.key);
					break;
				case SDL_KEYUP:
					l.keyReleased(event.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					l.mousePressed(event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					l.mouseReleased(event.button);
					break;
				case SDL_MOUSEWHEEL:
					l.mouseWheelRolled(event.wheel);
					break;
				case SDL_MOUSEMOTION:
					l.mouseMoved(event.motion);
					break;
				case SDL_FINGERDOWN:
					// for finger down we have to move the pointer first
					l.touchMoved(event.tfinger);
					l.touchPressed(event.tfinger);
					break;
				case SDL_FINGERUP:
					l.touchReleased(event.tfinger);
					break;
				case SDL_FINGERMOTION:
					l.touchMoved(event.tfinger);
					break;
				}
			}
			break;
		}
	}


}