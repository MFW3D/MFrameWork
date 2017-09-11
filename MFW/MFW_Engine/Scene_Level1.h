#pragma once
#include "MFW3D_SceneBase.h"
#include "Hydrax.h"
#include "Perlin.h"
#include "ProjectedGrid.h"
#define _def_SkyBoxNum 3

class Scene_Level1 :public MFW3D::MFW3D_SceneBase
{
private:
	// Hydrax pointer
	Hydrax::Hydrax *mHydrax = 0;

	Ogre::String mSkyBoxes[_def_SkyBoxNum] =
	{ "Sky/ClubTropicana",
		"Sky/EarlyMorning",
		"Sky/Clouds" };

	Ogre::Vector3 mSunPosition[_def_SkyBoxNum] =
	{ Ogre::Vector3(0,10000,0),
		Ogre::Vector3(0,10000,90000),
		Ogre::Vector3(0,10000,0) };

	Ogre::Vector3 mSunColor[_def_SkyBoxNum] =
	{ Ogre::Vector3(1, 0.9, 0.6),
		Ogre::Vector3(1,0.6,0.4),
		Ogre::Vector3(0.45,0.45,0.45) };

	int mCurrentSkyBox = 0;

	// Just to wshow skyboxes information
	Ogre::TextAreaOverlayElement* mTextArea = 0;
public:
	Ogre::SceneNode* mPivot;
	Scene_Level1();
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void setupContent();
	void createTextArea();

	virtual bool keyPressed(const MFW3D::KeyboardEvent& evt);
	virtual bool keyReleased(const MFW3D::KeyboardEvent& evt);
	virtual bool mouseMoved(const MFW3D::MouseMotionEvent& evt);
	virtual bool mousePressed(const MFW3D::MouseButtonEvent& evt);
	virtual bool mouseReleased(const MFW3D::MouseButtonEvent& evt);
};

