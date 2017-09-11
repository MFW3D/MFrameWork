#include "Help.h"

namespace Hydrax
{
	Ogre::Vector2 Math::intersectionOfTwoLines(const Ogre::Vector2 &a, const Ogre::Vector2 &b, 
		const Ogre::Vector2 &c, const Ogre::Vector2 &d)
	{
		float r, s, denominator = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);

		// If the denominator in above is zero, AB & CD are colinear
		if (denominator == 0)
		{
			return Ogre::Vector2::ZERO;
		}

		float numeratorR = (a.y - c.y) * (d.x - c.x) - (a.x - c.x) * (d.y - c.y);
		//  If the numerator above is also zero, AB & CD are collinear.
		//  If they are collinear, then the segments may be projected to the x- 
		//  or y-axis, and overlap of the projected intervals checked.

		r = numeratorR / denominator;

		float numeratorS = (a.y - c.y) * (b.x - a.x) - (a.x - c.x) * (b.y - a.y);

		s = numeratorS / denominator;

		//  If 0<=r<=1 & 0<=s<=1, intersection exists
		//  r<0 or r>1 or s<0 or s>1 line segments do not intersect
		if (r < 0 || r > 1 || s < 0 || s > 1)
		{
			return Ogre::Vector2::ZERO;
		}

		///*
		//    Note:
		//    If the intersection point of the 2 lines are needed (lines in this
		//    context mean infinite lines) regardless whether the two line
		//    segments intersect, then
		//
		//        If r>1, P is located on extension of AB
		//        If r<0, P is located on extension of BA
		//        If s>1, P is located on extension of CD
		//        If s<0, P is located on extension of DC
		//*/

		// Find intersection point
		return Ogre::Vector2((a.x + (r * (b.x - a.x))),
		                   	 (a.y + (r * (b.y - a.y))));
	}
}
