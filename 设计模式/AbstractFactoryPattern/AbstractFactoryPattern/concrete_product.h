#pragma once

#include "product.h"

// ����
// ����
class BenzCar :public ICar {
public:
	string Name() 
	{
		return "Benz Car";
	}
};

// ����
class BmwCar :public ICar
{
public:
	string Name()
	{
		return "Bmw Car";
	}
};

 //�µ�
class AudiCar :public ICar
{
public:
	string Name()
	{
		return "Audi Car";
	}
};

// ���г�
class BenzBike :public IBike 
{
public:
	string Name()
	{
		return "Benz Bike";
	}
};

class BmwBike :public IBike
{
public:
	string Name()
	{
		return "Bmw Bike";
	}
};

class AudiBike :public IBike
{
public:
	string Name()
	{
		return "Audi Bike";
	}
};


