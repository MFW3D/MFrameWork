#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreBuildSettings.h"
#include "OgreLogManager.h"
#include "OgrePlugin.h"
#include "OgreFileSystemLayer.h"
#include "OgreFrameListener.h"
#include "MFW3D_PluginLoader.h"

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#include "MFW3D_SGTechniqueResolverListener.h"
#endif 
// forward declarations
extern "C" struct SDL_Window;

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
    class  ApplicationContext :
            public Ogre::FrameListener,
            public Ogre::WindowEventListener
    {
    public:
        explicit ApplicationContext(const Ogre::String& appName = OGRE_VERSION_NAME, bool grabInput = true);
        virtual ~ApplicationContext();
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
        //��ʼ����Ⱦϵͳ����Դ
        void initApp();
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
        void initAppForAndroid(AAssetManager* assetMgr, ANativeWindow* window);
        void _fireInputEventAndroid(AInputEvent* event, int wheel = 0);
#endif
		//�ر�app
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

        void _fireInputEvent(const Event& event) const;
        bool initialiseRTShaderSystem();
        void setRTSSWriteShadersToDisk(bool write);
        void destroyRTShaderSystem();
		//��������
		virtual void setup(bool UseSdl=true);
		//����ogre���ڵ�
        virtual void createRoot();
		//ֻ����һ�ε�����
        virtual bool oneTimeConfig();
		//����SDL������
        virtual void setupInput(bool grab);
		//������Դ�ļ���·����Ĭ��Ϊ���õ�·����Ҳ�����Լ�����
        virtual void locateResources();
        virtual void loadResources();
        virtual void reconfigure(const Ogre::String& renderer, Ogre::NameValuePairList& options);
		//�ر�
        virtual void shutdown();
		//ת�������¼�
        void pollEvents();
		//������Ʒ����
        void createDummyScene();
		//������Ʒ����
        void destroyDummyScene();
        void enableShaderCache() const;
        void addInputListener(InputListener* lis) {
            mInputListeners.insert(lis);
        }
        void removeInputListener(InputListener* lis) {
            mInputListeners.erase(lis);
        }
    protected:
		//����һ�����ڣ�������sdl�ķ���sdl�޷����յ���Ϣ�¼�
        virtual Ogre::RenderWindow* createWindow();
		//�����Զ���Ĵ���
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
        Ogre::Root* mRoot;              // OGRE root
        MFW3D_PluginLoader mStaticPluginLoader;
        bool mGrabInput;
        bool mFirstRun;
        Ogre::String mNextRenderer;     // name of renderer used for next run
        Ogre::String mAppName;
        Ogre::NameValuePairList mLastSampleState;     // state of last sample
        Ogre::RenderWindow* mWindow;    // render window
        SDL_Window* mSDLWindow;
        std::set<InputListener*> mInputListeners;
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
        Ogre::RTShader::ShaderGenerator*       mShaderGenerator; // The Shader generator instance.
        SGTechniqueResolverListener*       mMaterialMgrListener; // Shader generator material manager listener.
        Ogre::String                           mRTShaderLibPath;
#endif // INCLUDE_RTSHADER_SYSTEM
    };
}
