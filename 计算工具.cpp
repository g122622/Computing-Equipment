// ������ƣ����㹤��
// ���ڣ�20190912
// �汾��v1.4.4
// ����ƽ̨��Windows��Microsoft Visual Studio��Android��c4droid
// test2332







// changelog:
// v1.1.0 �ı���������Ⱥ�˳���õȴ�ʱ�������֪ϰ�ߡ�
// v1.1.1 �޸�����ѭ������ֵ��20000�������������
// v1.2.0 �������޸���λbug;��Ӽ���λ��
// v1.2.1 �İ��Ż���
// v1.2.2 ��������ɫ��
// v1.3.0 ������������Ԥ����ٹ��ܡ�
// v1.4.0 �Ż�������������ٶȣ����Լ50%;����ʾ�����Ż���������ʾ1�����ֱ���
// v1.4.1 ������Ĳ����Ż�����ʽ�Ż�;��Ԫһ�η������a=0ʱ���б���;����ͷ���������ʱ�������ʾ�ˡ�
// v1.4.2 �޸���������������2ʱ��ʾ�������bug��
// v1.4.3 ���̲��ִ������;�������������������ʾ;�޸�������������0ʱ��ʾ�������bug��
// v1.4.4 ����ֽ���Ӵ��������ж�ģ�顣
// v2.0.0 1.�����Ż�������û��warning��;2.�Ż���������������жϲ��ֵĽ���;3.�Ż���������a=0ʱ�Ľ���;4.�Ż����̲������ʾ;
// 5.�������������Ϊ����ʱ����ʾ;6.switch��֧�ṹ���ж�������͸�Ϊlong long���������ܳ;
// ���������ʷ�汾


//bug���1:�޷����С����ʾ����
//bug���2:aΪС�ڵ���-2����ʱ���޷��ֽ⡣���:����⵽aΪ����ʱ������if����תabc�ķ�š�
//���������ܴ����ش�����bug:��ʽ�ֽ���ʹ��������(int,long)��ʱ������ǿ������ת��С����ᵼ������쳣
//

/*
������� main ����֮����к�����ģ���ô����ʱ��һ��Ҫ�� main ����֮ǰ��������
������Զ��庯���� main ����֮ǰ����ģ��Ϳ��Բ���Ҫ��������main �����ܹ��Զ��ҵ��ú���
�����к�������������ı������оͻ�����Զ��庯���Ҳ���������
*/

   // system("pause");
// ���㹤��.cpp : ���ļ��� "main"
// �������ִ�н��ڴ˴���ʼ������
// ����user�ж����޷���Ҫ���aΪ��Ϊ0�����aΪ���ʱ���ĸ��������ģ�
// ��ʽ��Ҫ�����������

/*----------Ԥ������/Ԥ������������----------*/
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <iomanip>
//#include <cstdlib>
#define enabled 0
#define disabled 1
using namespace std;


/*----------�ṹ��������----------*/
// ���θ�ʽ����ṹ��
struct simplify_quadratic_radical_struct
{
	long in_radical;
	long out_radical;
};

// ð������ṹ��
struct getSortedData_struct
{
	long data_array[512];
	long swapcount = 0;
};

// ����Լ�ֽṹ��
struct simplify_fraction_struct
{
	long simplified_numerator;		// ����
	long simplified_denominator;	// ��ĸ
	long greatest_common_divisor;	// ���Լ��
	short single_display_state;
	short minus_display_state;
};


/*----------����������----------*/
double getRandData(long, long);
simplify_quadratic_radical_struct simplify_quadratic_radical(long);
void swapData(long&, long&);
getSortedData_struct getSortedData(getSortedData_struct, long&);
long long loadMasterConsole(long long);
simplify_fraction_struct simplify_fraction(long, long);
long getAbsoluteData(long);
void displayFraction(simplify_fraction_struct);


// ���������еĺ���
double getRandData(long min, long max)
{	// ���� 0��1֮������С��,�õ���ֵ�����Ϊ(0,1)
	double m1 = (double)(rand() % 101) / 101;
	// ������Ϊ(min+1,max)
	min++;
	// ���� min+1,max ֮����������õ���ֵ��Ϊ[min+1,max]
	double m2 = (double)((rand() % (max - min + 1)) + min);
	// ��ֵ��Ϊ[min,max-1]
	m2 = m2 - 1;
	// ����ֵ��Ϊ(min,max),Ϊ����������
	return m1 + m2;
}


