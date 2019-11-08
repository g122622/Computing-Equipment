// 工程名称：计算工具
// 日期：20190912
// 版本：v1.4.4
// 开发平台：Windows：Microsoft Visual Studio；Android：c4droid


/*----------预处理器/预编译语句加载区----------*/
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <iomanip>
#define enabled 0
#define disabled 1
using namespace std;


/*----------结构体声明区----------*/
// 二次根式化简结构体
struct simplify_quadratic_radical_struct
{
	long in_radical;
	long out_radical;
};

// 冒泡排序结构体
struct getSortedData_struct
{
	long data_array[512];
	long swapcount = 0;
};

// 分数约分结构体
struct simplify_fraction_struct
{
	long simplified_numerator;		// 分子
	long simplified_denominator;	// 分母
	long greatest_common_divisor;	// 最大公约数
	short single_display_state;
	short minus_display_state;
};


/*----------函数声明区----------*/
double getRandData(long, long);
simplify_quadratic_radical_struct getSimplifiedQuadraticRadical(long);
void swapData(long&, long&);
getSortedData_struct getSortedData(getSortedData_struct, long&);
long long loadMasterConsole(long long);
simplify_fraction_struct getSimplifiedFraction(long&, long&);
long getAbsoluteData(long);
void displayFraction(simplify_fraction_struct);
long getGreatestCommonDivisor(long[],long&);


// 获取最大公约数函数
long getGreatestCommonDivisor(long data_array[], long& data_amount)
{
	long GreatestCommonDivisor;
	// 声明结构体，以后再考虑内存释放
	getSortedData_struct temp;	
	for (int i = 0; i < data_amount; i++)		// 输入数全部取绝对值，同时赋值给temp
	{
		temp.data_array[i] = getAbsoluteData(data_array[i]);
	}
	temp = getSortedData(temp, data_amount);	// 函数返回的是结构体，所以可以temp一用到底，从而控制内存占用
	for (int j = temp.data_array[0]; j > 0; j--)// j的最终结果为最大公约数
	{
		for (int k = 0; k < data_amount; k++)
		{
			if ((double)temp.data_array[k] / j != (long)temp.data_array[k] / j)	// 判断是否能整除，若不能则直接break
			{
				break;
			}
			GreatestCommonDivisor = j;			// 如果一直都没有break,则此时j为最大公约数
		}
	}
	return GreatestCommonDivisor;
}

// 生成随机数列的函数
double getRandData(long min, long max)
{	// 计算 0，1之间的随机小数,得到的值域近似为(0,1)
	double m1 = (double)(rand() % 101) / 101;
	// 将区间变为(min+1,max)
	min++;
	// 计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
	double m2 = (double)((rand() % (max - min + 1)) + min);
	// 令值域为[min,max-1]
	m2 = m2 - 1;
	// 返回值域为(min,max),为所求随机浮点数
	return m1 + m2;
}


// 二次根式化简函数
getSimplifiedQuadraticRadical_struct simplify_quadratic_radical(long numscan)
{
	// 使用结构体传参
	simplify_quadratic_radical_struct temp;	// 定义temp结构体
	for (long i = numscan; i > 0; i--)
	{
		if ((double) numscan / i == (long) numscan / i and (double)sqrt(i) == (long)sqrt(i))
			// 第一个条件：确保i为numscan的整因数；第二个条件：确保i是最大的完全平方因数
		{
			temp.in_radical =  numscan / i;	// 输出根号内剩余的数
			temp.out_radical =  sqrt(i);	// 输出根号外分解出来的数
			break;
		}
	}
	return temp;
}


// 数对交换函数
void swapData(long& num1, long& num2)
{
	long* temp = new long;	// 给缓存分配内存空间
	*temp = num2;
	num2 = num1;
	num1 = *temp;
	delete temp;			// 释放内存
}


