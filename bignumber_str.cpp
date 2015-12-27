#include "bignumber_str.h"

void Bignumber::IntandDecimal(string number, string *Intpart, string *Decimalpart) //��һ����ת���������ַ�����������С���������أ�����Ҫ���޷��ţ�
{
	int point = number.find('.');
	if (point >= number.length() || point <= 0) { //δ�ҵ�
		*Intpart = number; //Decimalpart = ""
	}
	else {
		*Intpart = number.substr(0, point);
		*Decimalpart = number.substr(point + 1, number.length() - point - 1);
	}
}

int Bignumber::De2int(string number, string *numbernew) //����������С����ȥ����������С��λ��������Ҫ���޷��ţ�
{
	int len = number.size();
	int point = number.find('.');
	if (point >= len || point <= 0) { //δ�ҵ�
		*numbernew = number;
		return 0;
	}
	else {
		*numbernew = number.erase(point, 1);
		return len - 1 - point;
	}
}

int Bignumber::COMPARE(string number1, string number2) //�Ƚ�������С������Ҫ���޷��ţ���1��ʾnumber1��-1��ʾnumber2��0��ʾ����һ����
{
	int j;
	int length1 = number1.size();
	int length2 = number2.size();
	if (number1.size() == 0) number1 = "0";
	if (number2.size() == 0) number2 = "0";

	j = 0;
	for (int i = 0; i < length1; i++) //ȥ���ײ����õ���
	{
		if (number1[i] == '0' && number1[i + 1] != '.') j++;
		else break;
	}
	number1 = number1.substr(j);

	j = 0;
	for (int i = 0; i < length2; i++) //ȥ���ײ����õ���
	{
		if (number2[i] == '0' && number2[i + 1] != '.') j++;
		else break;
	}
	number2 = number2.substr(j);

	//��������С���ֿ�
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	if (length1_Int > length2_Int) return 1;
	else if (length1_Int == length2_Int) { //�������ֳ������
		if (number1_Int.compare(number2_Int) > 0) return 1;
		else if (number1_Int.compare(number2_Int) == 0) { //�����������
			return number1_De.compare(number2_De); //ֱ�ӱȽ�С������
		}
		else return -1;
	}
	else return -1;
	return 0;
}