// ���θ�ʽ������
simplify_quadratic_radical_struct simplify_quadratic_radical(long numscan)
{
	// ʹ�ýṹ�崫��
	simplify_quadratic_radical_struct temp;	// ����temp�ṹ��
	for (long i = numscan; i > 0; i--)
	{
		if ((double) numscan / i == (long) numscan / i and (double)sqrt(i) == (long)sqrt(i))
			// ��һ�������ȷ��iΪnumscan��������ڶ��������ȷ��i��������ȫƽ������
		{
			temp.in_radical =  numscan / i;	// �������ʣ�����
			temp.out_radical =  sqrt(i);	// �������ֽ�������
			break;
		}
	}
	return temp;
}


// ��Խ�������
void swapData(long& num1, long& num2)
{
	long* temp = new long;	// �������ڴ�ռ�
	*temp = num2;
	num2 = num1;
	num1 = *temp;
	delete temp;			// �ͷ��ڴ�
}


// ð��������
getSortedData_struct getSortedData(getSortedData_struct temp, long& dataamount)
{
	//getSortedData_struct temp;	// ����temp�ṹ��
	for (int k = 0; k < dataamount; k++)
	{
		for (int j = dataamount - 1; j > 0;j--)
		{
			if (temp.data_array[j] < temp.data_array[j - 1])
			{
				swapData(temp.data_array[j - 1], temp.data_array[j]);	// ����������
				(temp.swapcount)++;
			}
		}
	}
	return temp;
}


// ����Լ�ֺ���
simplify_fraction_struct simplify_fraction(long numerator, long denominator)
{
	simplify_fraction_struct temp;
	temp.single_display_state = enabled;								// Ĭ������������ʾ
	long abs_num = getAbsoluteData(numerator);							// ȡ���ֵ�����⴫�븺��ʱ�ڴ�δ����ʼ��
	long abs_den = getAbsoluteData(denominator);
	for (long i = (abs_num + abs_den) / 2; i > 0; i--)					// ab���ֵ��ӳ���2����������������
	{																	// jΪ���Լ��
		if ((double)numerator / i == (long)numerator / i and (double)denominator / i == (long)denominator / i)
		{
			temp.greatest_common_divisor = i;
			temp.simplified_numerator = numerator / i;
			temp.simplified_denominator = denominator / i;
			// �жϷ����Ƿ���ʾ����
			if (temp.simplified_numerator * temp.simplified_denominator >= 0)
			{
				temp.minus_display_state = disabled;
			}
			else
			{
				temp.minus_display_state = enabled;
			}
			// ���ӷ�ĸȫ��ȡ���ֵ
			temp.simplified_numerator = getAbsoluteData(temp.simplified_numerator);
			temp.simplified_denominator = getAbsoluteData(temp.simplified_denominator);
			// ������Լ����ڷ�ĸ�ľ��ֵ������������ʾ
			if (temp.greatest_common_divisor == abs_den)
			{
				temp.single_display_state = enabled;
			}
			else
			{
				temp.single_display_state = disabled;
			}
			break;
		}
	}
	return temp;
}


// ������ʾ����
void displayFraction(simplify_fraction_struct temp)
{
	if (temp.simplified_numerator != 0)			// ������Ϊ0��ֱ����ʾ0
	{
		if (temp.minus_display_state == enabled)
		{
			cout << "-";
		}
		if (temp.single_display_state == disabled)
		{
			cout << temp.simplified_numerator << "/"
				<< temp.simplified_denominator;
		}
		else
		{
			cout << temp.simplified_numerator;
		}
	}
	else
	{
		cout << "0";
	}
}


// ȡ���ֵ����
long getAbsoluteData(long numscan)
{
	if (numscan < 0)
	{
		numscan = -numscan;
	}
	return numscan;
}


// ����ֽ⺯��


