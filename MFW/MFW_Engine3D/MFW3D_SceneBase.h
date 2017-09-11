#pragma once
#include "MFW3D_Base.h"
#include "MFW_Trays.h"
#include "MFW3D_CameraMan.h"
#include "MFW3D_AdvancedRenderControls.h"
#include "Ogre.h"
/*
�����Ļ������ƣ�����������ã��Լ��������̴����¼��ļ��
*/
namespace MFW3D
{
    class MFW3D_SceneBase : public MFW3D_Base, public MFW3D::TrayListener
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
    protected:
		virtual void setupView();
		virtual void setDragLook(bool enabled);
        Ogre::Viewport* mViewport;          // ���ӽ�
        Ogre::Camera* mCamera;              // �����
        Ogre::SceneNode* mCameraNode;       // ����ڵ�
		MFW3D::TrayManager* mTrayMgr;           // tray����ӿ�
		MFW3D::CameraMan* mCameraMan;           // ���������������
		MFW3D::AdvancedRenderControls* mControls; // ������ϸ��Ϣ���
        bool mCursorWasVisible;             // ���Ի�����ֵ�ʱ��������Ƿ�ɼ�
        bool mDragLook;                     // ����϶��Ĵ��鿴
    };
}

