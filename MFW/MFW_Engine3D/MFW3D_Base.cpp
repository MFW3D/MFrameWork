#include "MFW3D_Base.h"
namespace MFW3D
{
#ifdef INCLUDE_RTSHADER_SYSTEM
	MFW3D_Base::MFW3D_Base()() : mShaderGenerator(0)
#else
	MFW3D_Base::MFW3D_Base()
#endif
	{
		mRoot = Ogre::Root::getSingletonPtr();
		mWindow = 0;
		mSceneMgr = 0;
		mDone = true;
		mResourcesLoaded = false;
		mContentSetup = false;

		mFSLayer = 0;
		mOverlaySystem = 0;
	}
	MFW3D_Base::~MFW3D_Base() {}

	Ogre::NameValuePairList& MFW3D_Base::getInfo()
	{
		return mInfo;
	}
	void MFW3D_Base::testCapabilities(const Ogre::RenderSystemCapabilities* caps) {}
	Ogre::String MFW3D_Base::getRequiredRenderSystem()
	{
		return "";
	}
	Ogre::StringVector MFW3D_Base::getRequiredPlugins()
	{
		return Ogre::StringVector();
	}
	Ogre::SceneManager* MFW3D_Base::getSceneManager()
	{
		return mSceneMgr;
	}

	bool MFW3D_Base::isDone()
	{
		return mDone;
	}

	void MFW3D_Base::_setup(Ogre::RenderWindow* window, Ogre::FileSystemLayer* fsLayer, 
		Ogre::OverlaySystem* overlaySys)
	{
		mRoot = Ogre::Root::getSingletonPtr();
		mOverlaySystem = overlaySys;
		mWindow = window;
		mFSLayer = fsLayer;
		locateResources();
		createSceneManager();
		setupView();
		loadResources();
		mResourcesLoaded = true;
		setupContent();
		mContentSetup = true;
		mDone = false;
	}
	void MFW3D_Base::_shutdown()

	{
		if (mContentSetup)
			cleanupContent();
		if (mSceneMgr)
			mSceneMgr->clearScene();
		mContentSetup = false;
		if (mResourcesLoaded)
			unloadResources();
		mResourcesLoaded = false;
		if (mSceneMgr)
		{
#ifdef INCLUDE_RTSHADER_SYSTEM
			mShaderGenerator->removeSceneManager(mSceneMgr);
#endif
			mSceneMgr->removeRenderQueueListener(mOverlaySystem);
			mRoot->destroySceneManager(mSceneMgr);
		}
		mSceneMgr = 0;
		mDone = true;
	}
	void MFW3D_Base::paused() 
	{
	}
	void MFW3D_Base::unpaused() 
	{
	}
	void MFW3D_Base::saveState(Ogre::NameValuePairList& state) 
	{
	}
	void MFW3D_Base::restoreState(Ogre::NameValuePairList& state) 
	{
	}
	bool MFW3D_Base::frameStarted(const Ogre::FrameEvent& evt)
	{ 
		return true;
	}
	bool MFW3D_Base::frameRenderingQueued(const Ogre::FrameEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::frameEnded(const Ogre::FrameEvent& evt)
	{ 
		return true;
	}
	void MFW3D_Base::windowMoved(Ogre::RenderWindow* rw) 
	{
	}
	void MFW3D_Base::windowResized(Ogre::RenderWindow* rw) 
	{
	}
	bool MFW3D_Base::windowClosing(Ogre::RenderWindow* rw) 
	{ return true; }
	void MFW3D_Base::windowClosed(Ogre::RenderWindow* rw) 
	{
	}
	void MFW3D_Base::windowFocusChange(Ogre::RenderWindow* rw) 
	{
	}
	bool MFW3D_Base::keyPressed(const MFW3D::KeyboardEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::keyReleased(const MFW3D::KeyboardEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::touchMoved(const MFW3D::TouchFingerEvent& evt)
	{ 
		return true;
	}
	bool MFW3D_Base::touchPressed(const MFW3D::TouchFingerEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::touchReleased(const MFW3D::TouchFingerEvent& evt) 
	{ 
		return true; 
	}
	bool MFW3D_Base::mouseMoved(const MFW3D::MouseMotionEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::mouseWheelRolled(const MFW3D::MouseWheelEvent& evt)
	{ 
		return true; 
	}
	bool MFW3D_Base::mousePressed(const MFW3D::MouseButtonEvent& evt) 
	{ 
		return true;
	}
	bool MFW3D_Base::mouseReleased(const MFW3D::MouseButtonEvent& evt)
	{ 
		return true;
	}
	void MFW3D_Base::locateResources() 
	{
	}
	void MFW3D_Base::loadResources() 
	{
	}
	void MFW3D_Base::createSceneManager()
	{
		mSceneMgr = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
#ifdef INCLUDE_RTSHADER_SYSTEM
		mShaderGenerator->addSceneManager(mSceneMgr);
#endif
		if (mOverlaySystem)
			mSceneMgr->addRenderQueueListener(mOverlaySystem);
	}
	void MFW3D_Base::setupView() 
	{
	}
	void MFW3D_Base::setupContent() 
	{
	}
	void MFW3D_Base::cleanupContent()
	{
	}
	void MFW3D_Base::unloadResources()
	{
		Ogre::ResourceGroupManager::ResourceManagerIterator resMgrs =
			Ogre::ResourceGroupManager::getSingleton().getResourceManagerIterator();
		while (resMgrs.hasMoreElements())
		{
			resMgrs.getNext()->unloadUnreferencedResources();
		}
	}
}