#pragma once

#include "Prerequisites.h"
#include "GPUNormalMapManager.h"

namespace Hydrax{ namespace Noise
{
	/** Base noise class, 
	    Override it for create different ways of create water noise.
	 */
	class  Noise
	{
	public:
		/** Constructor
		    @param Name Noise name
			@param GPUNormalMapSupported Is GPU normal map generation supported?
		 */
		Noise(const Ogre::String &Name, const bool& GPUNormalMapSupported);

		/** Destructor
		 */
		virtual ~Noise();

		/** Create
		 */
		virtual void create();

		/** Remove
		 */
		virtual void remove();

		/** Create GPUNormalMap resources
		    @param g GPUNormalMapManager pointer
			@return true if it needs to be created, false if not
		 */
		virtual bool createGPUNormalMapResources(GPUNormalMapManager *g);

		/** Remove GPUNormalMap resources
		    @param g GPUNormalMapManager pointer
		 */
		virtual void removeGPUNormalMapResources(GPUNormalMapManager *g);

		/** Call it each frame
		    @param timeSinceLastFrame Time since last frame(delta)
		 */
		virtual void update(const Ogre::Real &timeSinceLastFrame) = 0;

		/** Save config
		    @param Data String reference 
		 */
		virtual void saveCfg(Ogre::String &Data);

		/** Load config
		    @param CgfFile Ogre::ConfigFile reference 
			@return True if is the correct noise config
		 */
		virtual bool loadCfg(Ogre::ConfigFile &CfgFile);

		/** Get noise name
		    @return Noise name
		 */
		inline const Ogre::String& getName() const
		{
			return mName;
		}

		/** Is created() called?
		    @return true if create() have been already called
		 */
		inline const bool& isCreated() const
		{
			return mCreated;
		}

		/** Is GPU Normal map generation supported
		    @return true if yes, false if not
		 */
		inline const bool& isGPUNormalMapSupported() const
		{
			return mGPUNormalMapSupported;
		}

		/** Are GPU normal map resources created?
		    @return true if yes, false if not
		 */
		inline const bool& areGPUNormalMapResourcesCreated() const
		{
			return mGPUNormalMapResourcesCreated;
		}
	
		/** Get the especified x/y noise value
		    @param x X Coord
			@param y Y Coord
			@return Noise value
		 */
		virtual float getValue(const float &x, const float &y) = 0;

	protected:
		/// Module name
		Ogre::String mName;
		/// Has create() been already called?
		bool mCreated;

		/// Is GPU normal map generation supported?
        bool mGPUNormalMapSupported;
		/// Are GPU normal map resources created?
		bool mGPUNormalMapResourcesCreated;
	};
}}

