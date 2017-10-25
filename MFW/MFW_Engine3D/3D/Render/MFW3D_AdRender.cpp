﻿#include "MFW3D_AdRender.h"
#include <OgreTextureManager.h>
#include <OgreMaterialManager.h>
#include "../UI/MFW3D_UIMgr.h"

namespace MFW3D {
	MFW3D_AdRender::MFW3D_AdRender(MFW3D_UIMgr* trayMgr, Ogre::Camera* cam)
		: mCamera(cam), mTrayMgr(trayMgr) {
		mRoot = Ogre::Root::getSingletonPtr();

		// create a params panel for displaying sample details
		Ogre::StringVector items;
		items.push_back("cam.pX");
		items.push_back("cam.pY");
		items.push_back("cam.pZ");
		items.push_back("");
		items.push_back("cam.oW");
		items.push_back("cam.oX");
		items.push_back("cam.oY");
		items.push_back("cam.oZ");
		items.push_back("");
		items.push_back("Filtering");
		items.push_back("Poly Mode");

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		items.push_back("RT Shaders");
		items.push_back("Lighting Model");
		items.push_back("Compact Policy");
		items.push_back("Generated VS");
		items.push_back("Generated FS");
#endif

		mDetailsPanel = mTrayMgr->createParamsPanel(TL_NONE, "DetailsPanel", 200, items);
		mDetailsPanel->hide();

		mDetailsPanel->setParamValue(9, "Bilinear");
		mDetailsPanel->setParamValue(10, "Solid");

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		mDetailsPanel->setParamValue(11, "Off");
		if (!mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION)) {
			mDetailsPanel->setParamValue(11, "On");
		}

