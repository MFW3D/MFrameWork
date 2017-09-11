#pragma once
#include "MFW3D_SceneBase.h"
#include "MaterialControls.h"
#include "OgreBillboard.h"
#define MINSPEED .150f
#define MOVESPEED 30
#define MAXSPEED 1.800f

#define CONTROLS_PER_PAGE 5
enum OceanMaterial {
	OCEAN1_CG,
	OCEAN1_NATIVE,
	OCEAN2_CG,
	OCEAN2_NATIVE
};

class Scene_Level2 :public MFW3D::MFW3D_SceneBase
{
public:
	Scene_Level2();
protected:
	//Things from the frame listener
	Ogre::Vector3 mTranslateVector;
	int mSceneDetailIndex;
	float mUpdateFreq;
	bool mSpinLight;
	// just to stop toggles flipping too fast
	Ogre::TextureFilterOptions mFiltering;
	int mAniso;

	Ogre::SceneNode*      mMainNode;
	Ogre::Entity*         mOceanSurfaceEnt;

	size_t                mCurrentMaterial;
	size_t                mCurrentPage;
	size_t                mNumPages;
	Ogre::MaterialPtr     mActiveMaterial;
	Ogre::Pass*           mActivePass;
	Ogre::GpuProgramPtr   mActiveFragmentProgram;
	Ogre::GpuProgramPtr   mActiveVertexProgram;
	Ogre::GpuProgramParametersSharedPtr mActiveFragmentParameters;
	Ogre::GpuProgramParametersSharedPtr mActiveVertexParameters;
	Ogre::Real                  mRotateSpeed;
	MFW3D::Slider* mShaderControls[CONTROLS_PER_PAGE];

	ShaderControlsContainer    mShaderControlContainer;
	MaterialControlsContainer mMaterialControlsContainer;

	void setupGUI();
	void setupScene();
	virtual void setupContent();
	virtual void cleanupContent();

	void sliderMoved(MFW3D::Slider* slider);
	void buttonHit(MFW3D::Button* button);
	void checkBoxToggled(MFW3D::CheckBox* box);
	void selectOceanMaterial(OceanMaterial newMaterial);
	void itemSelected(MFW3D::SelectMenu* menu);
	void changePage(int nextPage = -1);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