// 冒泡排序函数
getSortedData_struct getSortedData(getSortedData_struct temp, long& dataamount)
{
	for (int k = 0; k < dataamount; k++)
	{
		for (int j = dataamount - 1; j > 0;j--)
		{
			if (temp.data_array[j] < temp.data_array[j - 1])
			{
				swapData(temp.data_array[j - 1], temp.data_array[j]);	// 交换两个对象
				(temp.swapcount)++;
			}
		}
	}
	return temp;
}


// 分数约分函数
simplify_fraction_struct getSimplifiedFraction(long &numerator, long &denominator)	// 传引用，减少内存占用 
{
	simplify_fraction_struct temp;				// 声明要返回的结构体
	long data_array = new long[2];				// 内存中分配一个数组，用于给公约数模块传参
	// 数组赋值
	data_array[0] = numerator;
	data_array[1] = denominator;
	// 判断分数是否显示负号
	if (temp.simplified_numerator * temp.simplified_denominator >= 0)
	{
		temp.minus_display_state = disabled;
	}
	else
	{
		temp.minus_display_state = enabled;
	}
	temp.single_display_state = enabled;			// 默认启用整数显示
	// 调用公约数函数
	temp.greatest_common_divisor = getGreatestCommonDivisor(data_array[], 2);
	delete[] data_array;					// 释放数组内存
	// 计算约分后的分子和分母
	temp.simplified_numerator = numerator / temp.greatest_common_divisor;
	temp.simplified_denominator = denominator / temp.greatest_common_divisor;
	// 分子分母全部取绝对值
	temp.simplified_numerator = getAbsoluteData(temp.simplified_numerator);
	temp.simplified_denominator = getAbsoluteData(temp.simplified_denominator);
	// 判断是否采用整数显示：如果最大公约数等于分母的绝对值，则启用整数显示
	if (temp.greatest_common_divisor == getAbsoluteData(numerator))
	{
		temp.single_display_state = enabled;
	}
	else
	{
		temp.single_display_state = disabled;
	}
	return temp;
}


