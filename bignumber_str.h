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
	int De2int(string number, string *numbernew); //将任意数的小数点去掉，并返回小数位数
	int COMPARE(string number1, string number2); //比较两数大小
	void IntandDecimal(string number, string *Intpart, string *Decimalpart); //将一个数转化成两个字符串（整数、小数）并返回
	string PLUS(string number1, string number2); //加法
	string MINUS(string number1, string number2); //减法
	string MULTIPLY(string number1, string number2); //乘法
	string DIVIDE(string number1, string number2, int floatpoint = FLOAT); //除法
	string MOD(string number1, string number2); //求余
};