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
	void IntandDecimal(string number, string *Intpart, string *Decimalpart); //��һ����ת���������ַ�����������С����������
	int De2int(string number, string *numbernew); //����������С����ȥ����������С��λ��

public:
	int COMPARE(string number1, string number2); //�Ƚ�������С
	string PLUS(string number1, string number2); //�ӷ�
	string MINUS(string number1, string number2); //����
	string MINUS2(string number1, string number2); //������������
	string MULTIPLY(string number1, string number2); //�˷���Ĭ�Ϸ���FLOATλ��
	string DIVIDE(string number1, string number2, int floatpoint = FLOAT); //������Ĭ�Ϸ���FLOATλ��
	string MOD(string number1, string number2); //����
	string POW(string x, int k); //����
};