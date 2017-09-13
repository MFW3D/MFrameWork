#pragma once
#include "MFW3D_ApplicationContext.h"
#include "MFW3D_Base.h"
#include "Ogre.h"
namespace MFW3D
{
    class MFW3D_SceneMgr : public MFW3D::ApplicationContext, MFW3D::InputListener
    {
    public:

		MFW3D_SceneMgr(const Ogre::String& appName = OGRE_VERSION_NAME,
			bool grabInput = true);
		virtual MFW3D_Base* getCurrentScene();
		virtual void runScene(MFW3D_Base* sceneBase);
		virtual void go(MFW3D_Base* initialScene = 0);
		virtual void go(MFW3D_Base* initialScene,HWND hWnd, int width, int height);
		virtual void loadStartUpScene();
		virtual bool isCurrentScenePaused();
		virtual void pauseCurrentScene();
		virtual void unpauseCurrentScene();
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowMoved(Ogre::RenderWindow* rw);
		virtual bool windowClosing(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);
		virtual bool keyPressed(const MFW3D::KeyboardEvent& evt);
		virtual bool keyReleased(const MFW3D::KeyboardEvent& evt);
		void transformInputState(MFW3D::TouchFingerEvent &state);
		virtual bool touchMoved(const MFW3D::TouchFingerEvent& evt);
		virtual bool mouseMoved(const MFW3D::MouseMotionEvent& evt);
		virtual bool touchPressed(const MFW3D::TouchFingerEvent& evt);
		virtual bool mousePressed(const MFW3D::MouseButtonEvent& evt);
		virtual bool touchReleased(const MFW3D::TouchFingerEvent& evt);
		virtual bool mouseReleased(const MFW3D::MouseButtonEvent& evt);
		virtual bool mouseWheelRolled(const MFW3D::MouseWheelEvent& evt);
		bool isFirstRun();
		void setFirstRun(bool flag);
		bool isLastRun();
		void setLastRun(bool flag);
    protected:
		virtual void reconfigure(const Ogre::String& renderer,
			Ogre::NameValuePairList& options);
		virtual void recoverLastScene();
		virtual void shutdown();
		MFW3D_Base* mCurrentScene;			// 当前运行的场景
        bool mScenePaused;					// 当前场景是否暂停
        bool mLastRun;						// 是否是第一次运行场景
		MFW3D_Base* mLastScene;				// 重新加载配置后的场最后一个运行场景
        Ogre::NameValuePairList mLastSampleState;     // 最后一个场景的状态
    };
}
