#include "GPUNormalMapManager.h"

#include "Hydrax.h"

namespace Hydrax
{
	GPUNormalMapManager::GPUNormalMapManager(Hydrax* h)
		: mHydrax(h)
		, mRttManager(h->getRttManager())
		, mCreated(false)
	{
		mRttManager->setBitsPerChannel(RttManager::RTT_GPU_NORMAL_MAP, RttManager::BPC_16);
		mRttManager->setNumberOfChannels(RttManager::RTT_GPU_NORMAL_MAP, RttManager::NOC_3);

		mNormalMapMaterial.setNull();
	}

	GPUNormalMapManager::~GPUNormalMapManager()
	{
		remove();
	}

	void GPUNormalMapManager::create()
	{
		mRttManager->initialize(RttManager::RTT_GPU_NORMAL_MAP);

		mHydrax->getMaterialManager()->reload(MaterialManager::MAT_WATER);

		if (mHydrax->isComponent(HYDRAX_COMPONENT_UNDERWATER))
		{
		    mHydrax->getMaterialManager()->reload(MaterialManager::MAT_UNDERWATER);
		}

		mCreated = true;
	}

	void GPUNormalMapManager::remove()
	{
		if (!mCreated)
		{
			return;
		}

		for (unsigned int k = 0; k < mTextures.size(); k++)
		{
			Ogre::TextureManager::getSingleton().remove(mTextures.at(k)->getName());
		}

		mTextures.clear();

		mRttManager->remove(RttManager::RTT_GPU_NORMAL_MAP);

		Ogre::HighLevelGpuProgramManager::getSingleton().unload(mNormalMapMaterial->getTechnique(0)->getPass(0)->getVertexProgramName());
        Ogre::HighLevelGpuProgramManager::getSingleton().unload(mNormalMapMaterial->getTechnique(0)->getPass(0)->getFragmentProgramName());
		Ogre::HighLevelGpuProgramManager::getSingleton().remove(mNormalMapMaterial->getTechnique(0)->getPass(0)->getVertexProgramName());
        Ogre::HighLevelGpuProgramManager::getSingleton().remove(mNormalMapMaterial->getTechnique(0)->getPass(0)->getFragmentProgramName());

		Ogre::MaterialManager::getSingleton().remove(mNormalMapMaterial->getName());
		mNormalMapMaterial.setNull();
		
		mCreated = false;
	}
}
