#pragma once

#include "Prerequisites.h"

namespace Hydrax
{
    /** Struct wich contains an especific width and height value
    */
    struct  Size
    {
        /// Width value
        int Width;
        /// Height value
        int Height;

        /** Default constructor
        */
        Size()
        {
            Width  = 0;
            Height = 0;
        }

        /** Constructor
        	@param size The width and height values
        */
        Size(const int &size)
        {
            Width  = size;
            Height = size;
        }

        /** Constructor
        	@param width Width value
        	@param height Height value
        */
        Size(const int &width, const int &height)
        {
            Width  = width;
            Height = height;
        }

        /** Destructor
        */
        ~Size()
        {
        }

        /** Sets the same width and height value
        	@param size The width and height values
        */
        void setSize(const int &size)
        {
            Width  = size;
            Height = size;
        }

        /** Sets the especified values
        	@param width Width value
        	@param height Height value
        */
        void setSize(const int &width, const int &height)
        {
            Width  = width;
            Height = height;
        }
    };

	/** Math class with some help funtions
	 */
	class Math
	{
	public:
		/** Constructor
		 */
		Math(){};
		/** Destructor
		 */
		~Math(){};

		/** Find the intersection point of two lines
		    @param a First line origin
			@param b First line final
			@param c First line origin
			@param d First line final
			@return Ogre::Vector2::ZERO if there isn't intersection, intersection point
		 */
		static Ogre::Vector2 intersectionOfTwoLines(const Ogre::Vector2 &a, const Ogre::Vector2 &b, 
			                                        const Ogre::Vector2 &c, const Ogre::Vector2 &d);
	};
}
