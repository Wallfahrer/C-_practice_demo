#pragma once

// ����ӿ�
#include <string>
using std::string;

// �����ӿ�
class ICar {
public:
	virtual string Name() = 0;

};

// ���г��ӿ�
class IBike {
public:
	virtual string Name() = 0;
};

