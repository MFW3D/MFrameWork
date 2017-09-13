#pragma once
#include "MFW3D_Input.h"
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
#include <OgreRTShaderSystem.h>
#endif

namespace MFW3D {
class TrayManager;
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
class AdvancedRenderControls : public InputListener {
public:
    AdvancedRenderControls(TrayManager* trayMgr, Ogre::Camera* cam);
    ~AdvancedRenderControls();

    bool keyPressed(const KeyboardEvent& evt);
    void frameRendered(const Ogre::FrameEvent& evt);
protected:
    Ogre::Root* mRoot;
    Ogre::Camera* mCamera;      // main camera
    TrayManager* mTrayMgr;      // tray interface manager
    ParamsPanel* mDetailsPanel; // sample details panel
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
    Ogre::RTShader::ShaderGenerator* mShaderGenerator;
#endif
};
} 

