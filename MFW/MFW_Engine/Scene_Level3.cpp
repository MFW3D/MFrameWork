#include "Scene_Level3.h"
Scene_Level3::Scene_Level3()
	: mTerrainGlobals(0)
	, mTerrainGroup(0)
	, mTerrainPaging(0)
	, mPageManager(0)
	, mFly(false)
	, mFallVelocity(0)
	, mMode(MODE_NORMAL)
	, mLayerEdit(1)
	, mBrushSizeTerrainSpace(0.02)
	, mHeightUpdateCountDown(0)
	, mTerrainPos(1000, 0, 5000)
	, mTerrainsImported(false)

{
	mInfo["Title"] = "Terrain";
	mInfo["Description"] = "Demonstrates use of the terrain rendering plugin.";
	mInfo["Thumbnail"] = "thumb_terrain.png";
	mInfo["Category"] = "Environment";
	mInfo["Help"] = "Left click and drag anywhere in the scene to look around. Let go again to show "
		"cursor and access widgets. Use WASD keys to move. Use +/- keys when in edit mode to change content.";

	// Update terrain at max 20fps
	mHeightUpdateRate = 1.0 / 20.0;
}
void Scene_Level3::testCapabilities(const Ogre::RenderSystemCapabilities* caps)
{
	if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM) || !caps->hasCapability(Ogre::RSC_FRAGMENT_PROGRAM))
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "Your graphics card does not support vertex or fragment shaders, "
			"so you cannot run this sample. Sorry!", "Sample_Terrain::testCapabilities");
	}
}
Ogre::StringVector Scene_Level3::getRequiredPlugins()
{
	Ogre::StringVector names;
	if (!Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles") && !Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		names.push_back("Cg Program Manager");
	return names;
}
void Scene_Level3::doTerrainModify(Ogre::Terrain* terrain, const Ogre::Vector3& centrepos, 
	Ogre::Real timeElapsed)
{
	Ogre::Vector3 tsPos;
	terrain->getTerrainPosition(centrepos, &tsPos);
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS && OGRE_BITES_HAVE_SDL
	const Ogre::uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_EQUALS] || state[SDL_SCANCODE_KP_PLUS] ||
		state[SDL_SCANCODE_KP_MINUS] || state[SDL_SCANCODE_MINUS])
	{
		switch (mMode)
		{
		case MODE_EDIT_HEIGHT:
		{
			// we need point coords
			Ogre::Real terrainSize = (terrain->getSize() - 1);
			long startx = (tsPos.x - mBrushSizeTerrainSpace) * terrainSize;
			long starty = (tsPos.y - mBrushSizeTerrainSpace) * terrainSize;
			long endx = (tsPos.x + mBrushSizeTerrainSpace) * terrainSize;
			long endy = (tsPos.y + mBrushSizeTerrainSpace) * terrainSize;
			startx = std::max(startx, 0L);
			starty = std::max(starty, 0L);
			endx = std::min(endx, (long)terrainSize);
			endy = std::min(endy, (long)terrainSize);
			for (long y = starty; y <= endy; ++y)
			{
				for (long x = startx; x <= endx; ++x)
				{
					Ogre::Real tsXdist = (x / terrainSize) - tsPos.x;
					Ogre::Real tsYdist = (y / terrainSize) - tsPos.y;

					Ogre::Real weight = std::min((Ogre::Real)1.0,
						Ogre::Math::Sqrt(tsYdist * tsYdist + tsXdist * tsXdist) / Ogre::Real(0.5 * mBrushSizeTerrainSpace));
					weight = 1.0 - (weight * weight);

					float addedHeight = weight * 250.0 * timeElapsed;
					float newheight;
					if (state[SDL_SCANCODE_EQUALS] || state[SDL_SCANCODE_KP_PLUS])
						newheight = terrain->getHeightAtPoint(x, y) + addedHeight;
					else
						newheight = terrain->getHeightAtPoint(x, y) - addedHeight;
					terrain->setHeightAtPoint(x, y, newheight);

				}
			}
			if (mHeightUpdateCountDown == 0)
				mHeightUpdateCountDown = mHeightUpdateRate;
		}
		break;
		case MODE_EDIT_BLEND:
		{
			Ogre::TerrainLayerBlendMap* layer = terrain->getLayerBlendMap(mLayerEdit);
			// we need image coords
			Ogre::Real imgSize = terrain->getLayerBlendMapSize();
			long startx = (tsPos.x - mBrushSizeTerrainSpace) * imgSize;
			long starty = (tsPos.y - mBrushSizeTerrainSpace) * imgSize;
			long endx = (tsPos.x + mBrushSizeTerrainSpace) * imgSize;
			long endy = (tsPos.y + mBrushSizeTerrainSpace) * imgSize;
			startx = std::max(startx, 0L);
			starty = std::max(starty, 0L);
			endx = std::min(endx, (long)imgSize);
			endy = std::min(endy, (long)imgSize);
			for (long y = starty; y <= endy; ++y)
			{
				for (long x = startx; x <= endx; ++x)
				{
					Ogre::Real tsXdist = (x / imgSize) - tsPos.x;
					Ogre::Real tsYdist = (y / imgSize) - tsPos.y;

					Ogre::Real weight = std::min((Ogre::Real)1.0,
						Ogre::Math::Sqrt(tsYdist * tsYdist + tsXdist * tsXdist) / Ogre::Real(0.5 * mBrushSizeTerrainSpace));
					weight = 1.0 - (weight * weight);

					float paint = weight * timeElapsed;
					size_t imgY = imgSize - y;
					float val;
					if (state[SDL_SCANCODE_EQUALS] || state[SDL_SCANCODE_KP_PLUS])
						val = layer->getBlendValue(x, imgY) + paint;
					else
						val = layer->getBlendValue(x, imgY) - paint;
					val = Ogre::Math::Clamp(val, 0.0f, 1.0f);
					layer->setBlendValue(x, imgY, val);

				}
			}

			layer->update();
		}
		break;
		case MODE_NORMAL:
		case MODE_COUNT:
			break;
		};
	}
