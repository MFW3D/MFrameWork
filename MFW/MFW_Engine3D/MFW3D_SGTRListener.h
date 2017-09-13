#pragma once
#include "OgreBitesPrerequisites.h"
#include <OgreRTShaderSystem.h>
#include <OgreMaterialManager.h>

namespace MFW3D {
class  MFW3D_SGTRListener : public Ogre::MaterialManager::Listener {
public:
    explicit MFW3D_SGTRListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);
    Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
                                          const Ogre::String& schemeName,
                                          Ogre::Material* originalMaterial, unsigned short lodIndex,
                                          const Ogre::Renderable* rend);
    bool afterIlluminationPassesCreated(Ogre::Technique* tech);
    bool beforeIlluminationPassesCleared(Ogre::Technique* tech);
protected:
    Ogre::RTShader::ShaderGenerator* mShaderGenerator; // The shader generator instance.
};
}
