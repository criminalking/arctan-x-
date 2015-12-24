#include<iostream>
#include<string>
#include <time.h>
using namespace std;
#define min(x, y) ( x < y ? x : y )
#define max(x, y) ( x > y ? x : y )

class Bignumber
{
private:
	int COMPARE(string number1, string number2); //比较两数大小

public:
	string PLUS(string number1, string number2); //加法
	string MINUS(string number1, string number2); //减法
	string MULTIPLY(string number1, string number2); //乘法
	string DIVIDE(string number1, string number2, int floatpoint = 0); //除法
	string MOD(string number1, string number2); //求余
};