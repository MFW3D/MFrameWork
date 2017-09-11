#include "MFW3D_ConfigDialog.h"

namespace MFW3D {
    Ogre::ConfigDialog* getNativeConfigDialog() {
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        static Ogre::ConfigDialog dialog;
        return &dialog;
#else
        return NULL;
#endif
    }
} /* namespace MFW3D */