// 分数显示函数
void displayFraction(simplify_fraction_struct temp)
{
	if (temp.simplified_numerator != 0)			// 分子若为0，直接显示0
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


// 取绝对值函数
long getAbsoluteData(long numscan)
{
	if (numscan < 0)
	{
		numscan = -numscan;
	}
	return numscan;
}


// 因数分解函数


// 加载总控制台函数
long long loadMasterConsole()
{
	long long SwitchNum;
	cout << "===============[总控制台]===============" << endl
		<< "1::解/分析二元一次方程" << endl
		<< "2::因数分解" << endl
		<< "3::找最小公倍数、最大公因数" << endl
		<< "4::判断完全平方数" << endl
		<< "5::数据排序" << endl
		<< "6::分数约分" << endl
		<< "7::二次根式化简" << endl
		<< "8::二次根式分母有理化" << endl
		<< "9::身份证验证码计算" << endl
		<< "10::条形码验证码计算" << endl
		<< "11::计算平均数、中位数、众数、方差" << endl
		<< "12::计算加权平均数" << endl
		<< "13::生成随机数" << endl
		<< "14::二次函数解析式计算" << endl
		// 备份
		/*
		<< "11::" << endl
		<< "11::" << endl
		<< "11::" << endl
		*/
		<< "0::显示控制台" << endl
		<< "[输入]";
	cin >> SwitchNum;
	cout << "====================" << endl << endl;
	return SwitchNum;
}

clock_t start, stop;				// 初始化计时函数

int main(void)						// 开始执行主函数
{
	long double pretime;
	short speedTestState = enabled;	// 避免多次测速
Select_Num_Scan:
	switch (loadMasterConsole())	// 加载总控制台
	{
	case 1:		// 解/分析二元一次方程
	{
		float* a = new float;		// 用于方程的输入
		float* b = new float;
		float* c = new float;
		float* Delta = new float;
		float* mid2 = new float;	// 方程两根
		float* mid3 = new float;

		int* fzacount = new int;
		long* fzmid1 = new long;					//用于除a和c
		long double* fzmid2 = new long double;		//用于被a除
		int* FZA = new int[512];
		*fzacount = 0;
		*fzmid1 = 1;
		// int m1, d1, m2, d2, m3, d3, mid4, mid5, mid6, d = 0; //
		// 分数运算需要用到的在这里定义，暂时还用不到
		// float mid7, mid8, mid9; //
		// 用于分数除法，暂时还用不到

		std::cout << "{!}程序启动，方程类型：ax^2+bx+c=0 \n" << std::endl;
	A_Scan:
		printf("{!}请输入a的值。 \n");
		printf("[a]");
		cin >> *a;
		if (*a == 0)
		{
			cout <<
				"∵a=0，∴该方程不属于二元一次方程，请重新输入a的值."
				<< endl;
			goto A_Scan;
		}
		else
		{
			goto B_Scan;
		}
	B_Scan:
		printf("{!}请输入b的值。 \n");
		printf("[b]");
		cin >> *b;
		printf("{!}请输入c的值。 \n");
		printf("[c]");
		cin >> *c;
		// 输入结束

		cout << endl;	// 输出空行
		printf("%gx^2+%gx+%g=0 \n\n", *a, *b, *c);

		cout << "由韦达定理，\nx(1)+x(2) = -b/a = " << -*b / *a << "." << endl
			<< "x(1)x(2) = c/a = " << *c / *a << "." << endl << endl;

		std::cout << "[解法1：因式分解法(实验性，bug可能较多)]" << std::endl;
		do
			// 开始a的因数计算循环，a的分解只需要正值即可
		{
			*fzmid2 = *a / *fzmid1;
			if (*fzmid2 == (long long)* fzmid2)
			{
				FZA[*fzacount] = *fzmid1;
				//cout << *fzacount+1 << "→";
				//cout << FZA[*fzacount] << endl;
				//输出流调试
				(*fzmid1)++;
				(*fzacount)++;
			}			// if
			else
			{
				(*fzmid1)++;
			}			// else
		}				// do
		while (*fzmid1 <= *a and *fzacount <= 20000);	//异常中断

		// ///////开始*c的因数计算循环，正负值都要计算，先讨论*c的正负性
		long* fzmid3 = new long;
		*fzmid3 = (long)-*c;	// 设立fzmid3是为了避免数据类型转换的warning
		*fzmid1 = *fzmid3;		// 复位
		delete fzmid3;			// 赋值后即销毁
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
					//cout << FZC[fzccount] << endl;	// 输出流用于调试
					(*fzmid1)++;
					(*fzccount)++;
				}			// if
				else
				{
					(*fzmid1)++;
				}			// else
			}				// do
			while (*fzmid1 <= *c and *fzccount <= 20000);	//异常中断
		}					// if (*c>0)
		else				//*c的负数因数计算模块（新）
		{
			do
				// 开始*c的因数计算循环，正负值都要计算
			{
				*fzmid2 = *c / *fzmid1;
				if (*fzmid2 == (long long)* fzmid2)
				{
					FZC[*fzccount] = *fzmid1;
					//cout << FZC[fzccount] << "test" << endl;	// 输出流用于调试
					(*fzmid1)--;
					(*fzccount)++;
				}			// if
				else
				{
					(*fzmid1)--;
				}			// else
			}				// do
			while (*fzmid1 >= *c and *fzccount <= 20000);	//异常中断
		}					//if（first-else）

							// 因数计算完成，开始for循环+if条件匹配
		for (int i = 0; i <= *fzccount; i++)
		{
			for (int j = 0; j <= *fzacount; j++)
			{
				if (FZA[j] * (*c / FZC[i]) + FZC[i] * (*a / FZA[j]) == *b)//触发输出的条件
				{
					// ！！！开始输出 Output
					if (FZC[i] == *c / FZC[i] and FZA[j] == *a / FZA[j]) //输出完全平方
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
						cout << "x " << FZC[i] << " = 0，或 ";
					}
					else
					{
						cout << "x + " << FZC[i] << " = 0，或 ";
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
					cout << "x + " << FZC[i] << " ) = 0，或 ( ";
					cout << *a / FZA[j] << "x + " << *c / FZC[i] << " ) = 0" << endl;
					*/
					if ((float)-FZC[i] / FZA[j] == (float)(-*c / FZC[i]) / (*a / FZA[j]))	//以等根形式输出结果
					{
					EqualRoot_Output:
						cout << "∴x(1)=x(2)=" << (float)-FZC[i] / FZA[j] << "." << endl << endl;
					}
					else	//以不等根形式输出结果
					{
						cout << "∴x(1)=" << (float)-FZC[i] / FZA[j];
						cout << "，x(2)=" << (float)(-*c / FZC[i]) / (*a / FZA[j]) << "." << endl;
						cout << endl;	// 空一行
					}
					goto Method_2;	// 跳出两层for循环
				}		// if
			}			// for Aj
		}				// for Ci

		cout << "{!}该方程不可因式分解!" << endl << endl;
	Method_2:
		std::cout << "[解法2：公式法]" << std::endl;
		// 判断&运算模块of公式法
		*Delta = pow(*b, 2) - 4 * *a * *c;
		printf("Δ=%g^2-4×%g×%g=%g. \n", *b, *a, *c, *Delta);
		if (*Delta > 0)	// ///如果判别式大于零
		{
			if (sqrt(*Delta) == (int)sqrt(*Delta))
			{
				//是完全平方数
				*mid2 = (-1 * *b + sqrt(*Delta)) / (2 * *a);
				*mid3 = (-1 * *b - sqrt(*Delta)) / (2 * *a);
				// =====公式法开始输出=====
	 /*------------------输出模块（判别式大于零,且为完全平方）of公式法------------------*/
				std::cout << "∵Δ>0，∴方程有两个不相等的实数根." <<
					std::endl;
				printf("∴x(1)=%g，x(2)=%g. \n", *mid2, *mid3);
			}
			else
			{
				//不是完全平方数
				*mid2 = -*b;
				*mid3 = 2 * *a;
				/*------------------输出模块（判别式大于零,且不为完全平方）of公式法------------------*/
				std::cout << "∵Δ>0，∴方程有两个不相等的实数根." <<
					std::endl;
				printf("∴x(1) =（%g+√%g）/ %g，x(2) =（%g-√%g）/ %g. \n", *mid2,
					*Delta, *mid3, *mid2, *Delta, *mid3);
			}
		}
		else			// 如果判别式不大于零
		{
			if (*Delta == 0)	// ///如果判别式为零，则不需要判定Δ是否为完全平方
			{
				*mid2 = (-1 * *b + sqrt(*Delta)) / (2 * *a);
				/*------------------输出模块（判别式等于零，且为完全平方）of公式法------------------*/
				std::cout << "∵Δ=0，∴方程有两个相等的实数根." <<
					std::endl;
				printf("∴x(1)=x(2)=%g. \n", *mid2);
			}
			else		// ///判别式为负，无实数根
			{
				/*------------------输出模块（判别式小于零）of公式法------------------*/
				std::cout << "∵Δ<0,∴方程没有实数根.\n{!}计算中止." <<
					std::endl;
			}			// else
		}				// else
						// =====分数模块
						/* }//来自if mid1 = 0,1,2,3,4,5,6,7,8,9 为假的判断//
		   else { std::cout <<
		   "输入分数请用“/”作为分数线 " << std::endl;
		   std::cout << "请输入a的值 " << std::endl;
		   scanf("%d/%d", &m1, &d1); std::cout << "请输入*b的值 "
		   << std::endl; scanf("%d/%d", &m2, &d2); std::cout <<
		   "请输入c的值 " << std::endl; scanf("%d/%d", &m3, &d3);
		   }			*/
		   //释放内存
		delete a, b, c, Delta, mid2, mid3;
		delete[] FZA, FZC;
		delete fzacount, fzccount, fzmid1, fzmid2;
		goto Select_Num_Scan;
	}						// case1

	case 2:		// 因数分解
	{
		long double prenumscan = 4777778;
		if (speedTestState == enabled) // 避免重复测速
		{
			long double* premid1 = new long double;
			long double* premid2 = new long double;
			int* precount = new int;
			*premid1 = 2;
			*precount = 1;
			cout << "{!}程序开始执行。\n[正在测速，请稍侯。调试信息请忽略。]" << endl;
			start = clock();	// 开始测速
			do
			{
				*premid2 = prenumscan / *premid1;
				if (*premid2 == (long long)* premid2)
				{
					printf("IF_%d = ", *precount);
					cout << *premid1;
					cout << endl;	// 输出一个换行符
					(*premid1)++;
					(*precount)++;
				}
				else
				{
					(*premid1)++;
				}
			} while (*premid1 <= (prenumscan / 2) and *precount <= 20000);	// while异常中断
			stop = clock();		// 停止测速
			pretime = (float)(stop - start) / CLOCKS_PER_SEC;
			cout << "Time=" << pretime << endl << "测速完成。" << endl << endl;
			speedTestState = disabled;
			delete premid1, premid2, precount;
		}
		// 测速结束
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
		// FOREGROUND_BLUE);/////set白色
	Case2_Scan:
		printf("{!}请输入一个整数，十一位数及以下，按回车键继续。\n");
		//			printf
		("   Please enter an integer,eleven digits or less,press enter to continue.\n\n");
		printf("[输入整数]");
		cin >> *numscan;
		if (*numscan < 0)
		{
			cout << endl << "系统消息：暂不支持负数的计算。跳转回到开头。" << endl << endl;
			goto Case2_Scan;
		}
		cout << fixed << setprecision(6);	// 锁定浮点数显示，不使用科学计数法，小数显示6位
		*predicttime = (pretime / prenumscan) * *numscan;
		cout << "[预计耗时]" << *predicttime << " sec." << endl << endl;
		cout << fixed << setprecision(0);	// 锁定浮点数显示，不使用科学计数法，小数不显示
		if (*predicttime >= 60)
		{
		Select_BigTask_Scan_Default:
			cout <<
				"你输入的数预计运算时间大于一分钟，检测到大型任务，是否继续？"
				<< endl;
			cout << "请输入[0:Y/1:N]";
			long* Select_BigTask_Scan = new long;
			cin >> *Select_BigTask_Scan;
			cout << endl;	// 空一行
			switch (*Select_BigTask_Scan)
			{
			case 0:
				goto Select_BigTask_Scan_0;
			case 1:
				cout << "计算中止，跳转回到开头。" << endl <<
					"==============================" << endl << endl;
				goto Case2_Scan;
			default:
				cout << "输入非法！请重新输入。" << endl << endl;
				goto Select_BigTask_Scan_Default;
			}			// switch

		}				// if
	Select_BigTask_Scan_0:
		start = clock();	// 开始计时
		if (*numscan == 0 or *numscan == 2)	// 判断输入是否为0,2
		{
			goto PrimeNum_Output;
		}
		else
		{
			goto Default_Output;
		}
	Default_Output:
		// 核心算法部分
		do
		{
			*mid2 = *numscan / *mid1;
			if (*mid2 == (long long)* mid2)
			{
				printf("[整因数%d] = ", *count);
				cout << *mid1 << endl;
				(*mid1)++;
				(*count)++;
			}
			else
			{
				(*mid1)++;
			}
		} while (*mid1 <= (*numscan / 2) and *count <= 20000);	// while异常中断
	PrimeNum_Output:
		if (*count == 1)
		{
			cout << "{!}该数是质数。" << endl;
		}
		stop = clock();	// 停止计时
		*duration = (float)(stop - start) / CLOCKS_PER_SEC;
		printf("\n{!}本次计算共耗时%f秒。\n", *duration);
		//			printf("   Processing time is %f sec.\n", *duration);
					// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
					// FOREGROUND_INTENSITY | FOREGROUND_GREEN);/////set绿色
		printf("{!}执行完毕，无错误。No errors.\n");
		// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		// FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
		// FOREGROUND_BLUE);/////set白色
		cout.unsetf(ios::fixed); // 消除显示锁定
		delete duration;
		delete numscan, predicttime, mid1, mid2, count;
		goto Select_Num_Scan;
	}						// case 2

	case 3:		// 找最小公倍数、最大公因数
	{
		double* numscan1 = new double;
		double* numscan2 = new double;
		cout << "{!}程序开始执行。" << endl;
	Case3_Scan:
		cout << "{!}请输入两个正整数：" << endl << "[a]=";
		cin >> *numscan1;
		cout << "[b]=";
		cin >> *numscan2;
		if (*numscan1 * *numscan2 <= 0 or *numscan1 + *numscan2 < 0)
		{
			cout << endl << "{!}a,b中任一值不可为0或负数，请重新输入。" << endl << endl;
			goto Case3_Scan;
		}
		for (long i = 1; i < *numscan1 + *numscan2; i++)
		{
			if (*numscan1 * i / *numscan2 == (long)* numscan1 * i / (long)* numscan2)
			{
				cout << "最小公倍数为：" << *numscan1 * i << endl;
				break;
			}
		}
		for (long j = (*numscan1 + *numscan2) / 2; j > 0; j--)	//ab相加除以2，避免做无用运算
		{
			if (*numscan1 / j == (long)* numscan1 / j and *numscan2 / j == (long)* numscan2 / j)
			{
				cout << "最大公约数为：" << j << endl;
				break;
			}
		}
		//释放内存
		delete numscan1, numscan2;
		goto Select_Num_Scan;
	}						// case 3

	case 4:		// 判断完全平方数
	{
		double* numscan = new double;
		cout << "{!}程序开始执行。" << endl;
	Case4_Scan:
		cout << "{!}请输入一个正整数：" << endl << "[a]=";
		cin >> *numscan;
		if (sqrt(*numscan) == (long long)sqrt(*numscan))
		{
			cout << "该数是完全平方数。开方值为：" << sqrt(*numscan) << "." << endl;
		}
		else
		{
			cout << "该数不是完全平方数。" << endl;
		}
		delete numscan;
		goto Select_Num_Scan;
	}						// case 4

	case 5:		// 数据排序
	{
		getSortedData_struct input;
		long* numamount = new long;
Case5_Scan:
		cout << "请输入数据的数量" << endl << "[数量]";
		cin >> *numamount;
		if (*numamount > 512)
		{
			cout << "暂不支持512个以上数据，请重新输入。" << endl;
			goto Case5_Scan;					// 重新输入
		}
		cout << "请依次输入各个数据" << endl;		// 输入数据
		for (int i = 0; i < *numamount;i++)
		{
			printf("[输入数%ld] = ", i + 1);
			cin >> input.data_array[i];
		}
		input = getSortedData(input, *numamount);
		
		cout << endl							// 计算完毕，输出结果
			 << "从小到大排序结果为：" << endl;
		for (int m = 0; m < *numamount; m++)
		{
			printf("[输出数%ld] = ", m + 1);
			cout << input.data_array[m] << endl;
		}
		printf("共进行了%ld次交换。\n", input.swapcount);
		delete numamount;
		goto Select_Num_Scan;
	}

	case 6:		// 分数约分
	{
		long long* numscan1 = new long long;
		long long* numscan2 = new long long;
		simplify_fraction_struct simplified;
		cout << "请输入两个正整数，分别作为分子和分母。" << endl
			<< "[分子]";
		cin >> *numscan1;
		cout << "[分母]";
		cin >> *numscan2;
		cout << endl;
		simplified = simplify_fraction(*numscan1, *numscan2);
				cout << "最大公约数：" << simplified.greatest_common_divisor << endl
					 << "约分结果为：" << endl;
				cout << "[分子]" << simplified.simplified_numerator << endl
					 << "[分母]" << simplified.simplified_denominator << endl;
		delete numscan1, numscan2;
		goto Select_Num_Scan;
	}

	case 7:		// 二次根式化简
	{
		long* numscan = new long;
		cout << "请输入要化简的二次根式：" << endl << "√";
		cin >> *numscan;
		simplify_quadratic_radical_struct returnNums ;
		returnNums = simplify_quadratic_radical(*numscan);
		cout << "[因式分解] " << *numscan << " = " << pow(returnNums.out_radical, 2) << " * "
			 << *numscan / pow(returnNums.out_radical, 2) << endl;
		cout << "[化简结果]" << "√" << *numscan << " = ";
		if (returnNums.out_radical != 1)
		{
			cout << returnNums.out_radical;
		}
		if (returnNums.in_radical != 1)
		{
			cout << "√" << returnNums.in_radical;
		}
		cout << endl;
		delete numscan;
		goto Select_Num_Scan;
	}

	case 13:	// 生成随机数
	{
		// 申请内存
		long* max = new long;
		long* min = new long;
		long* randnum = new long;
		long* randnumamount = new long;
		cout << "请输入要生成的随机数的区间。" << endl;
		cout << "[最小值]" << endl;
		cin >> *min;
		cout << "[最大值]" << endl;
		cin >> *max;
		cout << "请输入要生成的随机数的个数。" << endl
			<< "[个数]";
		cin >> *randnumamount;
		cout << endl;
		// bug unfixed
		if (*min >= 0)	 // min累加/减一次，避免值域出问题的bug
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
		// 开始调用，生成随机数
		for (long i = 0;i < *randnumamount;i++)
		{
			*randnum = getRandData(*min, *max);
			printf("[输出数%ld] = ", i+1);
			cout << *randnum << endl;
		}
		

		delete max, min, randnum, randnumamount;
		goto Select_Num_Scan;
	}

	case 14:	// 二次函数解析式计算
		double a, b, c;
		cout << "请分别输入抛物线一般式的a,b,c的值" << endl;
