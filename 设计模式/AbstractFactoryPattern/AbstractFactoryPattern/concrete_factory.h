#pragma once
// ����ģʽ 

#include "Factory.h"
#include "concrete_product.h"

// ���۹���
class BenzFactory :public Factory 
{
public:
	ICar* CreateCar()
	{
		return new BenzCar();
	}
	IBike* CreateBike()
	{
		return new BenzBike();
	}
};

// ������
class BmwFactory :public Factory
{
public:
	ICar* CreateCar()
	{
		return new BmwCar();
	}
	IBike* CreateBike()
	{
		return new BmwBike();
	}
};

// �µϹ���
class AudiFactory :public Factory
{
public:
	ICar* CreateCar()
	{
		return new AudiCar();
	}
	IBike* CreateBike()
	{
		return new AudiBike();
	}
};




