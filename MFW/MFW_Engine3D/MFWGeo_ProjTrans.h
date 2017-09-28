#pragma once
#include "Singleton.h"
#include "proj_api.h"

namespace MFWGeo
{
	class MFW_GeoProjTrans:public MFW::Singleton<MFW_GeoProjTrans>
	{
	public:
		/**
* ������WGS84��������ϵתΪWGS84��γ������
* @param pTransformArg	ת������������ΪNULL��������������Ƿ�����GDAL�ĺ���ָ��
* @param bDstToSrc		TRUEΪ����ת��γ�ȣ�FALSEΪ��γ��ת����
* @param nPointCount	�����
* @param x				X��������
* @param y				Y��������
* @param z				Z��������
* @param panSuccess		ת���������������
* @return �ɹ�ִ�з���ֵΪtrue�����򷵻�ֵΪfalse
*/
		int GeocentLonLatTransform(void *pTransformArg, int bDstToSrc, int nPointCount,
			double *x, double *y, double *z, int *panSuccess);
	};

}