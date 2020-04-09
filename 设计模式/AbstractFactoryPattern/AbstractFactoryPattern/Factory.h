#pragma once

#include "product.h"

// ���󹤳�ģʽ
class Factory {
public:
	// ö��
	enum FACTORY_TYPE
	{
		BENZ_FACTORY,
		BMW_FACTORY,
		AUDI_FACTORY
	};

	virtual ICar* CreateCar() = 0; // ��������
	virtual IBike* CreateBike() = 0; //�������г�
	static Factory*CreateFactory(FACTORY_TYPE factory); // ��������

};
