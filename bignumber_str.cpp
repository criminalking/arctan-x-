#include "bignumber_str.h"

void Bignumber::IntandDecimal(string number, string *Intpart, string *Decimalpart) //将一个数转化成两个字符串（整数、小数）并返回（输入要求无符号）
{
	int point = number.find('.');
	if (point >= number.length() || point <= 0) { //未找到
		*Intpart = number; //Decimalpart = ""
	}
	else {
		*Intpart = number.substr(0, point);
		*Decimalpart = number.substr(point + 1, number.length() - point - 1);
	}
}

int Bignumber::De2int(string number, string *numbernew) //将任意数的小数点去掉，并返回小数位数（输入要求无符号）
{
	int len = number.size();
	int point = number.find('.');
	if (point >= len || point <= 0) { //未找到
		*numbernew = number;
		return 0;
	}
	else {
		*numbernew = number.erase(point, 1);
		return len - 1 - point;
	}
}

int Bignumber::COMPARE(string number1, string number2) //比较两数大小（输入要求无符号），1表示number1大，-1表示number2大，0表示两者一样大
{
	int j;
	int length1 = number1.size();
	int length2 = number2.size();
	if (number1.size() == 0) number1 = "0";
	if (number2.size() == 0) number2 = "0";

	j = 0;
	for (int i = 0; i < length1; i++) //去掉首部无用的零
	{
		if (number1[i] == '0' && number1[i + 1] != '.') j++;
		else break;
	}
	number1 = number1.substr(j);

	j = 0;
	for (int i = 0; i < length2; i++) //去掉首部无用的零
	{
		if (number2[i] == '0' && number2[i + 1] != '.') j++;
		else break;
	}
	number2 = number2.substr(j);

	//将整数与小数分开
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	if (length1_Int > length2_Int) return 1;
	else if (length1_Int == length2_Int) { //整数部分长度相等
		if (number1_Int.compare(number2_Int) > 0) return 1;
		else if (number1_Int.compare(number2_Int) == 0) { //整数部分相等
			return number1_De.compare(number2_De); //直接比较小数部分
		}
		else return -1;
	}
	else return -1;
	return 0;
}

