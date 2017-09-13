#pragma once

#include "OgreRoot.h"
#include "OgreOverlaySystem.h"
#include "OgreResourceManager.h"
#include "OgreFileSystemLayer.h"
#include "MFW3D_Input.h"
#ifdef INCLUDE_RTSHADER_SYSTEM
#   include "OgreRTShaderSystem.h"
#endif //INCLUDE_RTSHADER_SYSTEM

#if OGRE_PLATFORM == OGRE_PLATFORM_NACL && !defined(INCLUDE_RTSHADER_SYSTEM)
#   define INCLUDE_RTSHADER_SYSTEM
#include "OgreShaderGenerator.h"
#endif

/*
设置保存场景中的信息,创建场景管理器
*/

namespace MFW3D
{
    class MFW3D_Base : public Ogre::GeneralAllocatedObject
    {
    public:
        struct Comparer
        {
            bool operator() (MFW3D_Base* a, MFW3D_Base* b)
            {
                Ogre::NameValuePairList::iterator aTitle = a->getInfo().find("Title");
                Ogre::NameValuePairList::iterator bTitle = b->getInfo().find("Title");
                
                if (aTitle != a->getInfo().end() && bTitle != b->getInfo().end())
                    return aTitle->second.compare(bTitle->second) < 0;
                else return false;
            }
        };
		MFW3D_Base();

		virtual ~MFW3D_Base();
		Ogre::NameValuePairList& getInfo();
		virtual void testCapabilities(const Ogre::RenderSystemCapabilities* caps);
		virtual Ogre::String getRequiredRenderSystem();
		virtual Ogre::StringVector getRequiredPlugins();
		Ogre::SceneManager* getSceneManager();
		bool isDone();
		virtual void _setup(Ogre::RenderWindow* window, Ogre::FileSystemLayer* fsLayer, Ogre::OverlaySystem* overlaySys);
		virtual void _shutdown();
		virtual void paused();
		virtual void unpaused();
		virtual void saveState(Ogre::NameValuePairList& state);
		virtual void restoreState(Ogre::NameValuePairList& state);
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual void windowMoved(Ogre::RenderWindow* rw);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual bool windowClosing(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);
		virtual bool keyPressed(const MFW3D::KeyboardEvent& evt);
		virtual bool keyReleased(const MFW3D::KeyboardEvent& evt);
		virtual bool touchMoved(const MFW3D::TouchFingerEvent& evt);
		virtual bool touchPressed(const MFW3D::TouchFingerEvent& evt);
		virtual bool touchReleased(const MFW3D::TouchFingerEvent& evt);
		virtual bool mouseMoved(const MFW3D::MouseMotionEvent& evt);
		virtual bool mouseWheelRolled(const MFW3D::MouseWheelEvent& evt);
		virtual bool mousePressed(const MFW3D::MouseButtonEvent& evt);
		virtual bool mouseReleased(const MFW3D::MouseButtonEvent& evt);
    protected:
		virtual void locateResources();
		virtual void loadResources();
		virtual void createSceneManager();
		virtual void setupView();
		virtual void setupContent();
		virtual void cleanupContent();
		virtual void unloadResources();
        Ogre::Root* mRoot;                // OGRE的根节点
        Ogre::OverlaySystem* mOverlaySystem; // UI系统
        Ogre::RenderWindow* mWindow;      // 内容渲染窗口
        Ogre::FileSystemLayer* mFSLayer;          // 文件系统抽象层
        Ogre::SceneManager* mSceneMgr;    // 这个例子的场景管理器
        Ogre::NameValuePairList mInfo;    // 自定义信息
        bool mDone;                       //标记场景结束
        bool mResourcesLoaded;    // 资源是否加载
        bool mContentSetup;       // 场景是否创建
#ifdef INCLUDE_RTSHADER_SYSTEM
		Ogre::RTShader::ShaderGenerator*            mShaderGenerator;           // The Shader generator instance.
	public:
		void setShaderGenerator(Ogre::RTShader::ShaderGenerator* shaderGenerator)
		{
			mShaderGenerator = shaderGenerator;
		};
#endif
    };
    typedef std::set<MFW3D_Base*, MFW3D_Base::Comparer> SceneSet;
}
