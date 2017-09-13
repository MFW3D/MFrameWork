#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"
#include "OgreFrameListener.h"

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#include "MFW3D_SGTRListener.h"
#endif 


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

#include "MFW3D_Input.h"
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

		bool initialiseRTShaderSystem();
		void setRTSSWriteShadersToDisk(bool write);
		void destroyRTShaderSystem();
		//设置内容
		virtual void setup(bool UseSdl = true);
		//创建ogre根节点
		virtual void createRoot();
		//只进行一次的配置
		virtual bool oneTimeConfig();
		//设置SDL的配置
		virtual void setupInput(bool grab);
		//设置资源的加载路径，默认为配置的路径，也可以自己定义
		virtual void locateResources();
		virtual void loadResources();
		virtual void reconfigure(const Ogre::String& renderer, Ogre::NameValuePairList& options);
		//关闭
		virtual void shutdown();
		//转发窗口事件
		void pollEvents();
		//创建样品场景
		void createDummyScene();
		//销毁样品场景
		void destroyDummyScene();
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
		Ogre::OverlaySystem* mOverlaySystem;  // Overlay system
		Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
		bool mGrabInput;
		bool mFirstRun;
		Ogre::String mNextRenderer;     // name of renderer used for next run
		Ogre::String mAppName;
		Ogre::NameValuePairList mLastSampleState;     // state of last sample
		Ogre::RenderWindow* mWindow;    // render window
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		Ogre::RTShader::ShaderGenerator*       mShaderGenerator; // The Shader generator instance.
		MFW3D_SGTRListener*       mMaterialMgrListener; // Shader generator material manager listener.
		Ogre::String                           mRTShaderLibPath;
#endif // INCLUDE_RTSHADER_SYSTEM
	protected:
		Ogre::Root* mRoot;              // OGRE root
	};
}