string Bignumber::PLUS(string number1, string number2)
{
	int i;
	////////////////////////���ȴ���������⣡����////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //�ݴ�
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //�������Ǹ���
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
		return "-" + PLUS(number1, number2);
	}
	else if (number1[0] == '-') { //��1��
		number1 = number1.erase(0, 1);
		return MINUS(number2, number1);
	}
	else if (number2[0] == '-') { //��2��
		number2 = number2.erase(0, 1);
		return MINUS(number1, number2);
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	////////////////////////С������////////////////////////////////////////
	//��������С���ֿ�
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	//���ȶ̵Ĳ���
	if (length1_De < length2_De) { //aС�����ֱȽ϶�
		number1_De = number1_De.insert(length1_De, length2_De - length1_De, '0');
		length1_De = number1_De.size();
	}
	else if (length2_De < length1_De) { //bС�����ֱȽ϶�
		number2_De = number2_De.insert(length2_De, length1_De - length2_De, '0');
		length2_De = number2_De.size();
	}

	//ȥ��С����
	number1 = number1_Int + number1_De;
	length1 = length1_Int + length1_De;
	number2 = number2_Int + number2_De;
	length2 = length2_Int + length2_De;

	////////////////////////////���////////////////////////////////////////
	//��ת�ַ���������Ӹ�λ������
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	//�����ǽ�λ�򵥼ӷ�
	for (i = 0; i < length1 && i < length2; i++) {
		char c = (char)(number1[i] + number2[i] - '0');//��ʱ�������λ
		result = result + c;
	}
	while (i < length1) { //number1�ϳ�
		result = result + number1[i];
		i++;
	}
	while (i < length2) { //number2�ϳ�
		result = result + number2[i];
		i++;
	}

	//�����λ
	int carry = 0;//��λ
	for (i = 0; i < (int)result.size(); i++) {
		int value = result[i] - '0' + carry;
		result[i] = (char)(value % 10 + '0');
		carry = value / 10;
	}
	if (carry != 0) {
		result = result + (char)(carry + '0');
	}

	reverse(result.begin(), result.end());
	if (length2_De != 0) result.insert(result.length() - length2_De, 1, '.');//����С����
	for (i = 0; i < result.length(); i++) { //ȥ���ײ���0
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, result.length());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MINUS2(string number1, string number2) //�����������
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
	////////////////////////���ȴ���������⣡����////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //�ݴ�
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //�������Ǹ���
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
		return MINUS(number2, number1);
	}
	else if (number1[0] == '-') { //��1��
		number1 = number1.erase(0, 1);
		return "-" + PLUS(number1, number2);
	}
	else if (number2[0] == '-') { //��2��
		number2 = number2.erase(0, 1);
		return PLUS(number1, number2);
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	if (COMPARE(number2, number1) > 0) { //��֤��������ֵ�ϴ�
		return "-" + MINUS(number2, number1);
	}

	////////////////////////С������////////////////////////////////////////
	//��������С���ֿ�
	string number1_Int = "", number1_De = "";
	string number2_Int = "", number2_De = "";
	IntandDecimal(number1, &number1_Int, &number1_De);
	IntandDecimal(number2, &number2_Int, &number2_De);

	int length1_Int = number1_Int.size();
	int length2_Int = number2_Int.size();
	int length1_De = number1_De.size();
	int length2_De = number2_De.size();

	//���ȶ̵Ĳ���
	if (length1_De < length2_De) { //aС�����ֱȽ϶�
		number1_De = number1_De.insert(length1_De, length2_De - length1_De, '0');
		length1_De = number1_De.size();
	}
	else if (length2_De < length1_De) { //bС�����ֱȽ϶�
		number2_De = number2_De.insert(length2_De, length1_De - length2_De, '0');
		length2_De = number2_De.size();
	}

	//ȥ��С����
	number1 = number1_Int + number1_De;
	length1 = length1_Int + length1_De;
	number2 = number2_Int + number2_De;
	length2 = length2_Int + length2_De;

	////////////////////////////���////////////////////////////////////////
	//��ת�ַ���������Ӹ�λ������
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	//�����ǽ�λ�򵥼���
	for (i = 0; i < length1 && i < length2; i++) {
		char c = number1[i] - number2[i] + '0';
		result = result + c;
	}
	if (i < length1) {
		for (; i < length1; i++) {
			result = result + number1[i];
		}
	}

	//������λ
	int back = 0; //��λ
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
	if (length2_De != 0) result.insert(result.length() - length2_De, 1, '.');//����С����
	for (i = 0; i < result.length(); i++) { //ȥ���ײ���0
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

	////////////////////////���ȴ���������⣡����////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //�ݴ�
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //�������Ǹ���
		number1 = number1.erase(0, 1);
		number2 = number2.erase(0, 1);
	}
	else if (number1[0] == '-') { //��1��
		number1 = number1.erase(0, 1);
		flag = 1;
	}
	else if (number2[0] == '-') { //��2��
		number2 = number2.erase(0, 1);
		flag = 1;
	}

	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

	int demi1 = De2int(number1, &number1);
	if (demi1 != 0) length1--;
	int demi2 = De2int(number2, &number2);
	if (demi2 != 0) length2--;                 //�˴�ע�⣺0.001����0001�����������ǳ˷����Բ�Ӱ�죬���һ��ܱ�֤��С����ʱ������

	//��ת�ַ���������Ӹ�λ������
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	allsum = (int*)malloc(sizeof(int) * (length1 + length2 + 1));
	memset(allsum, 0, sizeof(int) * (length1 + length2 + 1));

	//�����ǽ�λ�򵥳˷�
	for (i = 0; i < length1; i++) {
		for (j = 0; j < length2; j++) {
			allsum[i + j] += ((number1[i] - '0') * (number2[j] - '0'));
		}
	}

	//�����λ
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
	if (demi1 + demi2 != 0) { //��С����
		len = result.length() - demi1 - demi2;
		result.insert(len, 1, '.');//����С���㣬result.length() - demi1 - demi2ΪС��λ��
	}
	for (i = 0; i < length1 + length2 - 1; i++) { //ȥ���ײ���0
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, length1 + length2);
	if (flag == 1) result = result.insert(0, 1, '-');//Ϊ������������
	free(allsum);
	int a;
	for (a = 0; result[a] != '.' && a < result.length(); a++);
	if (a < result.length() && result.length() - a - 1 > 30) result = result.erase(a + FLOAT + 1);//��֤�����С��λ��С��FLOATλ
	//if (a < result.length()) result = result.erase(result.find_last_not_of('0'));//��С�������ɾ���Ӻ���ǰ�����0
	return result;
}

