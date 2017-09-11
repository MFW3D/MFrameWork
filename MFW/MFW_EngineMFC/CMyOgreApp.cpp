#include "StdAfx.h"
#include "CMyOgreApp.h"


CMyOgreApp::CMyOgreApp(void)
{
}


CMyOgreApp::~CMyOgreApp(void)
{
}


bool CMyOgreApp::go(CRect rt, HWND hWnd)
{
	createRoot();
	setupResources();
	setupRenderSystem();
	createRenderWindow(hWnd, rt.Width(), rt.Height());
	chooseSceneManager();
	createCamera();
	createViewport();
	initializeResourceGroups();
	createScene();
	//createFrameListener();
	return true;
}


void CMyOgreApp::createRoot(void)
{
	mRoot = new Ogre::Root("plugins_d.cfg");
}


void CMyOgreApp::setupResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load("resources_d.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}


void CMyOgreApp::setupRenderSystem(void)
{
	
	if (!mRoot->restoreConfig()) {
		 mRoot->showConfigDialog();
	}
	//if (!mRoot->restoreConfig() && !mRoot->showConfigDialog())
	//	throw Ogre::Exception(1, "未选择渲染系统","setupRenderSystem()");
}


void CMyOgreApp::createRenderWindow(HWND m_hWnd, int width, int height)
{
	mRoot->initialise(false);//禁止ogre创建新的渲染窗口，而使用MFC的窗口
	NameValuePairList misc;
	misc["externalWindowHandle"] = StringConverter::toString((int)m_hWnd);
	mWindow = mRoot->createRenderWindow("OgreRenderWindow", width, height, false, &misc);
}


int CMyOgreApp::initializeResourceGroups(void)
{
	TextureManager::getSingleton().setDefaultNumMipmaps(5);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	return 0;
}


void CMyOgreApp::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
}


void CMyOgreApp::createCamera(void)
{
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCameraNode->attachObject(mCamera);
	mCameraNode->setFixedYawAxis(true);

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0, 0, 80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0, 0, -300));
	mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::CameraMan(mCameraNode);   // create a default camera controller
}


void CMyOgreApp::createViewport(void)
{
	// Create one viewport, entire window
	Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0, 0, 0));
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}


void CMyOgreApp::createScene(void)
{

	//添加背景
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 6, 8);

	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

	Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);

	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20, 80, 50);
}

//创建帧监听
void CMyOgreApp::createFrameListener(void)
{
	//	mListener= new CAOgreFrameListener(mWindow, mCamera, mSceneMgr, light,/*headNode,*/ m_a_senode);
	//	mRoot->addFrameListener(mListener);
}





