#pragma once
// ��ϰһ������
#include <iostream>
using namespace std;

class Box {
public:
	Box() {
		hour = 0;
	}

	// ��ȡ �� ���� get set
	double getVolume(void) 
	{
		return length * height*breadth;
	}
	void setLength(double len) {
		length = len;
	}
	void setBreadth(double bre) {
		breadth = bre;
	}
	void setHeight(double hei) {
		height = hei;
	}
	
	// ��дһ�����ط��� + ���������
	Box operator+(const Box& b) 
	{
		Box box;
		box.length = b.length + this->length;
		box.breadth = b.breadth + this->breadth;
		box.height = b.height + this->height;
		return box;
	}

	// ��ϵ�������� <>=
	bool operator <(const Box& b) 
	{
		if (length < b.length) {
			return true;
		}
		else {
			return false;
		}
	}

	// ��ֵ���������
	void operator=(const Box&b) {
		length = b.length;
		height = b.height;
		breadth = b.breadth;
	}

	void print() 
	{
		cout << "length:" << length << endl;
	}

	

private:
	double length;
	double breadth;
	double height;
	int hour;
};

class Time {
private:
	int hours;
	int min;
public:
	Time() 
	{
		hours = 0;
		min = 0;
	}
	Time(int h,int m) 
	{
		hours = h;
		min = m;
	}
	// ��ʾʱ��
	void displayTime()
	{
		cout << "H: " << hours << " M:" << min << endl;
	}
	// ���� ǰ��++
	Time operator++()
	{
		++min;
		if (min >= 60) 
		{
			hours++;
			min -= 60;
		}
		return Time(hours, min);
		// ����д��
		/*Time t;
		t.hours = ++hours;
		return t;*/
	}
	// ����++ int �����ʾ���Ǻ�׺ʽ�ӵ���˼
	Time operator++(int)
	{
		Time t(hours, min);
		min++;
		if (min >= 60) {
			++hours;
			min -= 60;
		}
		// ����ԭʼֵ��������һ��ֵ�Ѿ��ı�
		return t;
	}

	
};



