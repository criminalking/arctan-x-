#include "bignumber_str.h"

int Bignumber::COMPARE(string number1, string number2) //�Ƚ�������С��1��ʾnumber1��-1��ʾnumber2��0��ʾ����һ����
{
	int length1 = number1.size();
	int length2 = number2.size();

	if (number1.size() == 0) number1 = "0";
	if (number2.size() == 0) number2 = "0";

	//j = 0;
	//for (int i = 0; i < length1; i++) //ȥ���ײ����õ���
	//{
	//	if (number1[i] == '0') j++;
	//	else break;
	//}
	//number1 = number1.substr(j);

	//j = 0;
	//for (int i = 0; i < length2; i++) //ȥ���ײ����õ���
	//{
	//	if (number2[i] == '0') j++;
	//	else break;
	//}
	//number2 = number2.substr(j);
	//length1 = number1.size();
	//length2 = number2.size();

	if (length1 > length2) return 1;
	else if (length1 == length2) {
		if (number1.compare(number2) > 0) return 1;
		else if (number1.compare(number2) == 0) return 0;
		else return -1;
	}
	else return -1;
	return 0;
}

string Bignumber::PLUS(string number1, string number2)
{
	int i;
	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

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

	//for (i = result.size() - 1; i >= 0; i--) { //ȥ���ײ���0
	//	if (result[i] != '0') break;
	//}
	//result = result.substr(0, i + 1);

	reverse(result.begin(), result.end());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MINUS(string number1, string number2)
{
	int i;
	string result = "";

	int length1 = number1.size();
	int length2 = number2.size();

	if (COMPARE(number2, number1) > 0) { //��֤��������ֵ�ϴ�
		return "-" + MINUS(number2, number1);
	}

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

	//�ײ�ȥ��(��2222 - 2221 = 1)
	for (i = result.size() - 1; i >= 0; i--) {
		if (result[i] != '0')break;
	}
	result = result.substr(0, i + 1);

	reverse(result.begin(), result.end());
	if (result.length() == 0) result = "0";
	return result;
}

string Bignumber::MULTIPLY(string number1, string number2)
{
	int i, j;
	int *allsum;
	int length1 = number1.size();
	int length2 = number2.size();
	string result = "";

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
	//ȥ���ײ��п��ܳ��ֵ�0
	for (i = length1 + length2 - 1; i >= 0; i--) {
		if (allsum[i] != 0) break;
	}

	for (; i >= 0; i--) {
		result = result + (char)(allsum[i] + '0');
	}
	if (result == "") result = "0";

	free(allsum);
	return result;
}

string Bignumber::DIVIDE(string number1, string number2, int floatpoint) //��������ȡ���� floatpoint����ָ������С�����λ��
{
	int i, j, pos;
	string result = "";
	string tempstr = "";
	int length1 = number1.size();
	int length2 = number2.size();

	if ((COMPARE(number2, number1) > 0) && (floatpoint == 0)) return "0";

	//�ȼ�����������
	tempstr = number1.substr(0, length2); //��number1��ȡ��number2λ
	pos = length2 - 1; //��־number1�����㵽����һλ
	while (pos < length1) {
		int quotient = 0;
		while (COMPARE(tempstr, number2) >= 0) {
			quotient++;
			tempstr = MINUS(tempstr, number2);
		}
		result = result + (char)(quotient + '0');
		pos++;
		if (pos < length1) { //�ó���һλ
			tempstr += number1[pos];
		}
	}
	//��ʱʣ�µ�tempstr��������
	string modd = tempstr;

	//�ټ���С������
	if (floatpoint > 0) {
		result += '.';
		/*string stmp = "1";
		for (int k = 0; k < floatpoint; k++) {
		stmp += '0';
		if (COMPARE(MULTIPLY(MINUS(number1, MULTIPLY(DIVIDE(number1, number2), number2)), stmp), number2) < 0) {
		result += '0';
		}
		}
		string temp = DIVIDE(MULTIPLY(MINUS(number1, MULTIPLY(DIVIDE(number1, number2), number2)), stmp), number2);
		if (temp[0] != '0') result += temp;*/

		for (int k = 0; k < floatpoint; k++) {
			modd += '0';
		}
		length1 = modd.size();
		tempstr = modd.substr(0, length2); //��number1��ȡ��number2λ
		pos = length2 - 1; //��־number1�����㵽����һλ
		while (pos < length1) {
			int quotient = 0;
			while (COMPARE(tempstr, number2) >= 0) {
				quotient++;
				tempstr = MINUS(tempstr, number2);
			}
			result = result + (char)(quotient + '0');
			pos++;
			if (pos < length1) { //�ó���һλ
				tempstr += modd[pos];
			}
		}
	}

	//ȥ���ײ���0
	j = result.size();
	for (i = 0; i < j; i++) {
		if (result[i] != '0') break;
	}
	result = result.substr(i, j);
	return result;
}

string Bignumber::MOD(string number1, string number2)
{
	if (COMPARE(number2, number1) > 0) return number1;
	else if (COMPARE(number2, number1) == 0) return "0";
	else return MINUS(number1, MULTIPLY(DIVIDE(number1, number2), number2));
}

int main(int argc, char* argv[])
{
	string str1 = "123330";
	string str2 = "234";
	string result;
	clock_t start, end;
	int interval = 0;
	Bignumber num;

	cout << "�ӷ�" << endl;
	cout << num.PLUS(str1, str2) << endl;
	cout << "����" << endl;
	cout << num.MINUS(str1, str2) << endl;
	cout << "�˷�" << endl;
	cout << num.MULTIPLY(str1, str2) << endl;
	cout << "����" << endl;
	cout << num.DIVIDE(str1, str2, 30) << endl;

	start = clock();
	result = num.DIVIDE(str1, str2, 30);
	end = clock();
	interval = (end - start) * 1000 / CLOCKS_PER_SEC;
	cout << "Result of ���� operation:" << endl;
	cout << result << endl;
	cout << "It took " << interval << "ms" << endl;
	system("pause");
	return 0;
}