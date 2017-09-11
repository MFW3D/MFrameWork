#pragma once
#include "MFW3D_SceneBase.h"
#include "MaterialControls.h"
#include "OgreBillboard.h"
#define TERRAIN_PAGE_MIN_X 0
#define TERRAIN_PAGE_MIN_Y 0
#define TERRAIN_PAGE_MAX_X 0
#define TERRAIN_PAGE_MAX_Y 0

#include "OgrePageManager.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

#define TERRAIN_FILE_PREFIX String("testTerrain")
#define TERRAIN_FILE_SUFFIX String("dat")
#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_SIZE 513

class Scene_Level3 :public MFW3D::MFW3D_SceneBase
{
public:

	Scene_Level3();

	void testCapabilities(const Ogre::RenderSystemCapabilities* caps);

	Ogre::StringVector getRequiredPlugins();

	void doTerrainModify(Ogre::Terrain* terrain, const Ogre::Vector3& centrepos, Ogre::Real timeElapsed);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void saveTerrains(bool onlyIfModified);

	bool keyPressed(const MFW3D::KeyboardEvent &e);

	void itemSelected(MFW3D::SelectMenu* menu);

	void checkBoxToggled(MFW3D::CheckBox* box);

protected:

	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::TerrainGroup* mTerrainGroup;
	bool mPaging;
	Ogre::TerrainPaging* mTerrainPaging;
	Ogre::PageManager* mPageManager;
#ifdef PAGING
	/// This class just pretends to provide prcedural page content to avoid page loading
	class DummyPageProvider : public PageProvider
	{
	public:
		bool prepareProceduralPage(Page* page, PagedWorldSection* section) { return true; }
		bool loadProceduralPage(Page* page, PagedWorldSection* section) { return true; }
		bool unloadProceduralPage(Page* page, PagedWorldSection* section) { return true; }
		bool unprepareProceduralPage(Page* page, PagedWorldSection* section) { return true; }
	};
	DummyPageProvider mDummyPageProvider;
#endif
	bool mFly;
	Ogre::Real mFallVelocity;
	enum Mode
	{
		MODE_NORMAL = 0,
		MODE_EDIT_HEIGHT = 1,
		MODE_EDIT_BLEND = 2,
		MODE_COUNT = 3
	};
	enum ShadowMode
	{
		SHADOWS_NONE = 0,
		SHADOWS_COLOUR = 1,
		SHADOWS_DEPTH = 2,
		SHADOWS_COUNT = 3
	};
	Mode mMode;
	ShadowMode mShadowMode;
	Ogre::uint8 mLayerEdit;
	Ogre::Real mBrushSizeTerrainSpace;
	Ogre::SceneNode* mEditNode;
	Ogre::Entity* mEditMarker;
	Ogre::Real mHeightUpdateCountDown;
	Ogre::Real mHeightUpdateRate;
	Ogre::Vector3 mTerrainPos;
	MFW3D::SelectMenu* mEditMenu;
	MFW3D::SelectMenu* mShadowsMenu;
	MFW3D::CheckBox* mFlyBox;
	MFW3D::Label* mInfoLabel;
	bool mTerrainsImported;
	Ogre::ShadowCameraSetupPtr mPSSMSetup;

	typedef std::list<Ogre::Entity*> EntityList;
	EntityList mHouseList;

	void defineTerrain(long x, long y, bool flat = false);

	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);

	void initBlendMaps(Ogre::Terrain* terrain);

	void configureTerrainDefaults(Ogre::Light* l);

	void addTextureDebugOverlay(MFW3D::TrayLocation loc, Ogre::TexturePtr tex, size_t i);
	void addTextureDebugOverlay(MFW3D::TrayLocation loc, const Ogre::String& texname, size_t i);

	void addTextureShadowDebugOverlay(MFW3D::TrayLocation loc, size_t num);

	Ogre::MaterialPtr buildDepthShadowMaterial(const Ogre::String& textureName);

	void changeShadows();

	void configureShadows(bool enabled, bool depthShadows);

	/*-----------------------------------------------------------------------------
	| Extends setupView to change some initial camera settings for this sample.
	-----------------------------------------------------------------------------*/
	void setupView();

	void setupControls();

	void setupContent();

	void _shutdown();
};

