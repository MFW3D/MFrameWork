#include "MFW3D_SceneMgr.h"
namespace MFW3D
{
	MFW3D_SceneMgr::MFW3D_SceneMgr(const Ogre::String& appName ,
		bool grabInput )
		:MFW3D::ApplicationContext(appName, grabInput)
	{
		mCurrentScene = 0;
		mScenePaused = false;
		mLastRun = false;
		mLastScene = 0;
		addInputListener(this);
	}
	MFW3D_Base* MFW3D_SceneMgr::getCurrentScene()
	{
		return mCurrentScene;
	}
	void MFW3D_SceneMgr::runScene(MFW3D_Base* sceneBase)
	{
#if OGRE_PROFILING
		Ogre::Profiler* prof = Ogre::Profiler::getSingletonPtr();
		if (prof)
			prof->setEnabled(false);
#endif
		//关闭当前场景
		if (mCurrentScene)
		{
			mCurrentScene->_shutdown();   
			mScenePaused = false;       
		}
		//去除视口
		mWindow->removeAllViewports(); 
		mWindow->resetStatistics();
		if (sceneBase!=nullptr)
		{
			Ogre::Root::PluginInstanceList ip = mRoot->getInstalledPlugins();
			Ogre::StringVector rp = sceneBase->getRequiredPlugins();
			for (Ogre::StringVector::iterator j = rp.begin(); j != rp.end(); j++)
			{
				bool found = false;
				for (Ogre::Root::PluginInstanceList::iterator k = ip.begin(); k != ip.end(); k++)
				{
					if ((*k)->getName() == *j)
					{
						found = true;
						break;
					}
				}
				if (!found)  
				{
					Ogre::String desc = "Sample requires plugin: " + *j;
					Ogre::String src = "SampleContext::runSample";
					OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, desc, src);
				}
			}
			Ogre::String rrs = sceneBase->getRequiredRenderSystem();
			if (!rrs.empty() && rrs != mRoot->getRenderSystem()->getName())
			{
				Ogre::String desc = "Sample only runs with renderer: " + rrs;
				Ogre::String src = "SampleContext::runSample";
				OGRE_EXCEPT(Ogre::Exception::ERR_INVALID_STATE, desc, src);
			}
			sceneBase->testCapabilities(mRoot->getRenderSystem()->getCapabilities());
			sceneBase->_setup(mWindow, mFSLayer, mOverlaySystem);   // 开始新的例子
		}
#if OGRE_PROFILING
		if (prof)
			prof->setEnabled(true);
#endif
		mCurrentScene = sceneBase;
	}
#if OGRE_PLATFORM != OGRE_PLATFORM_NACL
	void MFW3D_SceneMgr::go(MFW3D_Base* initialScene)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || ((OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__)
		createRoot();

		if (!oneTimeConfig()) return;

		if (!mFirstRun) mRoot->setRenderSystem(mRoot->getRenderSystemByName(mNextRenderer));

		mLastRun = true;  // assume this is our last run

		setup();

		if (!mFirstRun) recoverLastSample();
		else if (initialSample) runSample(initialSample);

		mRoot->saveConfig();
#else
		while (!mLastRun)
		{
			mLastRun = true;  // 假定是最后一次运行
			initApp();
			createWindow();
			setup();

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
			// 如果有需要恢复的场景就恢复一个，如果没有就运行新的场景
			if (!mFirstRun) recoverLastScene();
			else if (initialScene) runScene(initialScene);
#endif
			loadStartUpScene();
			if (mRoot->getRenderSystem() != NULL)
			{
				mRoot->startRendering();    // 开始渲染循环
			}
			closeApp();
			mFirstRun = false;
		}
#endif
	}
	void MFW3D_SceneMgr::go(MFW3D_Base* initialScene,HWND hWnd, int width, int height)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || ((OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__)
		createRoot();

		if (!oneTimeConfig()) return;

		if (!mFirstRun) mRoot->setRenderSystem(mRoot->getRenderSystemByName(mNextRenderer));

		mLastRun = true;  // assume this is our last run

		setup();

		if (!mFirstRun) recoverLastSample();
		else if (initialSample) runSample(initialSample);

		mRoot->saveConfig();
#else
		while (!mLastRun)
		{
			mLastRun = true;  // 假定是最后一次运行
			initApp();
			createWindow(hWnd,width,height);
			setup(false);

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
			// 如果有需要恢复的场景就恢复一个，如果没有就运行新的场景
			if (!mFirstRun) recoverLastScene();
			else if (initialScene) runScene(initialScene);
#endif
			loadStartUpScene();
			if (mRoot->getRenderSystem() != NULL)
			{
				mRoot->startRendering();    // 开始渲染循环
			}
			closeApp();
			mFirstRun = false;
		}
#endif
	}

