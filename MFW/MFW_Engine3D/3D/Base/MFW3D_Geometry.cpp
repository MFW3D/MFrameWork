#include "MFW3D_Geometry.h"

namespace MFW3D
{
	double MFW3D_Line3D::GetLength()
	{
		double result = 0.0;
		if (Points.size() <= 0)
			return result;
		auto endItr = Points.end()--;
		for(auto itr=Points.begin();itr!= endItr;itr++)
		{
			
		}
	}
}