#endif

}
bool Scene_Level3::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mMode != MODE_NORMAL)
	{
		// fire ray
		Ogre::Ray ray;
		//ray = mCamera->getCameraToViewportRay(0.5, 0.5);
		ray = mTrayMgr->getCursorRay(mCamera);

		Ogre::TerrainGroup::RayResult rayResult = mTerrainGroup->rayIntersects(ray);
		if (rayResult.hit)
		{
			mEditMarker->setVisible(true);
			mEditNode->setPosition(rayResult.position);

			// figure out which terrains this affects
			Ogre::TerrainGroup::TerrainList terrainList;
			Ogre::Real brushSizeWorldSpace = TERRAIN_WORLD_SIZE * mBrushSizeTerrainSpace;
			Ogre::Sphere sphere(rayResult.position, brushSizeWorldSpace);
			mTerrainGroup->sphereIntersects(sphere, &terrainList);

			for (Ogre::TerrainGroup::TerrainList::iterator ti = terrainList.begin();
				ti != terrainList.end(); ++ti)
				doTerrainModify(*ti, rayResult.position, evt.timeSinceLastFrame);
		}
		else
		{
			mEditMarker->setVisible(false);
		}
	}

	if (!mFly)
	{
		// clamp to terrain
		Ogre::Vector3 camPos = mCameraNode->getPosition();
		Ogre::Ray ray;
		ray.setOrigin(Ogre::Vector3(camPos.x, mTerrainPos.y + 10000, camPos.z));
		ray.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

		Ogre::TerrainGroup::RayResult rayResult = mTerrainGroup->rayIntersects(ray);
		Ogre::Real distanceAboveTerrain = 50;
		Ogre::Real fallSpeed = 300;
		Ogre::Real newy = camPos.y;
		if (rayResult.hit)
		{
			if (camPos.y > rayResult.position.y + distanceAboveTerrain)
			{
				mFallVelocity += evt.timeSinceLastFrame * 20;
				mFallVelocity = std::min(mFallVelocity, fallSpeed);
				newy = camPos.y - mFallVelocity * evt.timeSinceLastFrame;

			}
			newy = std::max(rayResult.position.y + distanceAboveTerrain, newy);
			mCameraNode->setPosition(camPos.x, newy, camPos.z);

		}

	}

	if (mHeightUpdateCountDown > 0)
	{
		mHeightUpdateCountDown -= evt.timeSinceLastFrame;
		if (mHeightUpdateCountDown <= 0)
		{
			mTerrainGroup->update();
			mHeightUpdateCountDown = 0;

		}
	}

	if (mTerrainGroup->isDerivedDataUpdateInProgress())
	{
		mTrayMgr->moveWidgetToTray(mInfoLabel, MFW3D::TL_TOP, 0);
		mInfoLabel->show();
		if (mTerrainsImported)
		{
			mInfoLabel->setCaption("Building terrain, please wait...");
		}
		else
		{
			mInfoLabel->setCaption("Updating textures, patience...");
		}
	}
	else
	{
		mTrayMgr->removeWidgetFromTray(mInfoLabel);
		mInfoLabel->hide();
		if (mTerrainsImported)
		{
			saveTerrains(true);
			mTerrainsImported = false;
		}
	}

	return MFW3D_SceneBase::frameRenderingQueued(evt);  // don't forget the parent updates!
}
void Scene_Level3::saveTerrains(bool onlyIfModified)
{
	mTerrainGroup->saveAllTerrains(onlyIfModified);
}
bool Scene_Level3::keyPressed(const MFW3D::KeyboardEvent &e)
{
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS
	SDL_Keymod mod = SDL_GetModState();
	switch (e.keysym.sym)
	{
	case 's':
		// CTRL-S to save
		if (mod & KMOD_CTRL)
		{
			saveTerrains(true);
		}
		else
			return MFW3D_SceneBase::keyPressed(e);
		break;
	case SDLK_F10:
		// dump
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while (ti.hasMoreElements())
		{
			Ogre::uint32 tkey = ti.peekNextKey();
			Ogre::TerrainGroup::TerrainSlot* ts = ti.getNext();
			if (ts->instance && ts->instance->isLoaded())
			{
				ts->instance->_dumpTextures("terrain_" + Ogre::StringConverter::toString(tkey), ".png");
			}
		}
	}
	break;
	/*
	case SDLK_F7:
	// change terrain size
	if (mTerrainGroup->getTerrainSize() == 513)
	mTerrainGroup->setTerrainSize(1025);
	else
	mTerrainGroup->setTerrainSize(513);
	break;
	case SDLK_F8:
	// change terrain world size
	if (mTerrainGroup->getTerrainWorldSize() == TERRAIN_WORLD_SIZE)
	mTerrainGroup->setTerrainWorldSize(TERRAIN_WORLD_SIZE * 2);
	else
	mTerrainGroup->setTerrainWorldSize(TERRAIN_WORLD_SIZE);
	break;
	*/
	default:
		return MFW3D_SceneBase::keyPressed(e);
	}
