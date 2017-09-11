#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "OgreFrameListener.h"
#include "MFW3D_Input.h"
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

    class  CameraMan : public InputListener
    {
    public:
        CameraMan(Ogre::SceneNode* cam);

        //更改主相机
        void setCamera(Ogre::SceneNode* cam);
        Ogre::SceneNode* getCamera()
        {
            return mCamera;
        }

        /**
        Sets the target we will revolve around. Only applies for orbit style.
        */
        virtual void setTarget(Ogre::SceneNode* target);

        Ogre::SceneNode* getTarget()
        {
            return mTarget;
        }

        /**
        Sets the spatial offset from the target. Only applies for orbit style.
        */
        void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);

        /**
        Sets the camera's top speed. Only applies for free-look style.
        */
        void setTopSpeed(Ogre::Real topSpeed)
        {
            mTopSpeed = topSpeed;
        }

        Ogre::Real getTopSpeed()
        {
            return mTopSpeed;
        }

        /**
        Sets the movement style of our camera man.
        */
        virtual void setStyle(CameraStyle style);

        CameraStyle getStyle()
        {
            return mStyle;
        }

        /**
        Manually stops the camera when in free-look mode.
        */
        void manualStop();

        void frameRendered(const Ogre::FrameEvent& evt);

        /**
        Processes key presses for free-look style movement.
        */
        bool keyPressed(const KeyboardEvent& evt);

        /**
        Processes key releases for free-look style movement.
        */
        bool keyReleased(const KeyboardEvent& evt);

        /**
        Processes mouse movement differently for each style.
        */
        bool mouseMoved(const MouseMotionEvent& evt);

        bool mouseWheelRolled(const MouseWheelEvent& evt);

        /**
        Processes mouse presses. Only applies for orbit style.
        Left button is for orbiting, and right button is for zooming.
        */
        bool mousePressed(const MouseButtonEvent& evt);

        /**
        Processes mouse releases. Only applies for orbit style.
        Left button is for orbiting, and right button is for zooming.
        */
        bool mouseReleased(const MouseButtonEvent& evt);

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