Case5_a_Scan:
		cout << "[a] = ";
		cin >> a;
		if (a == 0)
		{
			cout << "a不可为0！" << endl;
			goto Case5_a_Scan;
		}
		cout << "[b] = ";
		cin >> b;
		cout << "[c] = ";
		cin >> c;
		double x_numerator, x_denominator, y_numerator, y_denominator;				// 声明x轴、y轴坐标
		// 开始运算，赋值
		x_numerator = -b;
		x_denominator = 2 * a;
		y_numerator = 4 * a * c - b * b;
		y_denominator = 4 * a;
		// 调用函数
		cout << "对称轴(顶点坐标) : ( ";
		displayFraction(simplify_fraction(x_numerator, x_denominator));
		cout << " , ";
		displayFraction(simplify_fraction(y_numerator, y_denominator));
		cout << " )" << endl;
		goto Select_Num_Scan;


	case 0:		// 显示控制台
	{
		loadMasterConsole();
		/*exit(0);			// 退出程序*/
	}						// case 0

	default:	// 输入错误
	{
		cout << "系统消息:请输入正确的数。\n" << endl;
		goto Select_Num_Scan;
	}						// default
	}						// switch
	return 0;
}							// main

/*// 要用到的函数：sqrt(num)开平方 pow(num, 2)平方
   完全平方数判断模块 int n; scanf("%d", &n); if (sqrt(n) ==
   (int)sqrt(n)) { printf("是完全平方数"); } else {
   printf("不是完全平方数"); } */

   // 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
   // 调试程序: F5 或调试 >“开始调试”菜单
   // 入门使用技巧: 
   // 1. 使用解决方案资源管理器窗口添加/管理文件
   // 2. 使用团队资源管理器窗口连接到源代码管理
   // 3. 使用输出窗口查看生成输出和其他消息
   // 4. 使用错误列表窗口查看错误
   // 5.
   // 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
   // 6.
   // 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件 
