#include "bignumber_str.h"
#define dividefloat 30

string Num2str(int n) //int to string 
{
	string str;
	char buffer[30];
	sprintf_s(buffer, "%d", n);
	str = buffer;
	return str;
}

string Num2str(double n) //double to string 
{
	string str;
	char buffer[30];
	sprintf_s(buffer, "%f", n);
	str = buffer;
	return str;
}

string f(string x, Bignumber num) //计算f(x), f(x) = 1 / (1 + x ^ 2), f(0) = 1
{
	return num.DIVIDE("1", num.PLUS(num.MULTIPLY(x, x), "1"), dividefloat);
}

string simpsen(string x, Bignumber num) //复化新普生法
{
	int i, n0;
	double x0 = atof(x.c_str());
	string result = "", n;
	///////////////////////先算n///////////////////////////////
	if (x0 > 60) { //即x>60
		//寻找t，要求t^4 >= (x / 60)
		for (i = 1;; i++) {
			if (i * i * i * i * 60 > x0) break;
		}
		n0 = ceil(i * x0 * 100000);
	}
	else if (x0 <= 60) { //即x<=60
		double j;
		for (j = 0.1;; j = j + 0.1) {
			if (j * j * j * j * 60 > x0) break;
		}
		n0 = ceil(j * x0 * 100000);
	}
	n = Num2str(n0);
	string h;
	h = num.DIVIDE(x, n, dividefloat); //h为dividefloat位精度

	string sum1 = "", sum2 = "";
	for (int k = 1; k < n0; k++) {
		sum1 = num.PLUS(sum1, f(num.MULTIPLY(Num2str(k), h), num));
	}
	for (int k = 0; k < n0; k++) {
		sum2 = num.PLUS(sum2, f(num.MULTIPLY(Num2str(k + 0.5), h), num));
	}
	string plus = num.PLUS("1", f(x, num));
	plus = num.PLUS(plus, num.MULTIPLY("2", sum1));
	plus = num.PLUS(plus, num.MULTIPLY("4", sum2));
	result = num.MULTIPLY(num.DIVIDE(h, "6"), plus); //最终显示的结果是弧度制
	return result;
}

string longbege(string x, int error) //龙贝格法
{
	string result = "";
	//开大小为20的三角数组
	int *T = new int[20];





	return result;
}

int main(int argc, char* argv[])
{
	string str1 = "1";
	string str2 = "3.123152452452312323";
	string result;
	clock_t start, end;
	int interval = 0;
	Bignumber num;

	//cout << "加法" << endl;
	//cout << num.PLUS(str1, str2) << endl;
	//cout << "减法" << endl;
	//cout << num.MINUS(str1, str2) << endl;
	//cout << "乘法" << endl;
	//cout << num.MULTIPLY(str1, str2) << endl;
	//cout << "除法" << endl;
	//cout << num.DIVIDE(str1, str2, 30) << endl;

	//cout<<simpsen("12", num)<<endl;

	start = clock();
	result = num.DIVIDE(str1, str2);
	end = clock();
	interval = (end - start) * 1000 / CLOCKS_PER_SEC;
	cout << "Result of 除法 operation:" << endl;
	cout << result << endl;
	cout << "It took " << interval << "ms" << endl;

	system("pause");
	return 0;
}