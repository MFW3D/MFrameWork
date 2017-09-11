#pragma once
#include "Prerequisites.h"

#include "Enums.h"
#include "Image.h"

namespace Hydrax
{
	class Hydrax;

	/** Class for manager Normal maps.
	 */
	class  TextureManager
	{
	public:
		/** Textures enumeration
		 */
		enum TexturesID
		{
			// Normal map
			TEX_NORMAL_ID = 0
		};

		/** Constructor
		    @param h Hydrax main pointer
		 */
		TextureManager(Hydrax* h);

		/** Destructor
		 */
		~TextureManager();

		/** Create height and normal map textures
		    @param Size Textures's size
		 */
		void create(const Size &Size);

		/** Remove textures
		 */
		void remove();

		/** Update
		    @param Id Texture's ID
			@param Image Update image
			@return false if something fails
			@remarks If you need to update the texture with another way of data,
			         get the Ogre::TexturePtr and modify it directly.
					 Normal image will be Image::Type::TYPE_RGB [0,255] range
		 */
		inline bool update(const TexturesID &Id, Image &Image)
		{
            if (Id == TEX_NORMAL_ID)
			{
				return _updateNormalMap(Image);
			}

			return false;
		}

		/** Get texture
		    @param Id Texture Id ( TEX_NORMAL_ID )
			@return Ogre::TexturePtr
		 */
		inline Ogre::TexturePtr& getTexture(const TexturesID &Id)
		{
			return mTextures[static_cast<int>(Id)];
		}

		/** Get texture's name
		    @param Id Texture Id ( TEX_NORMAL_ID )
			@return Texture's name
		 */
		inline const Ogre::String& getTextureName(const TexturesID &Id) const
		{
			return mTextureNames[static_cast<int>(Id)];
		}

	private:
		/** Create an Ogre::Texture
		    @param Texture Our Ogre::TexturePtr
		    @param Name Texture's name
			@param Size Texture's size
			@return false if there is a problem. 
		 */
		bool _createTexture(Ogre::TexturePtr &Texture, const Ogre::String &Name, const Size &Size);

		/** Get an Ogre::TexturePtr
		    @param Name Texture's name
			@return Our texture
		 */
		Ogre::TexturePtr _getTexture(const Ogre::String &Name);

		/** Update normal map
		    @param Image Update image
			@return false if something fails
			@remarks Image type will be Image::Type::TYPE_RGB
		*/
        bool _updateNormalMap(Image &Image);

		/// Our Ogre::TexturePtr array
        Ogre::TexturePtr mTextures[1];
		/// Our Ogre::String array for store texture's names
		Ogre::String mTextureNames[1];

        /// Have been created already called?
        bool mCreated;

		/// Hydrax main pointer
		Hydrax *mHydrax;
	};
}