		mDetailsPanel->setParamValue(12, "Vertex");
		mDetailsPanel->setParamValue(13, "Low");
		mDetailsPanel->setParamValue(14, "0");
		mDetailsPanel->setParamValue(15, "0");
#endif
	}

	MFW3D_AdRender::~MFW3D_AdRender() {
		mTrayMgr->destroyWidget(mDetailsPanel);
	}

	bool MFW3D_AdRender::keyPressed(const KeyboardEvent& evt) {
		if (mTrayMgr->isDialogVisible())
			return true; // don't process any more keys if dialog is up

		int key = evt.keysym.sym;

		if (key == 'f') // toggle visibility of advanced frame stats
		{
			mTrayMgr->toggleAdvancedFrameStats();
		}
		else if (key == 'g') // toggle visibility of even rarer debugging details
		{
			if (mDetailsPanel->getTrayLocation() == TL_NONE) {
				mTrayMgr->moveWidgetToTray(mDetailsPanel, TL_TOPRIGHT, 0);
				mDetailsPanel->show();
			}
			else {
				mTrayMgr->removeWidgetFromTray(mDetailsPanel);
				mDetailsPanel->hide();
			}
		}
		else if (key == 't') // cycle texture filtering mode
		{
			Ogre::String newVal;
			Ogre::TextureFilterOptions tfo;
			unsigned int aniso;

			switch (Ogre::MaterialManager::getSingleton().getDefaultTextureFiltering(Ogre::FT_MAG)) {
			case Ogre::TFO_BILINEAR:
				newVal = "Trilinear";
				tfo = Ogre::TFO_TRILINEAR;
				aniso = 1;
				break;
			case Ogre::TFO_TRILINEAR:
				newVal = "Anisotropic";
				tfo = Ogre::TFO_ANISOTROPIC;
				aniso = 8;
				break;
			case Ogre::TFO_ANISOTROPIC:
				newVal = "None";
				tfo = Ogre::TFO_NONE;
				aniso = 1;
				break;
			default:
				newVal = "Bilinear";
				tfo = Ogre::TFO_BILINEAR;
				aniso = 1;
				break;
			}

			Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
			Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
			mDetailsPanel->setParamValue(9, newVal);
		}
		else if (key == 'r') // cycle polygon rendering mode
		{
			Ogre::String newVal;
			Ogre::PolygonMode pm;

			switch (mCamera->getPolygonMode()) {
			case Ogre::PM_SOLID:
				newVal = "Wireframe";
				pm = Ogre::PM_WIREFRAME;
				break;
			case Ogre::PM_WIREFRAME:
				newVal = "Points";
				pm = Ogre::PM_POINTS;
				break;
			default:
				newVal = "Solid";
				pm = Ogre::PM_SOLID;
				break;
			}

			mCamera->setPolygonMode(pm);
			mDetailsPanel->setParamValue(10, newVal);
		}
		else if (key == SDLK_F5) // refresh all textures
		{
			Ogre::TextureManager::getSingleton().reloadAll();
		}

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
		// Toggle schemes.
		else if (key == SDLK_F2) {
			if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_FIXED_FUNCTION)) {
				Ogre::Viewport* mainVP = mCamera->getViewport();
				const Ogre::String& curMaterialScheme = mainVP->getMaterialScheme();

				if (curMaterialScheme == Ogre::MaterialManager::DEFAULT_SCHEME_NAME) {
					mainVP->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
					mDetailsPanel->setParamValue(11, "On");
				}
				else if (curMaterialScheme == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME) {
					mainVP->setMaterialScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
					mDetailsPanel->setParamValue(11, "Off");
				}
			}
		}
		// Toggles per pixel per light model.
		else if (key == SDLK_F3) {
			static bool usePerPixelLighting = true;

			// Grab the scheme render state.
			Ogre::RTShader::RenderState* schemRenderState =
				mShaderGenerator->getRenderState(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

			// Add per pixel lighting sub render state to the global scheme render state.
			// It will override the default FFP lighting sub render state.
			if (usePerPixelLighting) {
				Ogre::RTShader::SubRenderState* perPixelLightModel =
					mShaderGenerator->createSubRenderState(Ogre::RTShader::PerPixelLighting::Type);

				schemRenderState->addTemplateSubRenderState(perPixelLightModel);
			}

			// Search the per pixel sub render state and remove it.
			else {
				const Ogre::RTShader::SubRenderStateList& subRenderStateList =
					schemRenderState->getTemplateSubRenderStateList();
				Ogre::RTShader::SubRenderStateListConstIterator it = subRenderStateList.begin();
				Ogre::RTShader::SubRenderStateListConstIterator itEnd = subRenderStateList.end();

				for (; it != itEnd; ++it) {
					Ogre::RTShader::SubRenderState* curSubRenderState = *it;

					// This is the per pixel sub render state -> remove it.
					if (curSubRenderState->getType() == Ogre::RTShader::PerPixelLighting::Type) {
						schemRenderState->removeTemplateSubRenderState(*it);
						break;
					}
				}
			}

			// Invalidate the scheme in order to re-generate all shaders based technique related to this
			// scheme.
			mShaderGenerator->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

			// Update UI.
			if (usePerPixelLighting)
				mDetailsPanel->setParamValue(12, "Pixel");
			else
				mDetailsPanel->setParamValue(12, "Vertex");
			usePerPixelLighting = !usePerPixelLighting;
		}

		// Switch vertex shader outputs compaction policy.
		else if (key == SDLK_F4) {
			switch (mShaderGenerator->getVertexShaderOutputsCompactPolicy()) {
			case Ogre::RTShader::VSOCP_LOW:
				mShaderGenerator->setVertexShaderOutputsCompactPolicy(Ogre::RTShader::VSOCP_MEDIUM);
				mDetailsPanel->setParamValue(13, "Medium");
				break;

			case Ogre::RTShader::VSOCP_MEDIUM:
				mShaderGenerator->setVertexShaderOutputsCompactPolicy(Ogre::RTShader::VSOCP_HIGH);
				mDetailsPanel->setParamValue(13, "High");
				break;

			case Ogre::RTShader::VSOCP_HIGH:
				mShaderGenerator->setVertexShaderOutputsCompactPolicy(Ogre::RTShader::VSOCP_LOW);
				mDetailsPanel->setParamValue(13, "Low");
				break;
			}

			// Invalidate the scheme in order to re-generate all shaders based technique related to this
			// scheme.
			mShaderGenerator->invalidateScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
		}
#endif // INCLUDE_RTSHADER_SYSTEM

		return true;
	}

	void MFW3D_AdRender::frameRendered(const Ogre::FrameEvent& evt) {
		if (!mTrayMgr->isDialogVisible() && mDetailsPanel->isVisible())
		{
			double x = mCamera->getDerivedPosition().x;
			double y = mCamera->getDerivedPosition().y;
			double z = mCamera->getDerivedPosition().z;
			MFWGeo::MFW_GeoProjTrans::GetInstance()->GeocentLonLatTransform(NULL, TRUE,1,&x,&y,&z,NULL);
			// if details panel is visible, then update its contents
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(x));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(y));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(z));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
			mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));

#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
			mDetailsPanel->setParamValue(14, Ogre::StringConverter::toString(mShaderGenerator->getVertexShaderCount()));
			mDetailsPanel->setParamValue(15, Ogre::StringConverter::toString(mShaderGenerator->getFragmentShaderCount()));
#endif
		}
	}

} /* namespace MFW3D */
