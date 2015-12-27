#include "bignumber_str.h"
#define Halfofpi "1.570796326794896619231321691639" //pi/2（30位）
#define Er "0.000000000000000000005" //0.5 * 10^(-20)
#define arctan1 "0.785398163397448309615660845819" //arctan1
#define xmax 0.5857 //1 - (根号2 - 1)
#define cap 40 //龙贝格三角形的最大层数
//PI = 3.
//14159 26535 89793 23846 26433
//83279 50288 41971 69399 37510
//58209 74944 59230 78164 06286
//20899 86280 34825 34211 70679

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

bool Abscompare(string a, string b, Bignumber num) // if (|a| < b) return true
{
	if (a[0] == '-') a = a.erase(0, 1);
	if (num.COMPARE(a, b) == -1) return true;
	else return false;
}

string f(string x, Bignumber num) //get f(x), f(x) = 1 / (1 + x ^ 2), f(0) = 1
{
	return num.DIVIDE("1", num.PLUS(num.MULTIPLY(x, x), "1"));
}

string Cotes(string x, Bignumber num) //复化科特斯法
{
	int n0;
	string result = "", n;
	int flag = 0, posi = 0;

	if (x[0] == '-') {
		x = x.erase(0, 1); //去掉负号
		posi = 1;
	}

	double x0 = atof(x.c_str());
	if (abs(x0 - 1) < xmax) { //接近1的地方需要采用特殊公式arctan A + arctan 1= arctan[(A+1)/(1-A)]， arctan A - arctan 1 = arctan[(A - 1) / (1 + A)]
		if (x0 - 1 < 0) {
			result = Cotes(num.DIVIDE(num.PLUS(x, "1"), num.MINUS("1", x)), num);
			result = num.MINUS(result, arctan1);
		}
		else if (x0 - 1 > 0){
			result = Cotes(num.DIVIDE(num.MINUS(x, "1"), num.PLUS("1", x)), num);
			result = num.PLUS(result, arctan1);
		}
		else return arctan1;
	}
	else 
	{
		if (x > "1") {
			x = num.DIVIDE("1", x); //x = 1 / x;
			flag = 1;
		}
		///////////////////////先算n///////////////////////////////
		x0 = atof(x.c_str());
		n0 = ceil(560 * x0) + 1;
		n = Num2str(n0);
		string h;
		h = num.DIVIDE(x, n); //h为FLOAT位精度

		string sum1 = "", sum2 = "", sum3 = "", sum4 = "";
		for (int k = 0; k < n0; k++) {
			sum1 = num.PLUS(sum1, f(num.MULTIPLY(Num2str(k + 0.25), h), num));
		}
		for (int k = 0; k < n0; k++) {
			sum2 = num.PLUS(sum2, f(num.MULTIPLY(Num2str(k + 0.5), h), num));
		}
		for (int k = 0; k < n0; k++) {
			sum3 = num.PLUS(sum3, f(num.MULTIPLY(Num2str(k + 0.75), h), num));
		}
		for (int k = 1; k < n0; k++) {
			sum4 = num.PLUS(sum4, f(num.MULTIPLY(Num2str(k), h), num));
		}
		string plus = num.PLUS("7", num.MULTIPLY("7", f(x, num)));
		plus = num.PLUS(plus, num.MULTIPLY("32", sum1));
		plus = num.PLUS(plus, num.MULTIPLY("12", sum2));
		plus = num.PLUS(plus, num.MULTIPLY("32", sum3));
		plus = num.PLUS(plus, num.MULTIPLY("14", sum4));
		result = num.MULTIPLY(num.DIVIDE(h, "90"), plus); //最终显示的结果是弧度制
	}
	if (flag == 1) result =  num.MINUS(Halfofpi, result);
	if (posi == 1) return result.insert(0, 1, '-');

	return result;
}

