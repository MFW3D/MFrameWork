#include "Scene_Level1.h"
float seed_ = 801;
float rnd_(const float& min, const float& max)
{
	seed_ += Ogre::Math::PI*2.8574f + seed_*(0.3424f - 0.12434f + 0.452345f);
	if (seed_ > 10000000000) seed_ -= 10000000000;
	return ((max - min)*Ogre::Math::Abs(Ogre::Math::Sin(Ogre::Radian(seed_))) + min);
}

void createPalms(Ogre::SceneManager *mSceneMgr)
{
	const int NumberOfPalms = 12;

	Ogre::SceneNode* mPalmsSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	for (int k = 0; k < NumberOfPalms; k++)
	{
		Ogre::Vector3 RandomPos = Ogre::Vector3(rnd_(500, 2500),
			0,
			rnd_(500, 2500));

		Ogre::RaySceneQuery * raySceneQuery = mSceneMgr->
			createRayQuery(Ogre::Ray(RandomPos + Ogre::Vector3(0, 1000000, 0),
				Ogre::Vector3::NEGATIVE_UNIT_Y));

		Ogre::RaySceneQueryResult& qryResult = raySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator i = qryResult.begin();

		if (i != qryResult.end() && i->worldFragment)
		{
			if (i->worldFragment->singleIntersection.y > 105 || i->worldFragment->singleIntersection.y < 20)
			{
				k--;
				continue;
			}

			RandomPos.y = i->worldFragment->singleIntersection.y;
		}
		else
		{
			k--;
			continue;
		}

		Ogre::Entity *mPalmEnt = mSceneMgr->createEntity("Palm" + Ogre::StringConverter::toString(k), "Palm.mesh");
		Ogre::SceneNode *mPalmSN = mPalmsSceneNode->createChildSceneNode();

		mPalmSN->rotate(Ogre::Vector3(-1, 0, rnd_(-0.3, 0.3)), Ogre::Degree(90));
		mPalmSN->attachObject(mPalmEnt);
		Ogre::Real Scale = rnd_(50, 75);
		mPalmSN->scale(Scale, Scale, Scale);
		mPalmSN->setPosition(RandomPos);
	}
}

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
	// Set default ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	// Create the SkyBox
	mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999 * 3, true);

	// Set some camera params
	mCamera->setFarClipDistance(99999 * 6);
	mCamera->setPosition(312.902, 206.419, 1524.02);
	mCamera->setOrientation(Ogre::Quaternion(0.998, -0.0121, -0.0608, -0.00074));

	// Light
	Ogre::Light *mLight = mSceneMgr->createLight("Light0");
	mLight->setPosition(mSunPosition[mCurrentSkyBox]);
	mLight->setDiffuseColour(1, 1, 1);
	mLight->setSpecularColour(mSunColor[mCurrentSkyBox].x,
		mSunColor[mCurrentSkyBox].y,
		mSunColor[mCurrentSkyBox].z);

	// Hydrax initialization code ---------------------------------------------
	// ------------------------------------------------------------------------

	// Create Hydrax object
	mHydrax = new Hydrax::Hydrax(mSceneMgr, mCamera, mWindow->getViewport(0));

	// Create our projected grid module  
	Hydrax::Module::ProjectedGrid *mModule
		= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			mHydrax,
			// Noise module
			new Hydrax::Noise::Perlin(/*Generic one*/),
			// Base plane
			Ogre::Plane(Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0)),
			// Normal mode
			Hydrax::MaterialManager::NM_VERTEX,
			// Projected grid options
			Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));

	// Set our module
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

	// Load all parameters from config file
	// Remarks: The config file must be in Hydrax resource group.
	// All parameters can be set/updated directly by code(Like previous versions),
	// but due to the high number of customizable parameters, since 0.4 version, Hydrax allows save/load config files.
	mHydrax->loadCfg("HydraxDemo.hdx");

	// Create water
	mHydrax->create();

	// Hydrax initialization code end -----------------------------------------
	// ------------------------------------------------------------------------

	// Load island
	//maomao
	//mSceneMgr->setWorldGeometry("Island.cfg");

	mHydrax->getMaterialManager()->addDepthTechnique(
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))
		->createTechnique());

	// Create palmiers
	createPalms(mSceneMgr);

	// Create text area to show skyboxes information
	createTextArea();

}
// Create text area to show skyboxes information
void Scene_Level1::createTextArea()
{
	// Create a panel
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "HydraxDemoInformationPanel"));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(10, 10);
	panel->setDimensions(400, 400);

	// Create a text area
	mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", 
			"HydraxDemoInformationTextArea"));
	mTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	mTextArea->setPosition(0, 0);
	mTextArea->setDimensions(100, 100);
	mTextArea->setCharHeight(16);
	mTextArea->setCaption("Hydrax 0.5.1 demo application\nCurrent water preset: " + Ogre::StringUtil::split(mSkyBoxes[mCurrentSkyBox], "/")[1] + " (" + Ogre::StringConverter::toString(mCurrentSkyBox + 1) + "/3). Press 'm' to switch water presets.");
	mTextArea->setFontName("BlueHighway");
	mTextArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	mTextArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	// Create an overlay, and add the panel
	Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("OverlayName");
	overlay->add2D(panel);

	// Add the text area to the panel
	panel->addChild(mTextArea);

	// Show the overlay
	overlay->show();
}

bool Scene_Level1::keyPressed(const MFW3D::KeyboardEvent& evt)
{
	return MFW3D::MFW3D_SceneBase::keyPressed(evt);
}

bool Scene_Level1::keyReleased(const MFW3D::KeyboardEvent& evt)
{
	return MFW3D::MFW3D_SceneBase::keyReleased(evt);
}

bool Scene_Level1::mouseMoved(const MFW3D::MouseMotionEvent& evt)
{

	return MFW3D::MFW3D_SceneBase::mouseMoved(evt);
}

bool Scene_Level1::mousePressed(const MFW3D::MouseButtonEvent& evt)
{

	return MFW3D::MFW3D_SceneBase::mousePressed(evt);
}

bool Scene_Level1::mouseReleased(const MFW3D::MouseButtonEvent& evt)
{

	return MFW3D::MFW3D_SceneBase::mouseReleased(evt);
}