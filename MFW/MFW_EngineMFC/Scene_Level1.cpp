#include "stdafx.h"
#include "Scene_Level1.h"

Scene_Level1::Scene_Level1()
{
	mInfo["Title"] = "Smoke";
	mInfo["Description"] = "Demonstrates depth-sorting of particles in particle systems.";
	mInfo["Thumbnail"] = "thumb_smoke.png";
	mInfo["Category"] = "Effects";
}
bool Scene_Level1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return MFW3D_SceneBase::frameRenderingQueued(evt);
}
void Scene_Level1::setupContent()
{
	mSceneMgr->setSkyBox(true, "Examples/EveningSkyBox");

	// dim orange ambient and two bright orange lights to match the skybox
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.2, 0));
	Ogre::Light* light = mSceneMgr->createLight();
	light->setPosition(2000, 1000, -1000);
	light->setDiffuseColour(1, 0.5, 0);
	light = mSceneMgr->createLight();
	light->setPosition(-2000, 1000, 1000);
	light->setDiffuseColour(1, 0.5, 0);
	mPivot = mSceneMgr->getRootSceneNode()->createChildSceneNode();  // create a pivot node
	Ogre::SceneNode* headNode = mPivot->createChildSceneNode(Ogre::Vector3(100, 0, 0));
	headNode->attachObject(mSceneMgr->createEntity("Head", "ogrehead.mesh"));
	headNode->attachObject(mSceneMgr->createParticleSystem("Smoke", "Examples/Smoke"));
	mCameraNode->setPosition(0, 30, 350);
}
