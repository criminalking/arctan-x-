#include<iostream>
#include<string>
#include <time.h>
using namespace std;
#define min(x, y) ( x < y ? x : y )
#define max(x, y) ( x > y ? x : y )

class Bignumber
{
private:
	int COMPARE(string number1, string number2); //�Ƚ�������С

public:
	string PLUS(string number1, string number2); //�ӷ�
	string MINUS(string number1, string number2); //����
	string MULTIPLY(string number1, string number2); //�˷�
	string DIVIDE(string number1, string number2, int floatpoint = 0); //����
	string MOD(string number1, string number2); //����
};