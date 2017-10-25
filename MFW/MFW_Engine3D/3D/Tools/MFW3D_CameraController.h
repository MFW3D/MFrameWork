#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "OgreFrameListener.h"
#include "../Input/MFW3D_Input.h"
/*
相机控制
*/
namespace MFW3D
{
    enum CameraStyle  
    {
        CS_FREELOOK,
        CS_ORBIT,
        CS_MANUAL
    };

    class MFW3D_CameraController : public MFW3D_InputListener
    {
    public:
        MFW3D_CameraController(Ogre::SceneNode* cam);

		//更改主相机
        void setCamera(Ogre::SceneNode* cam);
        Ogre::SceneNode* getCamera()
        {
            return mCamera;
        }
		//定点旋转
        virtual void setTarget(Ogre::SceneNode* target);
        Ogre::SceneNode* getTarget()
        {
            return mTarget;
        }
        void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);
        bool mousePressed(const MouseButtonEvent& evt);
        bool mouseReleased(const MouseButtonEvent& evt);
		//自由移动
		void setTopSpeed(Ogre::Real topSpeed)
        {
            mTopSpeed = topSpeed;
        }
        Ogre::Real getTopSpeed()
        {
            return mTopSpeed;
        }
        void manualStop();
        bool keyPressed(const KeyboardEvent& evt);
        bool keyReleased(const KeyboardEvent& evt);
		//相机风格
        virtual void setStyle(CameraStyle style);
        CameraStyle getStyle()
        {
            return mStyle;
        }
		
		void frameRendered(const Ogre::FrameEvent& evt);
        bool mouseMoved(const MouseMotionEvent& evt);
        bool mouseWheelRolled(const MouseWheelEvent& evt);
    protected:
        Ogre::SceneNode* mCamera;
        CameraStyle mStyle;
        Ogre::SceneNode* mTarget;
        bool mOrbiting;
        bool mZooming;
        Ogre::Real mTopSpeed;
        Ogre::Vector3 mVelocity;
        bool mGoingForward;
        bool mGoingBack;
        bool mGoingLeft;
        bool mGoingRight;
        bool mGoingUp;
        bool mGoingDown;
        bool mFastMove;
    };
}
