#include "MFW3D_SceneBase.h"

namespace MFW3D
{
	MFW3D_SceneBase::MFW3D_SceneBase()
	{
		mInfo["Title"] = "Untitled";
		mInfo["Description"] = "";
		mInfo["Category"] = "Unsorted";
		mInfo["Thumbnail"] = "";
		mInfo["Help"] = "";

		mTrayMgr = 0;
		mCameraMan = 0;
		mCamera = 0;
		mCameraNode = 0;
		mViewport = 0;
		mControls = 0;
		mCursorWasVisible = false;
		mDragLook = false;
	}
	
	 void MFW3D_SceneBase::unpaused()
	{
		mTrayMgr->refreshCursor();
	}
	
	 void MFW3D_SceneBase::saveState(Ogre::NameValuePairList& state)
	{
		if (mCameraMan->getStyle() == MFW3D::CS_FREELOOK)
		{
			state["CameraPosition"] = Ogre::StringConverter::toString(mCameraNode->getPosition());
			state["CameraOrientation"] = Ogre::StringConverter::toString(mCameraNode->getOrientation());
		}
	}
	
	 void MFW3D_SceneBase::restoreState(Ogre::NameValuePairList& state)
	{
		if (state.find("CameraPosition") != state.end() && state.find("CameraOrientation") != state.end())
		{
			mCameraMan->setStyle(MFW3D::CS_FREELOOK);
			mCameraNode->setPosition(Ogre::StringConverter::parseVector3(state["CameraPosition"]));
			mCameraNode->setOrientation(Ogre::StringConverter::parseQuaternion(state["CameraOrientation"]));
		}
	}
	 bool MFW3D_SceneBase::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		mTrayMgr->frameRendered(evt);
		mControls->frameRendered(evt);
		if (!mTrayMgr->isDialogVisible())
		{
			mCameraMan->frameRendered(evt);  
		}
		return true;
	}
	 void MFW3D_SceneBase::windowResized(Ogre::RenderWindow* rw)
	{
		mCamera->setAspectRatio((Ogre::Real)mViewport->getActualWidth() / (Ogre::Real)mViewport->getActualHeight());
	}
	 bool MFW3D_SceneBase::keyPressed(const MFW3D::KeyboardEvent& evt)
	{
		int key = evt.keysym.sym;
		if (key == 'h' || key == SDLK_F1)  
		{
			if (!mTrayMgr->isDialogVisible() && mInfo["Help"] != "") mTrayMgr->showOkDialog("Help", mInfo["Help"]);
			else mTrayMgr->closeDialog();
		}
		if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
		if (key == SDLK_F6)   // take a screenshot
		{
			mWindow->writeContentsToTimestampedFile("screenshot", ".png");
		}
#if OGRE_PROFILING
		// Toggle visibility of profiler window
		else if (key == 'p')
		{
			Ogre::Profiler* prof = Ogre::Profiler::getSingletonPtr();
			if (prof)
				prof->setEnabled(!prof->getEnabled());
		}
#endif // OGRE_PROFILING
		else {
			mControls->keyPressed(evt);
		}
		mCameraMan->keyPressed(evt);
		return true;
	}

	 bool MFW3D_SceneBase::keyReleased(const MFW3D::KeyboardEvent& evt)
	{
		mCameraMan->keyReleased(evt);
		return true;
	}

	 bool MFW3D_SceneBase::mouseMoved(const MFW3D::MouseMotionEvent& evt)
	{
		if (mTrayMgr->mouseMoved(evt)) 
			return true;
		mCameraMan->mouseMoved(evt);
		return true;
	}

	 bool MFW3D_SceneBase::touchMoved(const MFW3D::TouchFingerEvent& evt) {
		 MFW3D::MouseMotionEvent e;
		e.xrel = evt.dx * mWindow->getWidth();
		e.yrel = evt.dy * mWindow->getHeight();
		return mouseMoved(e);
	}

	 bool MFW3D_SceneBase::mousePressed(const MFW3D::MouseButtonEvent& evt)
	{
		if (mTrayMgr->mousePressed(evt)) 
			return true;
		if (mDragLook && evt.button == MFW3D::BUTTON_LEFT)
		{
			mCameraMan->setStyle(MFW3D::CS_FREELOOK);
			//mTrayMgr->hideCursor();
		}

		mCameraMan->mousePressed(evt);
		return true;
	}

	 bool MFW3D_SceneBase::touchPressed(const MFW3D::TouchFingerEvent& evt) {
		 MFW3D::MouseButtonEvent e;
		e.button = MFW3D::BUTTON_LEFT;
		return mousePressed(e);
	}

	 bool MFW3D_SceneBase::mouseReleased(const MFW3D::MouseButtonEvent& evt)
	{
		if (mTrayMgr->mouseReleased(evt)) return true;

		if (mDragLook && evt.button == MFW3D::BUTTON_LEFT)
		{
			mCameraMan->setStyle(MFW3D::CS_MANUAL);
			//mTrayMgr->showCursor();
		}
		mCameraMan->mouseReleased(evt);
		return true;
	}
	 bool MFW3D_SceneBase::touchReleased(const MFW3D::TouchFingerEvent& evt) {
		 MFW3D::MouseButtonEvent e;
		e.button = MFW3D::BUTTON_LEFT;
		return mouseReleased(e);
	}
	 bool MFW3D_SceneBase::mouseWheelRolled(const MFW3D::MouseWheelEvent& evt) {
		mCameraMan->mouseWheelRolled(evt);
		return true;
	}
	
	 void MFW3D_SceneBase::_setup(Ogre::RenderWindow* window, Ogre::FileSystemLayer* fsLayer, Ogre::OverlaySystem* overlaySys)
	{
		mRoot = Ogre::Root::getSingletonPtr();
		mWindow = window;
		mFSLayer = fsLayer;
		mOverlaySystem = overlaySys;

		locateResources();
		createSceneManager();
		setupView();

		mTrayMgr = new MFW3D::TrayManager("SampleControls", window, this);  // create a tray interface

		loadResources();
		mResourcesLoaded = true;

		mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
		//mTrayMgr->showLogo(TL_BOTTOMRIGHT);
		//mTrayMgr->hideCursor();
		//mTrayMgr->createLabel(MFW3D::TL_BOTTOM, "title", "bast scene", 50);
		mControls = new MFW3D::AdvancedRenderControls(mTrayMgr, mCamera);
		setupContent();
		mContentSetup = true;
		mDone = false;
	}
	 void MFW3D_SceneBase::_shutdown()
	{
		MFW3D_Base::_shutdown();
		delete mControls;
		delete mTrayMgr;
		delete mCameraMan;
		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_BILINEAR);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(1);
	}
	 void MFW3D_SceneBase::setupView()
	{
		mCamera = mSceneMgr->createCamera("MainCamera");
		mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mCameraNode->attachObject(mCamera);
		mCameraNode->setFixedYawAxis(true);
		mViewport = mWindow->addViewport(mCamera);
		mCamera->setAspectRatio((Ogre::Real)mViewport->getActualWidth() / (Ogre::Real)mViewport->getActualHeight());
		mCamera->setAutoAspectRatio(true);
		mCamera->setNearClipDistance(5);
		// 设置基础的camera控制器
		mCameraMan = new MFW3D::CameraMan(mCameraNode);  
	}
	 void MFW3D_SceneBase::setDragLook(bool enabled)
	{
		if (enabled)
		{
			mCameraMan->setStyle(MFW3D::CS_MANUAL);
			//mTrayMgr->showCursor();
			mDragLook = true;
		}
		else
		{
			mCameraMan->setStyle(MFW3D::CS_FREELOOK);
			//mTrayMgr->hideCursor();
			mDragLook = false;
		}
	}
}