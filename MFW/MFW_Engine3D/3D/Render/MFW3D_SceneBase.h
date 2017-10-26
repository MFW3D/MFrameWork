#pragma once
#include "MFW3D_Base.h"
#include "../UI/MFW3D_UIMgr.h"
#include "../tools/MFW3D_CameraController.h"
#include "Ogre.h"
/*
场景的基本控制，和相机的设置，以及对鼠标键盘窗体事件的监控
*/
namespace MFW3D
{
    class MFW3D_SceneBase : public MFW3D_Base, public MFW3D::MFW3D_UIListener
    {
    public:
		MFW3D_SceneBase();
		virtual void unpaused();
		virtual void saveState(Ogre::NameValuePairList& state);
		virtual void restoreState(Ogre::NameValuePairList& state);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual bool keyPressed(const MFW3D::KeyboardEvent& evt);
		virtual bool keyReleased(const MFW3D::KeyboardEvent& evt);
		virtual bool mouseMoved(const MFW3D::MouseMotionEvent& evt);
		virtual bool touchMoved(const MFW3D::TouchFingerEvent& evt);
		virtual bool mousePressed(const MFW3D::MouseButtonEvent& evt);
		virtual bool touchPressed(const MFW3D::TouchFingerEvent& evt);
		virtual bool mouseReleased(const MFW3D::MouseButtonEvent& evt);
		virtual bool touchReleased(const MFW3D::TouchFingerEvent& evt);
		virtual bool mouseWheelRolled(const MFW3D::MouseWheelEvent& evt);
		virtual void _setup(Ogre::RenderWindow* window, 
			Ogre::FileSystemLayer* fsLayer, Ogre::OverlaySystem* overlaySys);
		virtual void _shutdown();
		MFW3D::MFW3D_UIMgr* GetUIMgr()
		{
			return mUIMgr;
		}

    protected:
		virtual void setupView();
		virtual void setDragLook(bool enabled);
        Ogre::Viewport* mViewport;          // 主视角
        Ogre::Camera* mCamera;              // 主相机
        Ogre::SceneNode* mCameraNode;       // 相机节点
		MFW3D::MFW3D_UIMgr* mUIMgr;           // tray管理接口
		MFW3D::MFW3D_CameraController* mCameraMan;           // 基本的相机控制器
        bool mCursorWasVisible;             // 当对话框出现的时候鼠标光标是否可见
        bool mDragLook;                     // 点击拖动四处查看
    };
}