string Bignumber::PLUS(string number1, string number2)
{
	int i;
	////////////////////////首先处理符号问题！！！////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //容错
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //两个都是负数
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
		return "-" + PLUS(number1, number2);
	}
	else if (number1[0] == '-') { //数1负
		number1 = number1.erase(0, 1);
		return MINUS(number2, number1);
	}
	else if (number2[0] == '-') { //数2负
		number2 = number2.erase(0, 1);
		return MINUS(number1, number2);
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	////////////////////////小数补零////////////////////////////////////////
	//将整数与小数分开
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	//首先短的补零
	if (length1_De < length2_De) { //a小数部分比较短
		number1_De = number1_De.insert(length1_De, length2_De - length1_De, '0');
		length1_De = number1_De.size();
	}
	else if (length2_De < length1_De) { //b小数部分比较短
		number2_De = number2_De.insert(length2_De, length1_De - length2_De, '0');
		length2_De = number2_De.size();
	}

	//去除小数点
	number1 = number1_Int + number1_De;
	length1 = length1_Int + length1_De;
	number2 = number2_Int + number2_De;
	length2 = length2_Int + length2_De;

	////////////////////////////相加////////////////////////////////////////
	//反转字符串，方便从个位数加起
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	//不考虑进位简单加法
	for (i = 0; i < length1 && i < length2; i++) {
		char c = (char)(number1[i] + number2[i] - '0');//暂时不处理进位
		result = result + c;
	}
	while (i < length1) { //number1较长
		result = result + number1[i];
		i++;
	}
	while (i < length2) { //number2较长
		result = result + number2[i];
		i++;
	}

	//处理进位
	int carry = 0;//进位
	for (i = 0; i < (int)result.size(); i++) {
		int value = result[i] - '0' + carry;
		result[i] = (char)(value % 10 + '0');
		carry = value / 10;
	}
	if (carry != 0) {
		result = result + (char)(carry + '0');
	}

	reverse(result.begin(), result.end());
	if (length2_De != 0) result.insert(result.length() - length2_De, 1, '.');//插入小数点
	for (i = 0; i < result.length(); i++) { //去掉首部的0
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, result.length());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MINUS2(string number1, string number2) //正整大数相减
{
	int i;
	string result = "";

	int length1 = number1.size();
	int length2 = number2.size();

	if (COMPARE(number2, number1) > 0)
	{
		return "-" + MINUS2(number2, number1);
	}

	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	for (i = 0; i < length1 && i < length2; i++)
	{
		char c = number1[i] - number2[i] + 48;
		result = result + c;
	}

	if (i < length1)
	{
		for (; i < length1; i++)
		{
			result = result + number1[i];
		}
	}

	int carry = 0;
	for (i = 0; i < (int)result.length(); i++)
	{
		int value = result[i] - 48 + carry;
		if (value < 0)
		{
			value = value + 10;
			carry = -1;
		}
		else carry = 0;
		result[i] = (char)(value + 48);
	}

	for (i = result.size() - 1; i >= 0; i--)
	{
		if (result[i] != '0') break;
	}

	result = result.substr(0, i + 1);

	reverse(result.begin(), result.end());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MINUS(string number1, string number2) 
{
	int i;
	////////////////////////首先处理符号问题！！！////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //容错
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //两个都是负数
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
		return MINUS(number2, number1);
	}
	else if (number1[0] == '-') { //数1负
		number1 = number1.erase(0, 1);
		return "-" + PLUS(number1, number2);
	}
	else if (number2[0] == '-') { //数2负
		number2 = number2.erase(0, 1);
		return PLUS(number1, number2);
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	if (COMPARE(number2, number1) > 0) { //保证减数绝对值较大
		return "-" + MINUS(number2, number1);
	}

	////////////////////////小数补零////////////////////////////////////////
	//将整数与小数分开
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	//首先短的补零
	if (length1_De < length2_De) { //a小数部分比较短
		number1_De = number1_De.insert(length1_De, length2_De - length1_De, '0');
		length1_De = number1_De.size();
	}
	else if (length2_De < length1_De) { //b小数部分比较短
		number2_De = number2_De.insert(length2_De, length1_De - length2_De, '0');
		length2_De = number2_De.size();
	}

	//去除小数点
	number1 = number1_Int + number1_De;
	length1 = length1_Int + length1_De;
	number2 = number2_Int + number2_De;
	length2 = length2_Int + length2_De;

	////////////////////////////相减////////////////////////////////////////
	//反转字符串，方便从个位数减起
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	//不考虑进位简单减法
	for (i = 0; i < length1 && i < length2; i++) {
		char c = number1[i] - number2[i] + '0';
		result = result + c;
	}
	if (i < length1) {
		for (; i < length1; i++) {
			result = result + number1[i];
		}
	}

	//处理退位
	int back = 0; //退位
	for (i = 0; i < (int)result.length(); i++) {
		int value = result[i] - '0' + back;
		if (value < 0) {
			value = value + 10;
			back = -1;
		}
		else back = 0;
		result[i] = (char)(value + '0');
	}

	reverse(result.begin(), result.end());
	if (length2_De != 0) result.insert(result.length() - length2_De, 1, '.');//插入小数点
	for (i = 0; i < result.length(); i++) { //去掉首部的0
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, result.length());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MULTIPLY(string number1, string number2)
{
	int i, j, flag = 0;
	int *allsum;

	////////////////////////首先处理符号问题！！！////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //容错
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //两个都是负数
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
	}
	else if (number1[0] == '-') { //数1负
		number1 = number1.erase(0, 1);
		flag = 1;
	}
	else if (number2[0] == '-') { //数2负
		number2 = number2.erase(0, 1);
		flag = 1;
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	int demi1 = De2int(number1, &number1);
	if (demi1 != 0) length1--;
	int demi2 = De2int(number2, &number2);
	if (demi2 != 0) length2--;                 //此处注意：0.001会变成0001，不过由于是乘法所以不影响，而且还能保证加小数点时不超过

	//反转字符串，方便从个位数乘起
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	allsum = (int*)malloc(sizeof(int) * (length1 + length2 + 1));
	memset(allsum, 0, sizeof(int) * (length1 + length2 + 1));

	//不考虑进位简单乘法
	for (i = 0; i < length1; i++) {
		for (j = 0; j < length2; j++) {
			allsum[i + j] += ((number1[i] - '0') * (number2[j] - '0'));
		}
	}

	//处理进位
	int carry = 0;
	for (i = 0; i < length1 + length2; i++) {
		int value = allsum[i] + carry;
		allsum[i] = value % 10;
		carry = value / 10;
	}

	for (; i >= 0; i--) {
		result = result + (char)(allsum[i] + '0');
	}
	if (result == "") result = "0";
	
	int len = 0;
	if (demi1 + demi2 != 0) { //有小数点
		len = result.length() - demi1 - demi2;
		result.insert(len, 1, '.');//插入小数点，result.length() - demi1 - demi2为小数位数
	}
	for (i = 0; i < length1 + length2 - 1; i++) { //去掉首部的0
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, length1 + length2);
	if (flag == 1) result = result.insert(0, 1, '-');//为防错负号在最后加
	free(allsum);
	int a;
	for (a = 0; result[a] != '.' && a < result.length(); a++);
	if (a < result.length() && result.length() - a - 1 > 30) result = result.erase(a + FLOAT + 1);//保证输出的小数位数小于FLOAT位
	//if (a < result.length()) result = result.erase(result.find_last_not_of('0'));//有小数情况下删除从后往前多余的0
	return result;
}

string Bignumber::DIVIDE(string number1, string number2, int floatpoint) //商数向下取整， floatpoint用于指定保留小数点的位数
{
	int i, j, pos, flag = 0;

	////////////////////////首先处理符号问题！！！////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //容错
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //两个都是负数
		number1 = number1.erase(0, 1); //去掉负号
		number2 = number2.erase(0, 1);
	}
	else if (number1[0] == '-') { //数1负
		number1 = number1.erase(0, 1);
		flag = 1;
	}
	else if (number2[0] == '-') { //数2负
		number2 = number2.erase(0, 1);
		flag = 1;
	}

	string result = "";
	string tempstr = "";
	int length1, length2;

	for (i = 0; i < number1.length() && number1[i] != '.'; i++);
	int aaa = 1;
	if (number1[i] == '.' && number1.length() - i > FLOAT + 2) number1 = number1.substr(0, i + FLOAT + 1);//将输入的小数位数限定在FLOAT位
	////////////////////////去掉开头的0（如0.01变成001，去掉00）////////
	int demi1 = De2int(number1, &number1);
	length1 = number1.size();
	for (i = 0; i < length1; ++i) { //去开头的零
		if (number1[i] != '0') break;
	}
	number1 = number1.substr(i, length1 - i);
	length1 = number1.size();

	int demi2 = De2int(number2, &number2);
	length2 = number2.size();
	for (i = 0; i < length2; ++i) { //去开头的零
		if (number2[i] != '0') break;
	}
	number2 = number2.substr(i, length2 - i);
	length2 = number2.size();

	////////////////////////先计算整数部分//////////////////////////////
	tempstr = number1.substr(0, length2); //在number1中取出number2位
	pos = length2 - 1; //标志number1中运算到了哪一位
	while (pos < length1) {
		int quotient = 0;
		while (COMPARE(tempstr, number2) >= 0) {
			++quotient;
			tempstr = MINUS2(tempstr, number2);
		}
		result = result + (char)(quotient + '0');
		++pos;
		if (pos < length1) { //拿出下一位
			tempstr += number1[pos];
		}
	}
	if (result == "") result = "0"; // 整数部分如果无数设为0
	//此时剩下的tempstr就是余数
	string modd = tempstr;

	////////////////////////再计算小数部分//////////////////////////////
	if (floatpoint > 0) {
		int k;
		for (k = 0; k < floatpoint - demi1 + demi2; ++k) {
			modd += '0';
		}
		if (k != 0) {//不需要再进行小数运算
			length1 = modd.size();
			tempstr = modd.substr(0, tempstr.length() + 1); //取出余数加1位
			pos = tempstr.length() - 1; //标志number1中运算到了哪一位
			while (pos < length1) {
				int quotient = 0;
				while (COMPARE(tempstr, number2) >= 0) {
					++quotient;
					tempstr = MINUS(tempstr, number2);
				}
				result = result + (char)(quotient + '0');
				++pos;
				if (pos < length1) { //拿出下一位
					tempstr += modd[pos];
				}
			}
		}
	}

	//插入小数点前先加入足够的0以保证小数点位数足够
	if (demi1 > demi2) result = result.insert(0, demi1 - demi2, '0');
	if (floatpoint != 0) result = result.insert(result.length() - floatpoint, 1, '.');//插入小数点
	//去除首部的0
	for (i = 0; i < result.size(); ++i) {
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, result.size());
	if (flag == 1) result = result.insert(0, 1, '-');//为防错负号在最后加
	return result;
}

string Bignumber::MOD(string number1, string number2)
{
	if (COMPARE(number2, number1) > 0) return number1;
	else if (COMPARE(number2, number1) == 0) return "0";
	else return MINUS(number1, MULTIPLY(DIVIDE(number1, number2), number2));
}

string Bignumber::POW(string x, int k)//求x^k
{
	string result = "1";
	for (int i = 0; i < k; i++) {
		result = MULTIPLY(result, x);
	}
	return result;
}