#endif
	void MFW3D_SceneMgr::loadStartUpScene()
	{
	}
	bool MFW3D_SceneMgr::isCurrentScenePaused()
	{
		if (mCurrentScene) return mScenePaused;
		return false;
	}
	void MFW3D_SceneMgr::pauseCurrentScene()
	{
		if (mCurrentScene && !mScenePaused)
		{
			mScenePaused = true;
			mCurrentScene->paused();
		}
	}
	void MFW3D_SceneMgr::unpauseCurrentScene()
	{
		if (mCurrentScene && mScenePaused)
		{
			mScenePaused = false;
			mCurrentScene->unpaused();
		}
	}
	
	bool MFW3D_SceneMgr::frameStarted(const Ogre::FrameEvent& evt)
	{
		pollEvents();
		// 手动调用例子的回调来保证正确的顺序
		return (mCurrentScene && !mScenePaused) ? mCurrentScene->frameStarted(evt) : true;
	}
	
	bool MFW3D_SceneMgr::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		// 手动调用场景的帧渲染
		return (mCurrentScene && !mScenePaused) ? mCurrentScene->frameRenderingQueued(evt) : true;
	}
	
	bool MFW3D_SceneMgr::frameEnded(const Ogre::FrameEvent& evt)
	{
		if (mCurrentScene && !mScenePaused && !mCurrentScene->frameEnded(evt)) return false;
		if (mWindow->isClosed()) return false;
		if (mCurrentScene && mCurrentScene->isDone()) runScene(0);
		return true;
	}
	
	void MFW3D_SceneMgr::windowResized(Ogre::RenderWindow* rw)
	{
		if (mCurrentScene && !mScenePaused) mCurrentScene->windowResized(rw);
	}
	void MFW3D_SceneMgr::windowMoved(Ogre::RenderWindow* rw)
	{
		if (mCurrentScene && !mScenePaused) mCurrentScene->windowMoved(rw);
	}
	bool MFW3D_SceneMgr::windowClosing(Ogre::RenderWindow* rw)
	{
		if (mCurrentScene && !mScenePaused) return mCurrentScene->windowClosing(rw);
		return true;
	}
	void MFW3D_SceneMgr::windowClosed(Ogre::RenderWindow* rw)
	{
		if (mCurrentScene && !mScenePaused) mCurrentScene->windowClosed(rw);
	}
	void MFW3D_SceneMgr::windowFocusChange(Ogre::RenderWindow* rw)
	{
		if (mCurrentScene && !mScenePaused) mCurrentScene->windowFocusChange(rw);
	}
	bool MFW3D_SceneMgr::keyPressed(const MFW3D::KeyboardEvent& evt)
	{
		if (mCurrentScene && !mScenePaused) return mCurrentScene->keyPressed(evt);
		return true;
	}
	bool MFW3D_SceneMgr::keyReleased(const MFW3D::KeyboardEvent& evt)
	{
		if (mCurrentScene && !mScenePaused) return mCurrentScene->keyReleased(evt);
		return true;
	}
	void MFW3D_SceneMgr::transformInputState(MFW3D::TouchFingerEvent &state)
	{
	}
	bool MFW3D_SceneMgr::touchMoved(const MFW3D::TouchFingerEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->touchMoved(evt);
		return true;
	}
	bool MFW3D_SceneMgr::mouseMoved(const MFW3D::MouseMotionEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->mouseMoved(evt);
		return true;
	}
	bool MFW3D_SceneMgr::touchPressed(const MFW3D::TouchFingerEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->touchPressed(evt);
		return true;
	}
	bool MFW3D_SceneMgr::mousePressed(const MFW3D::MouseButtonEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->mousePressed(evt);
		return true;
	}
	bool MFW3D_SceneMgr::touchReleased(const MFW3D::TouchFingerEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->touchReleased(evt);
		return true;
	}
	bool MFW3D_SceneMgr::mouseReleased(const MFW3D::MouseButtonEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->mouseReleased(evt);
		return true;
	}
#if (OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS) || (OGRE_PLATFORM == OGRE_PLATFORM_ANDROID)
	//FIXME: Handle mouse wheel wheel events on mobile devices.
	// virtual bool touchReleased(const SDL_TouchFingerEvent& evt)
	// {
	//     if (mCurrentSample && !mSamplePaused)
	//         return mCurrentSample->touchReleased(evt);
	//     return true;
	// }
#endif
	bool MFW3D_SceneMgr::mouseWheelRolled(const MFW3D::MouseWheelEvent& evt)
	{
		if (mCurrentScene && !mScenePaused)
			return mCurrentScene->mouseWheelRolled(evt);
		return true;
	}
	bool MFW3D_SceneMgr::isFirstRun() { return mFirstRun; }
	void MFW3D_SceneMgr::setFirstRun(bool flag) { mFirstRun = flag; }
	bool MFW3D_SceneMgr::isLastRun() { return mLastRun; }
	void MFW3D_SceneMgr::setLastRun(bool flag) { mLastRun = flag; }
	void MFW3D_SceneMgr::reconfigure(const Ogre::String& renderer, 
		Ogre::NameValuePairList& options)
	{
		mLastScene = mCurrentScene;
		if (mCurrentScene) mCurrentScene->saveState(mLastSampleState);
		mLastRun = false;            
		ApplicationContext::reconfigure(renderer, options);
	}
	void MFW3D_SceneMgr::recoverLastScene()
	{
		runScene(mLastScene);
		mLastScene->restoreState(mLastSampleState);
		mLastScene = 0;
		mLastSampleState.clear();
	}
	void MFW3D_SceneMgr::shutdown()
	{
		if (mCurrentScene)
		{
			mCurrentScene->_shutdown();
			mCurrentScene = 0;
		}
		ApplicationContext::shutdown();
	}
}