string Romberg(string x, Bignumber num) //龙贝格法
{
	string result = "";
	int flag = 0, posi = 0;

	if (x[0] == '-') {
		x = x.erase(0, 1); //去掉负号
		posi = 1;
	}

	double x0 = atof(x.c_str());
	if (abs(x0 - 1) < xmax) { //接近1的地方需要采用特殊公式arctan A + arctan 1= arctan[(A+1)/(1-A)]， arctan A - arctan 1 = arctan[(A - 1) / (1 + A)]
		if (x0 - 1 < 0) {
			result = Romberg(num.DIVIDE(num.PLUS(x, "1"), num.MINUS("1", x)), num);
			result = num.MINUS(result, arctan1);
		}
		else if (x0 - 1 > 0){
			result = Romberg(num.DIVIDE(num.MINUS(x, "1"), num.PLUS("1", x)), num);
			result = num.PLUS(result, arctan1);
		}
		else return arctan1;
	}
	else
	{
		if (x > "1") {
			x = num.DIVIDE("1", x); //x = 1 / x;
			flag = 1;
		}
		//开大小为cap的三角数组
		string T[cap][cap];
		T[0][0] = num.MULTIPLY(num.MULTIPLY("0.5", x), num.PLUS("1", f(x, num)));
		string h = x;
		int n = 1;
		int i, j = 0;
		int flagout = 0;
		for (i = 1; i < cap; i++)
		{
			//计算T[i-1][0]
			string plus = "";
			for (int k = 0; k < n; k++)
			{
				plus = num.PLUS(plus, f(num.MULTIPLY(Num2str(k + 0.5), h), num));
			}
			T[i][0] = num.PLUS(num.DIVIDE(T[i - 1][0], "2"), num.MULTIPLY(num.DIVIDE(h, "2"), plus));
			n = n * 2;
			h = num.DIVIDE(h, "2");
			for (j = 1; j <= i; j++)
			{
				//计算T[i][j]
				double mul = 1;
				for (int aa = 1; aa <= j; aa++) mul = mul * 4;
				string K = num.DIVIDE("1", Num2str(mul - 1));
				T[i][j] = num.MINUS(num.MULTIPLY(num.MULTIPLY(Num2str(mul), K), T[i][j - 1]), num.MULTIPLY(K, T[i - 1][j - 1]));
				//计算T[i][j]与T[i][j - 1]的误差，如果小于0.5*10^(-20)则break
				if (j == (i + 1) / 2 && Abscompare(num.MINUS(T[i][j], T[i][j - 1]), Er, num) == true) //误差小于0.0005即可推出
				{
					flagout = 1;
					break;
				}
			}
			if (flagout == 1) break;
			if (i == cap - 1) { j = cap / 2; break; }
		}
		result = T[i][j];
	}
	if (flag == 1) result = num.MINUS(Halfofpi, result);
	if (posi == 1) return result.insert(0, 1, '-');
	
	return result;
}

string Taylor(string x, Bignumber num) //泰勒法
{
	int flag = 0, posi = 0;
	if (x[0] == '-') {
		x = x.erase(0, 1); //去掉负号
		posi = 1;
	}
	double x0 = atof(x.c_str());
	string result, value, xx;
	if (abs(x0 - 1) < xmax) { //接近1的地方需要采用特殊公式arctan A + arctan 1= arctan[(A+1)/(1-A)]， arctan A - arctan 1 = arctan[(A - 1) / (1 + A)]
		if (x0 - 1 < 0) {
			result = Taylor(num.DIVIDE(num.PLUS(x, "1"), num.MINUS("1", x)), num);
			result = num.MINUS(result, arctan1);
		}
		else if (x0 - 1 > 0){
			result = Taylor(num.DIVIDE(num.MINUS(x, "1"), num.PLUS("1", x)), num);
			result = num.PLUS(result, arctan1);
		}
		else return arctan1;
	}
	else //在0处展开
	{
		if (x > "1") {
			x = num.DIVIDE("1", x); //x = 1 / x;
			flag = 1;
		}
		result = x;
		//arctan(x) = x - 1/3x^3 + 1/5x^5 - 1/7x^7 + 1/9x^9 - 1/11x^11 + ……
		x0 = atof(x.c_str());
		value = x;//表示某一项的值，用来停止循环
		xx = x;//用来累积x
		int k = 1;
		while (value >= Er) {
			string coe = Num2str(2 * k + 1);
			coe = num.DIVIDE("1", coe);//系数
			xx = num.MULTIPLY(num.MULTIPLY(xx, x), x);//xx = xx * x * x;
			value = num.MULTIPLY(coe, xx);//某一项的值
			if (k % 2 == 1) result = num.MINUS(result, value);
			else result = num.PLUS(result, value);
			k++;
		}
	}
	if (flag == 1) result = num.MINUS(Halfofpi, result);
	if (posi == 1) return result.insert(0, 1, '-');
	return result;
}

int main(int argc, char* argv[])
{
	string str1 = "12.1234567890123456789012345678901234567"; 
	string str2 = "333";
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

	cout << Romberg("-0.23", num) << endl;

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