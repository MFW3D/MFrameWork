#pragma once

#include "OgreBitesPrerequisites.h"
#include "OgreConfigDialog.h"

namespace MFW3D {

    /**
     * get an platform native  dialog instance.
     * @return pointer to Ogre::ConfigDialog or NULL if not available on the current platform.
     */
     Ogre::ConfigDialog* getNativeConfigDialog();

} /* namespace MFW3D */
