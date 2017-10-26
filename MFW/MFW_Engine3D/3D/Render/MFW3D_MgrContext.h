#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"
#include "OgreFrameListener.h"


namespace Ogre {
	class OverlaySystem;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE |OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "macUtils.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#   ifdef __OBJC__
#       import <UIKit/UIKit.h>
#   endif
#endif
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#include <android/configuration.h>
#include <android/asset_manager.h>
#include <android/native_window.h>
#include <android/input.h>
#endif

#include "../Input/MFW3D_Input.h"
#include "OgreWindowEventUtilities.h"

namespace MFW3D
{
	class  MFW3D_MgrContext :
		public Ogre::FrameListener,
		public Ogre::WindowEventListener
	{
	public:
		explicit MFW3D_MgrContext(const Ogre::String& appName = OGRE_VERSION_NAME, bool grabInput = true);
		virtual ~MFW3D_MgrContext();
		Ogre::RenderWindow* getRenderWindow() const
		{
			return mWindow;
		}
		Ogre::Root* getRoot() const {
			return mRoot;
		}
		Ogre::OverlaySystem* getOverlaySystem() const {
			return mOverlaySystem;
		}
		//初始化渲染系统和资源
		void initApp();
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		void initAppForAndroid(AAssetManager* assetMgr, ANativeWindow* window);
		void _fireInputEventAndroid(AInputEvent* event, int wheel = 0);
#endif
		//关闭app
		void closeApp();
		virtual bool frameStarted(const Ogre::FrameEvent& evt) {
			pollEvents();
			return true;
		}
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
		virtual void windowMoved(Ogre::RenderWindow* rw) {}
		virtual void windowResized(Ogre::RenderWindow* rw) {}
		virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
		virtual void windowClosed(Ogre::RenderWindow* rw) {}
		virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

		void setRTSSWriteShadersToDisk(bool write);
		void destroyRTShaderSystem();
		virtual void setup();//设置内容
		virtual void createRoot();//创建ogre根节点
		virtual void locateResources();//设置资源的加载路径，默认为配置的路径，也可以自己定义
		virtual void loadResources();
		virtual void reconfigure(const Ogre::String& renderer, Ogre::NameValuePairList& options);
		virtual void shutdown();
		bool pollEvents();//转发窗口事件
		void enableShaderCache() const;
	protected:
		//创建一个窗口，必须是sdl的否则sdl无法接收到消息事件
		virtual Ogre::RenderWindow* createWindow();
		//创建自定义的窗口
		virtual Ogre::RenderWindow * createWindow(HWND m_hWnd, int width, int height);

#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
		Ogre::DataStreamPtr openAPKFile(const Ogre::String& fileName);
		AAssetManager* mAAssetMgr;
		ANativeWindow* mAWindow;
		AConfiguration* mAConfig;
#endif

#if (OGRE_THREAD_PROVIDER == 3) && (OGRE_NO_TBB_SCHEDULER == 1)
		tbb::task_scheduler_init mTaskScheduler;
#endif
		Ogre::OverlaySystem* mOverlaySystem;		//界面层元素
		Ogre::FileSystemLayer* mFSLayer;			
		bool mGrabInput;
		bool mFirstRun;
		Ogre::String mNextRenderer;					
		Ogre::String mAppName;
		Ogre::NameValuePairList mLastSceneState;   
		Ogre::RenderWindow* mWindow;				
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		Ogre::String                           mRTShaderLibPath;
#endif // INCLUDE_RTSHADER_SYSTEM
	protected:
		Ogre::Root* mRoot;              
	};
}
