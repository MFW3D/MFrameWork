#pragma once
#include "Singleton.h"
#include "proj_api.h"

namespace MFWGeo
{
	class MFW_GeoProjTrans:public MFW::Singleton<MFW_GeoProjTrans>
	{
	public:
		/**
* 批量将WGS84地心坐标系转为WGS84经纬度坐标
* @param pTransformArg	转换参数，设置为NULL，设置这个参数是方便用GDAL的函数指针
* @param bDstToSrc		TRUE为地心转经纬度，FALSE为经纬度转地心
* @param nPointCount	点个数
* @param x				X坐标序列
* @param y				Y坐标序列
* @param z				Z坐标序列
* @param panSuccess		转换就诶过标记序列
* @return 成功执行返回值为true，否则返回值为false
*/
		int GeocentLonLatTransform(void *pTransformArg, int bDstToSrc, int nPointCount,
			double *x, double *y, double *z, int *panSuccess);
	};

}