#endif

	return true;
}
void Scene_Level3::itemSelected(MFW3D::SelectMenu* menu)
{
	if (menu == mEditMenu)
	{
		mMode = (Mode)mEditMenu->getSelectionIndex();
	}
	else if (menu == mShadowsMenu)
	{
		mShadowMode = (ShadowMode)mShadowsMenu->getSelectionIndex();
		changeShadows();
	}
}
void Scene_Level3::checkBoxToggled(MFW3D::CheckBox* box)
{
	if (box == mFlyBox)
	{
		mFly = mFlyBox->isChecked();
	}
}
void Scene_Level3::defineTerrain(long x, long y, bool flat )
{
	// if a file is available, use it
	// if not, generate file from import

	// Usually in a real project you'll know whether the compact terrain data is
	// available or not; I'm doing it this way to save distribution size

	if (flat)
	{
		mTerrainGroup->defineTerrain(x, y, 0.0f);
	}
	else
	{
		Ogre::String filename = mTerrainGroup->generateFilename(x, y);
		if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
		{
			mTerrainGroup->defineTerrain(x, y);
		}
		else
		{
			Ogre::Image img;
			getTerrainImage(x % 2 != 0, y % 2 != 0, img);
			mTerrainGroup->defineTerrain(x, y, &img);
			mTerrainsImported = true;
		}
	}
}
void Scene_Level3::getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();
}
void Scene_Level3::initBlendMaps(Ogre::Terrain* terrain)
{
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	Ogre::Real minHeight0 = 70;
	Ogre::Real fadeDist0 = 40;
	Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;
	float* pBlend1 = blendMap1->getBlendPointer();
	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0) / fadeDist0;
			Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);

			val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend1++ = val;


		}
	}
	blendMap0->dirty();
	blendMap1->dirty();
	//blendMap0->loadImage("blendmap1.png", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	blendMap0->update();
	blendMap1->update();

	// set up a colour map
	/*
	if (!terrain->getGlobalColourMapEnabled())
	{
	terrain->setGlobalColourMapEnabled(true);
	Image colourMap;
	colourMap.load("testcolourmap.jpg", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	terrain->getGlobalColourMap()->loadImage(colourMap);
	}
	*/
}
void Scene_Level3::configureTerrainDefaults(Ogre::Light* l)
{
	// Configure global
	mTerrainGlobals->setMaxPixelError(8);
	// testing composite map
	mTerrainGlobals->setCompositeMapDistance(3000);
	//mTerrainGlobals->setUseRayBoxDistanceCalculation(true);
	//mTerrainGlobals->getDefaultMaterialGenerator()->setDebugLevel(1);
	//mTerrainGlobals->setLightMapSize(256);

	// Disable the lightmap for OpenGL ES 2.0. The minimum number of samplers allowed is 8(as opposed to 16 on desktop).
	// Otherwise we will run over the limit by just one. The minimum was raised to 16 in GL ES 3.0.
	if (Ogre::Root::getSingletonPtr()->getRenderSystem()->getCapabilities()->getNumTextureUnits() < 9)
	{
		Ogre::TerrainMaterialGeneratorA::SM2Profile* matProfile =
			static_cast<Ogre::TerrainMaterialGeneratorA::SM2Profile*>(mTerrainGlobals->getDefaultMaterialGenerator()->getActiveProfile());
		matProfile->setLightmapEnabled(false);
	}

	// Important to set these so that the terrain knows what to use for derived (non-realtime) data
	mTerrainGlobals->setLightMapDirection(l->getDerivedDirection());
	mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
	//mTerrainGlobals->setCompositeMapAmbient(ColourValue::Red);
	mTerrainGlobals->setCompositeMapDiffuse(l->getDiffuseColour());

	// Configure default import settings for if we use imported image
	Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = TERRAIN_SIZE;
	defaultimp.worldSize = TERRAIN_WORLD_SIZE;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;
	// textures
	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
	defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
	defaultimp.layerList[1].worldSize = 30;
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
	defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
	defaultimp.layerList[2].worldSize = 200;
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
}
void Scene_Level3::addTextureDebugOverlay(MFW3D::TrayLocation loc, Ogre::TexturePtr tex, size_t i)
{
	addTextureDebugOverlay(loc, tex->getName(), i);
}
void Scene_Level3::addTextureDebugOverlay(MFW3D::TrayLocation loc, const Ogre::String& texname, size_t i)
{
	// Create material
	Ogre::String matName = "Ogre/DebugTexture" + Ogre::StringConverter::toString(i);
	Ogre::MaterialPtr debugMat = Ogre::MaterialManager::getSingleton().getByName(matName);
	if (!debugMat)
	{
		debugMat = Ogre::MaterialManager::getSingleton().create(matName,
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}
	Ogre::Pass* p = debugMat->getTechnique(0)->getPass(0);
	p->removeAllTextureUnitStates();
	p->setLightingEnabled(false);
	Ogre::TextureUnitState *t = p->createTextureUnitState(texname);
	t->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);

	// create template
	if (!Ogre::OverlayManager::getSingleton().hasOverlayElement("Ogre/DebugTexOverlay", true))
	{
		Ogre::OverlayElement* e = Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "Ogre/DebugTexOverlay", true);
		e->setMetricsMode(Ogre::GMM_PIXELS);
		e->setWidth(128);
		e->setHeight(128);
	}

	// add widget
	Ogre::String widgetName = "DebugTex" + Ogre::StringConverter::toString(i);
	MFW3D::Widget* w = mTrayMgr->getWidget(widgetName);
	if (!w)
	{
		w = mTrayMgr->createDecorWidget(loc, widgetName, "Ogre/DebugTexOverlay");
	}
	w->getOverlayElement()->setMaterialName(matName);
}
void Scene_Level3::addTextureShadowDebugOverlay(MFW3D::TrayLocation loc, size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		Ogre::TexturePtr shadowTex = mSceneMgr->getShadowTexture(i);
		addTextureDebugOverlay(loc, shadowTex, i);
	}
}
Ogre::MaterialPtr Scene_Level3::buildDepthShadowMaterial(const Ogre::String& textureName)
{
	Ogre::String matName = "DepthShadows/" + textureName;

	Ogre::MaterialPtr ret = Ogre::MaterialManager::getSingleton().getByName(matName);
	if (!ret)
	{
		Ogre::MaterialPtr baseMat = Ogre::MaterialManager::getSingleton().getByName("Ogre/shadow/depth/integrated/pssm");
		ret = baseMat->clone(matName);
		Ogre::Pass* p = ret->getTechnique(0)->getPass(0);
		p->getTextureUnitState("diffuse")->setTextureName(textureName);

		Ogre::Vector4 splitPoints;
		const Ogre::PSSMShadowCameraSetup::SplitPointList& splitPointList =
			static_cast<Ogre::PSSMShadowCameraSetup*>(mPSSMSetup.get())->getSplitPoints();
		for (int i = 0; i < 3; ++i)
		{
			splitPoints[i] = splitPointList[i];
		}
		p->getFragmentProgramParameters()->setNamedConstant("pssmSplitPoints", splitPoints);
	}

	return ret;
}
void Scene_Level3::changeShadows()
{
	configureShadows(mShadowMode != SHADOWS_NONE, mShadowMode == SHADOWS_DEPTH);
}
void Scene_Level3::configureShadows(bool enabled, bool depthShadows)
{
	Ogre::TerrainMaterialGeneratorA::SM2Profile* matProfile =
		static_cast<Ogre::TerrainMaterialGeneratorA::SM2Profile*>(mTerrainGlobals->getDefaultMaterialGenerator()->getActiveProfile());
	matProfile->setReceiveDynamicShadowsEnabled(enabled);
#ifdef SHADOWS_IN_LOW_LOD_MATERIAL
	matProfile->setReceiveDynamicShadowsLowLod(true);
#else
	matProfile->setReceiveDynamicShadowsLowLod(false);
#endif

	// Default materials
	for (EntityList::iterator i = mHouseList.begin(); i != mHouseList.end(); ++i)
	{
		(*i)->setMaterialName("Examples/TudorHouse");
	}

	if (enabled)
	{
		// General scene setup
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
		mSceneMgr->setShadowFarDistance(3000);

		// 3 textures per directional light (PSSM)
		mSceneMgr->setShadowTextureCountPerLightType(Ogre::Light::LT_DIRECTIONAL, 3);

		if (!mPSSMSetup)
		{
			// shadow camera setup
			Ogre::PSSMShadowCameraSetup* pssmSetup = new Ogre::PSSMShadowCameraSetup();
			pssmSetup->setSplitPadding(mCamera->getNearClipDistance());
			pssmSetup->calculateSplitPoints(3, mCamera->getNearClipDistance(), mSceneMgr->getShadowFarDistance());
			pssmSetup->setOptimalAdjustFactor(0, 2);
			pssmSetup->setOptimalAdjustFactor(1, 1);
			pssmSetup->setOptimalAdjustFactor(2, 0.5);

			mPSSMSetup.reset(pssmSetup);
		}
		mSceneMgr->setShadowCameraSetup(mPSSMSetup);

		if (depthShadows)
		{
			mSceneMgr->setShadowTextureCount(3);
			mSceneMgr->setShadowTextureConfig(0, 2048, 2048, Ogre::PF_FLOAT32_R);
			mSceneMgr->setShadowTextureConfig(1, 1024, 1024, Ogre::PF_FLOAT32_R);
			mSceneMgr->setShadowTextureConfig(2, 1024, 1024, Ogre::PF_FLOAT32_R);
			mSceneMgr->setShadowTextureSelfShadow(true);
			mSceneMgr->setShadowCasterRenderBackFaces(true);

			Ogre::MaterialPtr houseMat = buildDepthShadowMaterial("fw12b.jpg");
			for (EntityList::iterator i = mHouseList.begin(); i != mHouseList.end(); ++i)
			{
				(*i)->setMaterial(houseMat);
			}
		}
		else
		{
			mSceneMgr->setShadowTextureCount(3);
			mSceneMgr->setShadowTextureConfig(0, 2048, 2048, Ogre::PF_X8B8G8R8);
			mSceneMgr->setShadowTextureConfig(1, 1024, 1024, Ogre::PF_X8B8G8R8);
			mSceneMgr->setShadowTextureConfig(2, 1024, 1024, Ogre::PF_X8B8G8R8);
			mSceneMgr->setShadowTextureSelfShadow(false);
			mSceneMgr->setShadowCasterRenderBackFaces(false);
			mSceneMgr->setShadowTextureCasterMaterial(Ogre::BLANKSTRING);
		}

		matProfile->setReceiveDynamicShadowsDepth(depthShadows);
		matProfile->setReceiveDynamicShadowsPSSM(static_cast<Ogre::PSSMShadowCameraSetup*>(mPSSMSetup.get()));

		//addTextureShadowDebugOverlay(TL_RIGHT, 3);
	}
	else
	{
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	}


}
void Scene_Level3::setupView()
{
	MFW3D_SceneBase::setupView();

	mCameraNode->setPosition(mTerrainPos + Ogre::Vector3(1683, 50, 2116));
	mCameraNode->lookAt(Ogre::Vector3(1963, 50, 1660), Ogre::Node::TS_PARENT);
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);

	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
	{
		mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
	}
}
void Scene_Level3::setupControls()
{
	mTrayMgr->showCursor();

	// make room for the controls
	mTrayMgr->showLogo(MFW3D::TL_TOPRIGHT);
	mTrayMgr->showFrameStats(MFW3D::TL_TOPRIGHT);
	mTrayMgr->toggleAdvancedFrameStats();

	mInfoLabel = mTrayMgr->createLabel(MFW3D::TL_TOP, "TInfo", "", 350);

	mEditMenu = mTrayMgr->createLongSelectMenu(MFW3D::TL_BOTTOM, "EditMode", "Edit Mode", 370, 250, 3);
	mEditMenu->addItem("None");
	mEditMenu->addItem("Elevation");
	mEditMenu->addItem("Blend");
	mEditMenu->selectItem(0);  // no edit mode

	mFlyBox = mTrayMgr->createCheckBox(MFW3D::TL_BOTTOM, "Fly", "Fly");
	mFlyBox->setChecked(false, false);

	mShadowsMenu = mTrayMgr->createLongSelectMenu(MFW3D::TL_BOTTOM, "Shadows", "Shadows", 370, 250, 3);
	mShadowsMenu->addItem("None");
	mShadowsMenu->addItem("Colour Shadows");
	mShadowsMenu->addItem("Depth Shadows");
	mShadowsMenu->selectItem(0);  // no edit mode

								  // a friendly reminder
	Ogre::StringVector names;
	names.push_back("Help");
	mTrayMgr->createParamsPanel(MFW3D::TL_TOPLEFT, "Help", 100, names)->setParamValue(0, "H/F1");
}
void Scene_Level3::setupContent()
{
	bool blankTerrain = false;
	//blankTerrain = true;

	if (!Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("Terrain"))
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup("Terrain");

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	// Bugfix for D3D11 Render System because of pixel format incompatibility when using
	// vertex compression
	if (Ogre::Root::getSingleton().getRenderSystem()->getName() == "Direct3D11 Rendering Subsystem")
		mTerrainGlobals->setUseVertexCompressionWhenAvailable(false);

	mEditMarker = mSceneMgr->createEntity("editMarker", "sphere.mesh");
	mEditNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mEditNode->attachObject(mEditMarker);
	mEditNode->setScale(0.05, 0.05, 0.05);

	setupControls();

	mCameraMan->setTopSpeed(50);

	setDragLook(true);

	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

	mSceneMgr->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.7, 0.7, 0.8), 0, 10000, 25000);

	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_BOREME);

	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	Ogre::Light* l = mSceneMgr->createLight("tstLight");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(lightdir);
	l->setDiffuseColour(Ogre::ColourValue::White);
	l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(Ogre::TERRAIN_FILE_PREFIX, Ogre::TERRAIN_FILE_SUFFIX);
	mTerrainGroup->setOrigin(mTerrainPos);
	mTerrainGroup->setResourceGroup("Terrain");

	configureTerrainDefaults(l);
