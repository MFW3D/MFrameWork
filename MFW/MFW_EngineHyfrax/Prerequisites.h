#pragma once

/// Include external headers
#include <Ogre.h>
/// Log macro
#define HydraxLOG(msg) Ogre::LogManager::getSingleton().logMessage("[Hydrax] " + Ogre::String(msg));

/// Hydrax defines
#define HYDRAX_VERSION_MAJOR 0
#define HYDRAX_VERSION_MINOR 5
#define HYDRAX_VERSION_PATCH 4

#define HYDRAX_RESOURCE_GROUP "Hydrax"

#define HYDRAX_IMAGE_CHECK_PIXELS 0 // See Image.cpp, 1 = Check pixels / 0 = No check pixels
                                    // Use it for debug mode only

// Windows math library backport
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


