#include<iostream>
#include<cstdio>
#include<string>
#include <time.h>
using namespace std;
#define min(x, y) ( x < y ? x : y )
#define max(x, y) ( x > y ? x : y )
#define FLOAT 30

class Bignumber
{
private:
	
	

public:
	int De2int(string number, string *numbernew); //����������С����ȥ����������С��λ��
	int COMPARE(string number1, string number2); //�Ƚ�������С
	void IntandDecimal(string number, string *Intpart, string *Decimalpart); //��һ����ת���������ַ�����������С����������
	string PLUS(string number1, string number2); //�ӷ�
	string MINUS(string number1, string number2); //����
	string MULTIPLY(string number1, string number2); //�˷�
	string DIVIDE(string number1, string number2, int floatpoint = FLOAT); //����
	string MOD(string number1, string number2); //����
};