string Bignumber::DIVIDE(string number1, string number2, int floatpoint) //��������ȡ���� floatpoint����ָ������С�����λ��
{
	int i, j, pos, flag = 0;

	////////////////////////���ȴ���������⣡����////////////////////////
	if (number1[0] == '+') number1 = number1.erase(0, 1); //�ݴ�
	if (number2[0] == '+') number2 = number2.erase(0, 1);
	if (number1[0] == '-' && number2[0] == '-') { //�������Ǹ���
		number1 = number1.erase(0, 1); //ȥ������
		number2 = number2.erase(0, 1);
	}
	else if (number1[0] == '-') { //��1��
		number1 = number1.erase(0, 1);
		flag = 1;
	}
	else if (number2[0] == '-') { //��2��
		number2 = number2.erase(0, 1);
		flag = 1;
	}

	string result = "";
	string tempstr = "";
	int length1, length2;

	for (i = 0; i < number1.length() && number1[i] != '.'; i++);
	int aaa = 1;
	if (number1[i] == '.' && number1.length() - i > FLOAT + 2) number1 = number1.substr(0, i + FLOAT + 1);//�������С��λ���޶���FLOATλ
	////////////////////////ȥ����ͷ��0����0.01���001��ȥ��00��////////
	int demi1 = De2int(number1, &number1);
	length1 = number1.size();
	for (i = 0; i < length1; ++i) { //ȥ��ͷ����
		if (number1[i] != '0') break;
	}
	number1 = number1.substr(i, length1 - i);
	length1 = number1.size();

	int demi2 = De2int(number2, &number2);
	length2 = number2.size();
	for (i = 0; i < length2; ++i) { //ȥ��ͷ����
		if (number2[i] != '0') break;
	}
	number2 = number2.substr(i, length2 - i);
	length2 = number2.size();

	////////////////////////�ȼ�����������//////////////////////////////
	tempstr = number1.substr(0, length2); //��number1��ȡ��number2λ
	pos = length2 - 1; //��־number1�����㵽����һλ
	while (pos < length1) {
		int quotient = 0;
		while (COMPARE(tempstr, number2) >= 0) {
			++quotient;
			tempstr = MINUS2(tempstr, number2);
		}
		result = result + (char)(quotient + '0');
		++pos;
		if (pos < length1) { //�ó���һλ
			tempstr += number1[pos];
		}
	}
	if (result == "") result = "0"; // �����������������Ϊ0
	//��ʱʣ�µ�tempstr��������
	string modd = tempstr;

	////////////////////////�ټ���С������//////////////////////////////
	if (floatpoint > 0) {
		int k;
		for (k = 0; k < floatpoint - demi1 + demi2; ++k) {
			modd += '0';
		}
		if (k != 0) {//����Ҫ�ٽ���С������
			length1 = modd.size();
			tempstr = modd.substr(0, tempstr.length() + 1); //ȡ��������1λ
			pos = tempstr.length() - 1; //��־number1�����㵽����һλ
			while (pos < length1) {
				int quotient = 0;
				while (COMPARE(tempstr, number2) >= 0) {
					++quotient;
					tempstr = MINUS(tempstr, number2);
				}
				result = result + (char)(quotient + '0');
				++pos;
				if (pos < length1) { //�ó���һλ
					tempstr += modd[pos];
				}
			}
		}
	}

	//����С����ǰ�ȼ����㹻��0�Ա�֤С����λ���㹻
	if (demi1 > demi2) result = result.insert(0, demi1 - demi2, '0');
	if (floatpoint != 0) result = result.insert(result.length() - floatpoint, 1, '.');//����С����
	//ȥ���ײ���0
	for (i = 0; i < result.size(); ++i) {
		if (result[i] != '0' || (result[i] == '0' && result[i + 1] == '.')) break;
	}
	result = result.substr(i, result.size());
	if (flag == 1) result = result.insert(0, 1, '-');//Ϊ������������
	return result;
}

string Bignumber::MOD(string number1, string number2)
{
	if (COMPARE(number2, number1) > 0) return number1;
	else if (COMPARE(number2, number1) == 0) return "0";
	else return MINUS(number1, MULTIPLY(DIVIDE(number1, number2), number2));
}

string Bignumber::POW(string x, int k)//��x^k
{
	string result = "1";
	for (int i = 0; i < k; i++) {
		result = MULTIPLY(result, x);
	}
	return result;
}