// �����ܿ���̨����
long long loadMasterConsole()
{
	long long SwitchNum;
	cout << "===============[�ܿ���̨]===============" << endl
		<< "1::��/�����Ԫһ�η���" << endl
		<< "2::����ֽ�" << endl
		<< "3::����С�������������" << endl
		<< "4::�ж���ȫƽ����" << endl
		<< "5::�������" << endl
		<< "6::����Լ��" << endl
		<< "7::���θ�ʽ����" << endl
		<< "8::���θ�ʽ��ĸ����" << endl
		<< "9::���֤��֤�����" << endl
		<< "10::��������֤�����" << endl
		<< "11::����ƽ������λ�������" << endl
		<< "12::�����Ȩƽ����" << endl
		<< "13::��������" << endl
		<< "14::���κ������ʽ����" << endl
		// ����
		/*
		<< "11::" << endl
		<< "11::" << endl
		<< "11::" << endl
		*/
		<< "0::��ʾ����̨" << endl
		<< "[����]";
	cin >> SwitchNum;
	cout << "====================" << endl << endl;
	return SwitchNum;
}

clock_t start, stop;				// ��ʼ����ʱ����

int main(void)						// ��ʼִ������
{
	long double pretime;
	short speedTestState = enabled;	// �����β���
Select_Num_Scan:
	switch (loadMasterConsole())	// �����ܿ���̨
	{
	case 1:		// ��/�����Ԫһ�η���
	{
		float* a = new float;		// ���ڷ��̵�����
		float* b = new float;
		float* c = new float;
		float* Delta = new float;
		float* mid2 = new float;	// �������
		float* mid3 = new float;

		int* fzacount = new int;
		long* fzmid1 = new long;					//���ڳ�a��c
		long double* fzmid2 = new long double;		//���ڱ�a��
		int* FZA = new int[512];
		*fzacount = 0;
		*fzmid1 = 1;
		// int m1, d1, m2, d2, m3, d3, mid4, mid5, mid6, d = 0; //
		// ����������Ҫ�õ��������ﶨ�壬��ʱ���ò���
		// float mid7, mid8, mid9; //
		// ���ڷ������ʱ���ò���

		std::cout << "{!}��������������ͣ�ax^2+bx+c=0 \n" << std::endl;
	A_Scan:
		printf("{!}������a��ֵ�� \n");
		printf("[a]");
		cin >> *a;
		if (*a == 0)
		{
			cout <<
				"��a=0����÷��̲����ڶ�Ԫһ�η��̣�����������a��ֵ."
				<< endl;
			goto A_Scan;
		}
		else
		{
			goto B_Scan;
		}
	B_Scan:
		printf("{!}������b��ֵ�� \n");
		printf("[b]");
		cin >> *b;
		printf("{!}������c��ֵ�� \n");
		printf("[c]");
		cin >> *c;
		// �������

		cout << endl;	// ������
		printf("%gx^2+%gx+%g=0 \n\n", *a, *b, *c);

		cout << "��Τ�ﶨ��\nx(1)+x(2) = -b/a = " << -*b / *a << "." << endl
			<< "x(1)x(2) = c/a = " << *c / *a << "." << endl << endl;

		std::cout << "[�ⷨ1����ʽ�ֽⷨ(ʵ���ԣ�bug���ܽ϶�)]" << std::endl;
		do
			// ��ʼa���������ѭ����a�ķֽ�ֻ��Ҫ��ֵ����
		{
			*fzmid2 = *a / *fzmid1;
			if (*fzmid2 == (long long)* fzmid2)
			{
				FZA[*fzacount] = *fzmid1;
				//cout << *fzacount+1 << "��";
				//cout << FZA[*fzacount] << endl;
				//��������
				(*fzmid1)++;
				(*fzacount)++;
			}			// if
			else
			{
				(*fzmid1)++;
			}			// else
		}				// do
		while (*fzmid1 <= *a and *fzacount <= 20000);	//�쳣�ж�

		// ///////��ʼ*c���������ѭ������ֵ��Ҫ���㣬������*c������
		long* fzmid3 = new long;
		*fzmid3 = (long)-*c;	// ���fzmid3��Ϊ�˱����������ת����warning
		*fzmid1 = *fzmid3;		// ��λ
		delete fzmid3;			// ��ֵ�����
		int* fzccount = new int;
		*fzccount = 0;
		int* FZC = new int[512];
		if (*c > 0)
		{
			do
			{
				*fzmid2 = *c / *fzmid1;
				if (*fzmid2 == (long long)* fzmid2)
				{
					FZC[*fzccount] = *fzmid1;
					//cout << FZC[fzccount] << endl;	// ��������ڵ���
					(*fzmid1)++;
					(*fzccount)++;
				}			// if
				else
				{
					(*fzmid1)++;
				}			// else
			}				// do
			while (*fzmid1 <= *c and *fzccount <= 20000);	//�쳣�ж�
		}					// if (*c>0)
		else				//*c�ĸ����������ģ�飨�£�
		{
			do
				// ��ʼ*c���������ѭ������ֵ��Ҫ����
			{
				*fzmid2 = *c / *fzmid1;
				if (*fzmid2 == (long long)* fzmid2)
				{
					FZC[*fzccount] = *fzmid1;
					//cout << FZC[fzccount] << "test" << endl;	// ��������ڵ���
					(*fzmid1)--;
					(*fzccount)++;
				}			// if
				else
				{
					(*fzmid1)--;
				}			// else
			}				// do
			while (*fzmid1 >= *c and *fzccount <= 20000);	//�쳣�ж�
		}					//if��first-else��

							// ���������ɣ���ʼforѭ��+if���ƥ��
		for (int i = 0; i <= *fzccount; i++)
		{
			for (int j = 0; j <= *fzacount; j++)
			{
				if (FZA[j] * (*c / FZC[i]) + FZC[i] * (*a / FZA[j]) == *b)//�����������
				{
					// ��������ʼ��� Output
					if (FZC[i] == *c / FZC[i] and FZA[j] == *a / FZA[j]) //�����ȫƽ��
					{
						cout << "( ";
						if (FZA[j] != 1) /////1
						{
							cout << FZA[j];
						}			//if
						if (FZC[i] < 0)
						{
							cout << "x " << FZC[i] << " ) ^ 2 = 0" << endl;
						}
						else
						{
							cout << "x + " << FZC[i] << " ) ^ 2 = 0" << endl;
						}
						goto EqualRoot_Output;
					}				//if

					cout << "( ";
					if (FZA[j] != 1) /////1
					{
						cout << FZA[j];
					}
					if (FZC[i] < 0)
					{
						cout << "x " << FZC[i] << " ) " << "( ";
					}
					else
					{
						cout << "x + " << FZC[i] << " ) " << "( ";
					}
					if (*a / FZA[j] != 1) /////2
					{
						cout << *a / FZA[j];
					}
					if (*c / FZC[i] < 0)
					{
						cout << "x " << *c / FZC[i] << " ) = 0" << endl;
					}
					else
					{
						cout << "x + " << *c / FZC[i] << " ) = 0" << endl;
					}
					//line 2 output
					if (FZA[j] != 1) /////1
					{
						cout << FZA[j];
					}
					if (FZC[i] < 0)
					{
						cout << "x " << FZC[i] << " = 0���� ";
					}
					else
					{
						cout << "x + " << FZC[i] << " = 0���� ";
					}
					if (*a / FZA[j] != 1) /////2
					{
						cout << *a / FZA[j];
					}
					if (*c / FZC[i] < 0)
					{
						cout << "x " << *c / FZC[i] << " = 0" << endl;
					}
					else
					{
						cout << "x + " << *c / FZC[i] << " = 0" << endl;
					}

					/*
					cout << *a / FZA[j] << "x + " << *c / FZC[i] << " ) = 0" << endl;
					cout << *c / FZC[i] << " ) = 0" << endl;

					cout << "( " << FZA[j];
					cout << "x + " << FZC[i] << " ) = 0���� ( ";
					cout << *a / FZA[j] << "x + " << *c / FZC[i] << " ) = 0" << endl;
					*/
					if ((float)-FZC[i] / FZA[j] == (float)(-*c / FZC[i]) / (*a / FZA[j]))	//�Եȸ���ʽ�����
					{
					EqualRoot_Output:
						cout << "��x(1)=x(2)=" << (float)-FZC[i] / FZA[j] << "." << endl << endl;
					}
					else	//�Բ��ȸ���ʽ�����
					{
						cout << "��x(1)=" << (float)-FZC[i] / FZA[j];
						cout << "��x(2)=" << (float)(-*c / FZC[i]) / (*a / FZA[j]) << "." << endl;
						cout << endl;	// ��һ��
					}
					goto Method_2;	// ������forѭ��
				}		// if
			}			// for Aj
		}				// for Ci

		cout << "{!}�÷��̲�����ʽ�ֽ�!" << endl << endl;
	Method_2:
		std::cout << "[�ⷨ2����ʽ��]" << std::endl;
		// �ж�&����ģ��of��ʽ��
		*Delta = pow(*b, 2) - 4 * *a * *c;
		printf("��=%g^2-4��%g��%g=%g. \n", *b, *a, *c, *Delta);
		if (*Delta > 0)	// ///����б�ʽ������
		{
			if (sqrt(*Delta) == (int)sqrt(*Delta))
			{
				//����ȫƽ����
				*mid2 = (-1 * *b + sqrt(*Delta)) / (2 * *a);
				*mid3 = (-1 * *b - sqrt(*Delta)) / (2 * *a);
				// =====��ʽ����ʼ���=====
	 /*------------------���ģ�飨�б�ʽ������,��Ϊ��ȫƽ����of��ʽ��------------------*/
				std::cout << "�ߦ�>0���෽���������ȵ�ʵ���." <<
					std::endl;
				printf("��x(1)=%g��x(2)=%g. \n", *mid2, *mid3);
			}
			else
			{
				//������ȫƽ����
				*mid2 = -*b;
				*mid3 = 2 * *a;
				/*------------------���ģ�飨�б�ʽ������,�Ҳ�Ϊ��ȫƽ����of��ʽ��------------------*/
				std::cout << "�ߦ�>0���෽���������ȵ�ʵ���." <<
					std::endl;
				printf("��x(1) =��%g+��%g��/ %g��x(2) =��%g-��%g��/ %g. \n", *mid2,
					*Delta, *mid3, *mid2, *Delta, *mid3);
			}
		}
		else			// ����б�ʽ��������
		{
			if (*Delta == 0)	// ///����б�ʽΪ�㣬����Ҫ�ж����Ƿ�Ϊ��ȫƽ��
			{
				*mid2 = (-1 * *b + sqrt(*Delta)) / (2 * *a);
				/*------------------���ģ�飨�б�ʽ�����㣬��Ϊ��ȫƽ����of��ʽ��------------------*/
				std::cout << "�ߦ�=0���෽���������ȵ�ʵ���." <<
					std::endl;
				printf("��x(1)=x(2)=%g. \n", *mid2);
			}
			else		// ///�б�ʽΪ������ʵ���
			{
				/*------------------���ģ�飨�б�ʽС���㣩of��ʽ��------------------*/
				std::cout << "�ߦ�<0,�෽��û��ʵ���.\n{!}������ֹ." <<
					std::endl;
			}			// else
		}				// else
						// =====����ģ��
						/* }//���if mid1 = 0,1,2,3,4,5,6,7,8,9 Ϊ�ٵ��ж�//
		   else { std::cout <<
		   "����������á�/����Ϊ������ " << std::endl;
		   std::cout << "������a��ֵ " << std::endl;
		   scanf("%d/%d", &m1, &d1); std::cout << "������*b��ֵ "
		   << std::endl; scanf("%d/%d", &m2, &d2); std::cout <<
		   "������c��ֵ " << std::endl; scanf("%d/%d", &m3, &d3);
		   }			*/
		   //�ͷ��ڴ�
		delete a, b, c, Delta, mid2, mid3;
		delete[] FZA, FZC;
		delete fzacount, fzccount, fzmid1, fzmid2;
		goto Select_Num_Scan;
	}						// case1

	case 2:		// ����ֽ�
	{
		long double prenumscan = 4777778;
		if (speedTestState == enabled) // �����ظ�����
		{
			long double* premid1 = new long double;
			long double* premid2 = new long double;
			int* precount = new int;
			*premid1 = 2;
			*precount = 1;
			cout << "{!}����ʼִ�С�\n[���ڲ��٣����Ժ������Ϣ����ԡ�]" << endl;
			start = clock();	// ��ʼ����
			do
			{
				*premid2 = prenumscan / *premid1;
				if (*premid2 == (long long)* premid2)
				{
					printf("IF_%d = ", *precount);
					cout << *premid1;
					cout << endl;	// ���һ���з�
					(*premid1)++;
					(*precount)++;
				}
				else
				{
					(*premid1)++;
				}
			} while (*premid1 <= (prenumscan / 2) and *precount <= 20000);	// while�쳣�ж�
			stop = clock();		// ֹͣ����
			pretime = (float)(stop - start) / CLOCKS_PER_SEC;
			cout << "Time=" << pretime << endl << "������ɡ�" << endl << endl;
			speedTestState = disabled;
			delete premid1, premid2, precount;
		}
		// ���ٽ���
		double* duration = new double;
		long double* numscan = new long double;
		long double* predicttime = new long double;
		long double* mid1 = new long double;
		long double* mid2 = new long double;
		int* count = new int;
		*count = 1;
		*mid1 = 2;
		// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		// FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
		// FOREGROUND_BLUE);/////set��ɫ
	Case2_Scan:
		printf("{!}������һ������ʮһλ�����£����س������\n");
		//			printf
		("   Please enter an integer,eleven digits or less,press enter to continue.\n\n");
		printf("[��������]");
		cin >> *numscan;
		if (*numscan < 0)
		{
			cout << endl << "ϵͳ��Ϣ���ݲ�֧�ָ���ļ��㡣��ת�ص���ͷ��" << endl << endl;
			goto Case2_Scan;
		}
		cout << fixed << setprecision(6);	// ��������ʾ����ʹ�ÿ�ѧ����С����ʾ6λ
		*predicttime = (pretime / prenumscan) * *numscan;
		cout << "[Ԥ�ƺ�ʱ]" << *predicttime << " sec." << endl << endl;
		cout << fixed << setprecision(0);	// ��������ʾ����ʹ�ÿ�ѧ����С����ʾ
		if (*predicttime >= 60)
		{
		Select_BigTask_Scan_Default:
			cout <<
				"���������Ԥ������ʱ�����һ���ӣ���⵽���������Ƿ����"
				<< endl;
			cout << "������[0:Y/1:N]";
			long* Select_BigTask_Scan = new long;
			cin >> *Select_BigTask_Scan;
			cout << endl;	// ��һ��
			switch (*Select_BigTask_Scan)
			{
			case 0:
				goto Select_BigTask_Scan_0;
			case 1:
				cout << "������ֹ����ת�ص���ͷ��" << endl <<
					"==============================" << endl << endl;
				goto Case2_Scan;
			default:
				cout << "����Ƿ������������롣" << endl << endl;
				goto Select_BigTask_Scan_Default;
			}			// switch

		}				// if
	Select_BigTask_Scan_0:
		start = clock();	// ��ʼ��ʱ
		if (*numscan == 0 or *numscan == 2)	// �ж������Ƿ�Ϊ0,2
		{
			goto PrimeNum_Output;
		}
		else
		{
			goto Default_Output;
		}
	Default_Output:
		// �����㷨����
		do
		{
			*mid2 = *numscan / *mid1;
			if (*mid2 == (long long)* mid2)
			{
				printf("[������%d] = ", *count);
				cout << *mid1 << endl;
				(*mid1)++;
				(*count)++;
			}
			else
			{
				(*mid1)++;
			}
		} while (*mid1 <= (*numscan / 2) and *count <= 20000);	// while�쳣�ж�
	PrimeNum_Output:
		if (*count == 1)
		{
			cout << "{!}����������" << endl;
		}
		stop = clock();	// ֹͣ��ʱ
		*duration = (float)(stop - start) / CLOCKS_PER_SEC;
		printf("\n{!}���μ��㹲��ʱ%f�롣\n", *duration);
		//			printf("   Processing time is %f sec.\n", *duration);
					// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					// FOREGROUND_INTENSITY | FOREGROUND_GREEN);/////set��ɫ
		printf("{!}ִ����ϣ��޴���No errors.\n");
		// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		// FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
		// FOREGROUND_BLUE);/////set��ɫ
		cout.unsetf(ios::fixed); // �����ʾ��
		delete duration;
		delete numscan, predicttime, mid1, mid2, count;
		goto Select_Num_Scan;
	}						// case 2

	case 3:		// ����С�������������
	{
		double* numscan1 = new double;
		double* numscan2 = new double;
		cout << "{!}����ʼִ�С�" << endl;
	Case3_Scan:
		cout << "{!}���������������" << endl << "[a]=";
		cin >> *numscan1;
		cout << "[b]=";
		cin >> *numscan2;
		if (*numscan1 * *numscan2 <= 0 or *numscan1 + *numscan2 < 0)
		{
			cout << endl << "{!}a,b����һֵ����Ϊ0�������������롣" << endl << endl;
			goto Case3_Scan;
		}
		for (long i = 1; i < *numscan1 + *numscan2; i++)
		{
			if (*numscan1 * i / *numscan2 == (long)* numscan1 * i / (long)* numscan2)
			{
				cout << "��С������Ϊ��" << *numscan1 * i << endl;
				break;
			}
		}
		for (long j = (*numscan1 + *numscan2) / 2; j > 0; j--)	//ab��ӳ���2����������������
		{
			if (*numscan1 / j == (long)* numscan1 / j and *numscan2 / j == (long)* numscan2 / j)
			{
				cout << "���Լ��Ϊ��" << j << endl;
				break;
			}
		}
		//�ͷ��ڴ�
		delete numscan1, numscan2;
		goto Select_Num_Scan;
	}						// case 3

	case 4:		// �ж���ȫƽ����
	{
		double* numscan = new double;
		cout << "{!}����ʼִ�С�" << endl;
	Case4_Scan:
		cout << "{!}������һ��������" << endl << "[a]=";
		cin >> *numscan;
		if (sqrt(*numscan) == (long long)sqrt(*numscan))
		{
			cout << "��������ȫƽ�����ֵΪ��" << sqrt(*numscan) << "." << endl;
		}
		else
		{
			cout << "��������ȫƽ����" << endl;
		}
		delete numscan;
		goto Select_Num_Scan;
	}						// case 4

	case 5:		// �������
	{
		getSortedData_struct input;
		long* numamount = new long;
	Case5_Scan:
		cout << "��������ݵ����" << endl << "[���]";
		cin >> *numamount;
		if (*numamount > 512)
		{
			cout << "�ݲ�֧��512��������ݣ����������롣" << endl;
			goto Case5_Scan;					// ��������
		}
		cout << "��������������" << endl;		// �������
		for (int i = 0; i < *numamount;i++)
		{
			printf("[������%ld] = ", i + 1);
			cin >> input.data_array[i];
		}
		input = getSortedData(input, *numamount);
		
		cout << endl							// ������ϣ������
			 << "��С����������Ϊ��" << endl;
		for (int m = 0; m < *numamount; m++)
		{
			printf("[�����%ld] = ", m + 1);
			cout << input.data_array[m] << endl;
		}
		printf("��������%ld�ν�����\n", input.swapcount);
		delete numamount;
		goto Select_Num_Scan;
	}

	case 6:		// ����Լ��
	{
		long long* numscan1 = new long long;
		long long* numscan2 = new long long;
		simplify_fraction_struct simplified;
		cout << "���������������ֱ���Ϊ���Ӻͷ�ĸ��" << endl
			<< "[����]";
		cin >> *numscan1;
		cout << "[��ĸ]";
		cin >> *numscan2;
		cout << endl;
		simplified = simplify_fraction(*numscan1, *numscan2);
				cout << "���Լ��" << simplified.greatest_common_divisor << endl
					 << "Լ�ֽ��Ϊ��" << endl;
				cout << "[����]" << simplified.simplified_numerator << endl
					 << "[��ĸ]" << simplified.simplified_denominator << endl;
		delete numscan1, numscan2;
		goto Select_Num_Scan;
	}

	case 7:		// ���θ�ʽ����
	{
		long* numscan = new long;
		cout << "������Ҫ����Ķ��θ�ʽ��" << endl << "��";
		cin >> *numscan;
		simplify_quadratic_radical_struct returnNums ;
		returnNums = simplify_quadratic_radical(*numscan);
		cout << "[��ʽ�ֽ�] " << *numscan << " = " << pow(returnNums.out_radical, 2) << " * "
			 << *numscan / pow(returnNums.out_radical, 2) << endl;
		cout << "[������]" << "��" << *numscan << " = ";
		if (returnNums.out_radical != 1)
		{
			cout << returnNums.out_radical;
		}
		if (returnNums.in_radical != 1)
		{
			cout << "��" << returnNums.in_radical;
		}
		cout << endl;
		delete numscan;
		goto Select_Num_Scan;
	}

	case 13:	// ��������
	{
		// �����ڴ�
		long* max = new long;
		long* min = new long;
		long* randnum = new long;
		long* randnumamount = new long;
		cout << "������Ҫ��ɵ���������䡣" << endl;
		cout << "[��Сֵ]" << endl;
		cin >> *min;
		cout << "[���ֵ]" << endl;
		cin >> *max;
		cout << "������Ҫ��ɵ������ĸ���" << endl
			<< "[����]";
		cin >> *randnumamount;
		cout << endl;
		// bug unfixed
		if (*min >= 0)	 // min�ۼ�/��һ�Σ�����ֵ��������bug
		{
			(*min)++;
			for (int i = 0;i < 3;i++)
			{
				(*max)++;
			}
		}
		//else
		{
			(*min)++;

			for (int i = 0;i < 3;i++)
			{
				(*max)++;
			}
		}
		// ��ʼ���ã���������
		for (long i = 0;i < *randnumamount;i++)
		{
			*randnum = getRandData(*min, *max);
			printf("[�����%ld] = ", i+1);
			cout << *randnum << endl;
		}
		

		delete max, min, randnum, randnumamount;
		goto Select_Num_Scan;
	}

	case 14:	// ���κ������ʽ����
		double a, b, c;
		cout << "��ֱ�����������һ��ʽ��a,b,c��ֵ" << endl;
		cout << "[a] = ";
		cin >> a;
		cout << "[b] = ";
		cin >> b;
		cout << "[c] = ";
		cin >> c;
		double x_numerator, x_denominator, y_numerator, y_denominator;				// ����x�ᡢy�����
		// ��ʼ���㣬��ֵ
		x_numerator = -b;
		x_denominator = 2 * a;
		y_numerator = 4 * a * c - b * b;
		y_denominator = 4 * a;
		// ���ú���
		cout << "�Գ���(�������) : ( ";
		displayFraction(simplify_fraction(x_numerator, x_denominator));
		cout << " , ";
		displayFraction(simplify_fraction(y_numerator, y_denominator));
		cout << " )" << endl;
		goto Select_Num_Scan;


	case 0:		// ��ʾ����̨
	{
		loadMasterConsole();
		/*exit(0);			// �˳����*/
	}						// case 0

	default:	// �������
	{
		cout << "ϵͳ��Ϣ:��������ȷ����\n" << endl;
		goto Select_Num_Scan;
	}						// default
	}						// switch
	return 0;
}							// main

/*// Ҫ�õ��ĺ���sqrt(num)��ƽ�� pow(num, 2)ƽ��
   ��ȫƽ�����ж�ģ�� int n; scanf("%d", &n); if (sqrt(n) ==
   (int)sqrt(n)) { printf("����ȫƽ����"); } else {
   printf("������ȫƽ����"); } */

   // ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
   // ���Գ���: F5 ����� >����ʼ���ԡ��˵�
   // ����ʹ�ü���: 
   // 1. ʹ�ý�����Դ����������/�����ļ�
   // 2. ʹ���Ŷ���Դ���������ӵ�Դ�������
   // 3. ʹ�����ڲ鿴�������������Ϣ
   // 4. ʹ�ô����б��ڲ鿴����
   // 5.
   // ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
   // 6.
   // �������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ� 