#ifdef PAGING
	// Paging setup
	mPageManager = OGRE_NEW PageManager();
	// Since we're not loading any pages from .page files, we need a way just
	// to say we've loaded them without them actually being loaded
	mPageManager->setPageProvider(&mDummyPageProvider);
	mPageManager->addCamera(mCamera);
	mTerrainPaging = OGRE_NEW TerrainPaging(mPageManager);
	PagedWorld* world = mPageManager->createWorld();
	mTerrainPaging->createWorldSection(world, mTerrainGroup, 2000, 3000,
		TERRAIN_PAGE_MIN_X, TERRAIN_PAGE_MIN_Y,
		TERRAIN_PAGE_MAX_X, TERRAIN_PAGE_MAX_Y);
#else
	for (long x = TERRAIN_PAGE_MIN_X; x <= TERRAIN_PAGE_MAX_X; ++x)
		for (long y = TERRAIN_PAGE_MIN_Y; y <= TERRAIN_PAGE_MAX_Y; ++y)
			defineTerrain(x, y, blankTerrain);
	// sync load since we want everything in place when we start
	mTerrainGroup->loadAllTerrains(true);
#endif

	if (mTerrainsImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
		while (ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;
			initBlendMaps(t);
		}
	}

	mTerrainGroup->freeTemporaryResources();

	// create a few entities on the terrain
	Ogre::Entity* e = mSceneMgr->createEntity("tudorhouse.mesh");
	Ogre::Vector3 entPos(mTerrainPos.x + 2043, 0, mTerrainPos.z + 1715);
	Ogre::Quaternion rot;
	entPos.y = mTerrainGroup->getHeightAtWorldPosition(entPos) + 65.5 + mTerrainPos.y;
	rot.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(-180, 180)), Ogre::Vector3::UNIT_Y);
	Ogre::SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode(entPos, rot);
	sn->setScale(Ogre::Vector3(0.12, 0.12, 0.12));
	sn->attachObject(e);
	mHouseList.push_back(e);

	e = mSceneMgr->createEntity("tudorhouse.mesh");
	entPos = Ogre::Vector3(mTerrainPos.x + 1850, 0, mTerrainPos.z + 1478);
	entPos.y = mTerrainGroup->getHeightAtWorldPosition(entPos) + 65.5 + mTerrainPos.y;
	rot.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(-180, 180)), Ogre::Vector3::UNIT_Y);
	sn = mSceneMgr->getRootSceneNode()->createChildSceneNode(entPos, rot);
	sn->setScale(Ogre::Vector3(0.12, 0.12, 0.12));
	sn->attachObject(e);
	mHouseList.push_back(e);

	e = mSceneMgr->createEntity("tudorhouse.mesh");
	entPos = Ogre::Vector3(mTerrainPos.x + 1970, 0, mTerrainPos.z + 2180);
	entPos.y = mTerrainGroup->getHeightAtWorldPosition(entPos) + 65.5 + mTerrainPos.y;
	rot.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(-180, 180)), Ogre::Vector3::UNIT_Y);
	sn = mSceneMgr->getRootSceneNode()->createChildSceneNode(entPos, rot);
	sn->setScale(Ogre::Vector3(0.12, 0.12, 0.12));
	sn->attachObject(e);
	mHouseList.push_back(e);

	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");


}
void Scene_Level3::_shutdown()
{
	if (mTerrainPaging)
	{
		OGRE_DELETE mTerrainPaging;
		mTerrainPaging = 0;
		OGRE_DELETE mPageManager;
		mPageManager = 0;
	}
	else if (mTerrainGroup)
	{
		OGRE_DELETE mTerrainGroup;
		mTerrainGroup = 0;
	}

	if (mTerrainGlobals)
	{
		OGRE_DELETE mTerrainGlobals;
		mTerrainGlobals = 0;
	}

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Terrain");

	mHouseList.clear();

	MFW3D_SceneBase::_shutdown();
}

