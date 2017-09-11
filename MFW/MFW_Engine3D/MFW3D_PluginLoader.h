#pragma once
#include "OgreBitesPrerequisites.h"
#include "OgrePrerequisites.h"

namespace MFW3D
{
    class  MFW3D_PluginLoader {
        std::vector<Ogre::Plugin*> mPlugins;

    public:
        /** Load all the enabled plugins */
        void load();

        void unload();
    };
}
