#pragma once
#include "MFW3D_Input.h"
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#include <OgreRTShaderSystem.h>
#endif
#include "MFWGeo_ProjTrans.h"

namespace MFW3D {
class MFW3D_UIMgr;
class ParamsPanel;
/**
   - F:        Toggle frame rate stats on/off
   - G:        Toggle advanced frame stats on/off
   - R:        Render mode
               - Wireframe
               - Points
               - Solid
   - T:        Cycle texture filtering
               - Bilinear
               - Trilinear
               - Anisotropic(8)
               - None
   - F2:       Set the main viewport material scheme to default material manager scheme.
   - F3:       Toggle default shader generator lighting model from per vertex to per pixel.
   - F4:       Switch vertex shader outputs compaction policy.
 */
class MFW3D_AdRender : public MFW3D_InputListener {
public:
    MFW3D_AdRender(MFW3D_UIMgr* trayMgr, Ogre::Camera* cam);
    ~MFW3D_AdRender();

    bool keyPressed(const KeyboardEvent& evt);
    void frameRendered(const Ogre::FrameEvent& evt);
protected:
    Ogre::Root* mRoot;
    Ogre::Camera* mCamera;      // main camera
    MFW3D_UIMgr* mTrayMgr;      // tray interface manager
    ParamsPanel* mDetailsPanel; // sample details panel
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
    Ogre::RTShader::ShaderGenerator* mShaderGenerator;
#endif
};
} 

