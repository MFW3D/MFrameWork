#include "MFWGeo_ProjTrans.h"
namespace MFWGeo
{
	int MFW_GeoProjTrans::GeocentLonLatTransform(void *pTransformArg, int bDstToSrc, int nPointCount,
		double *x, double *y, double *z, int *panSuccess)
	{
		if (panSuccess != NULL)
			memset(panSuccess, false, nPointCount);

		// 地心坐标系
		const char* geoccs = "+proj=geocent +datum=WGS84";
		// 经纬度，WGS84基准
		const char* latlon = "+proj=latlong +datum=WGS84";

		projPJ pjGeoccs, pjLatlon;
		//初始化当前投影对象
		if (!(pjGeoccs = pj_init_plus(geoccs)))
			return false;
		if (!(pjLatlon = pj_init_plus(latlon)))
			return false;

		if (bDstToSrc)
		{
			int iRev = pj_transform(pjGeoccs, pjLatlon, nPointCount, 1, x, y, z);
			if (iRev != 0)
				return false;

			for (int i = 0; i < nPointCount; i++)
			{
				//弧度转度
				x[i] *= RAD_TO_DEG;
				y[i] *= RAD_TO_DEG;
			}
		}
		else
		{
			for (int i = 0; i < nPointCount; i++)
			{
				//度转弧度
				x[i] *= DEG_TO_RAD;
				y[i] *= DEG_TO_RAD;
			}

			int iRev = pj_transform(pjLatlon, pjGeoccs, nPointCount, 1, x, y, z);
			if (iRev != 0)
				return false;
		}

		pj_free(pjGeoccs);
		pj_free(pjLatlon);

		return true;
	}

}