// 工程名称：计算工具
// 日期：20200102
// 版本：v1.4.4
// 开发平台：Windows：Microsoft Visual Studio；Notepad++；Android：c4droid；Web：Github
// 开发语言：C++
// 应用类型：控制台应用
// 云同步平台：Github
// 开放源代码状态：开源

// 这个程序为解决初中阶段各种繁琐的数学运算而设计。
// 这是我在学习之余写的程序，下面是所有源代码。
// 未经允许严禁私自转载。严禁私改版权。
// 使用本程序内的算法需征得我（以及原作者）的授权。
// 除非这个算法是你自己独立写出来的qwq
// 之所以我不加密就是为了方便他人借鉴学习。
// 但这不意味着您可以“借鉴”走全部源代码作为自己的作品！
// 我很反感那种拿别人劳动成果盈利的人。
// 这里的盈利指利用别人的作品得到的各种好处。
// 如果你不这么觉得，→_→我只能鄙视你。


/*----------预处理器/预编译语句加载区----------*/
#include <iostream>
#include <cstdio> 
#include <cmath>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#define enabled 0
#define disabled 1
#define FZA factor_a.data_array
#define FZC factor_c.data_array
#define abnormality -1
#define add			0
#define subtract	1
#define multiply	2
#define divide		3


/*----------全局变量/结构体/对象声明区/杂项区1----------*/
typedef long var;
using namespace std;
const int times = 50;
int number = 0;
const int factor[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};// 加权因子
const int check_table[] = {1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2};// 校验值对应表



/*----------结构体声明区----------*/
// 二次根式化简结构体
struct simplify_quadratic_radical_struct
{
	long in_radical;
	long out_radical;
};

// 通用结构体1
struct general_struct_1
{
	vector<long> data_array;	// 这里使用了vector动态向量容器（实验性）
	long count = 0;
};

// 分数约分结构体
struct simplify_fraction_struct
{
	long simplified_numerator;		// 分子
	long simplified_denominator;	// 分母
	long greatest_common_divisor;	// 最大公约数
	bool single_display_state;
	bool minus_display_state;
};


/*----------函数声明区----------*/
double getRandData(long, long);
simplify_quadratic_radical_struct getSimplifiedQuadraticRadical(long);
void swapData(long&, long&);
general_struct_1 getSortedData(general_struct_1, long&);
simplify_fraction_struct getSimplifiedFraction(long&, long&);
template <typename T1>
T1 getAbsoluteData(T1);
void displayFraction(simplify_fraction_struct);
long getGreatestCommonDivisor(general_struct_1);
general_struct_1 getFactor(long, bool);
long getLowestCommonMultiple(simplify_fraction_struct);
long getSumData(general_struct_1);
// 以下都是miller_rabin算法分解质因数所需要的函数（by 倚剑笑紅尘）
void find(long long n, long long c);
long long pollard_rho(long long n, long long c);
long long gcd(long long a, long long b);
bool miller_rabin(long long n);
bool witness(long long a, long long n);
long long q_pow(long long a, long long b, long long mod);
long long q_mul(long long a, long long b, long long mod);
long long Random(long long n);
// 以下都是身份证验证码计算所需要的函数（by boshuzhang）
int _checkIDinput(char[]);
void _checkID(int[], char[]);


/*----------函数定义区----------*/
// 计算最小公倍数函数
long getLowestCommonMultiple(general_struct_1 temp)
{
	long data_amount = temp.count;				// 非引用
	// 数据预处理1：输入数全部取绝对值，同时赋值给temp
	for (var i = 0; i < data_amount; i++)
		temp.data_array[i] = getAbsoluteData(temp.data_array[i]);
	// 数据预处理2：冒泡排序，选出最小值(函数返回值类型为结构体，可以函数全局使用temp，但count已失效）
	temp = getSortedData(temp, data_amount);
	// 数据预处理3：删除值为零的元素，容器大小相应缩减
	for (vector<var>::iterator iter = temp.data_array.begin(); iter != temp.data_array.end(); ++iter)
	{
		if (*iter == 0)
		{
			iter = temp.data_array.erase(iter);
			data_amount--;
			--iter;			// 由于删除了一个元素，将迭代器指针前移
		}
		else break;
		if (iter == temp.data_array.end()) break;	// 额外的判断，避免越界
	}
	//<---数据预处理结束--->
	long LowestCommonMultiple;
	// 这两个临时值为缩减代码横向体积而设立，便于编辑和浏览
	double* dm1 = new double;
	long* lm2 = new long;
	for (var i = 1; i > 0; i++)
	{
		LowestCommonMultiple = temp.data_array[data_amount - 1] * i;	// 选取最大值
		for (var j = data_amount - 2; j >= 0; j--)	// 选取第二大的值
		{
			*dm1 = (double)LowestCommonMultiple / temp.data_array[j];
			*lm2 = (long)LowestCommonMultiple / temp.data_array[j];
			if (*dm1 != *lm2) break;	// 若不符合条件，直接break掉内层循环
			if (j == 0)			// 判断是否全部满足
				delete dm1, lm2;
				return LowestCommonMultiple;
		}
	}
	delete dm1, lm2;
	return abnormality;			// 返回异常值
}


// 因数分解函数（count从零开始）
general_struct_1 getFactor(long num_input, bool minus_output_state)
{
	general_struct_1 temp;
	for (var factor = 1; factor <= (num_input / 2); factor++)
	{
		if ((double)num_input / factor == (long)num_input / factor)
		{
			// 初始化容器内存，插入新元素
			temp.data_array.push_back(0);
			temp.data_array[temp.count] = factor;
			temp.count++;
		}
	}
	temp.data_array.push_back(0);
	temp.data_array[temp.count] = num_input;// 这里的count计数器不可再累加，巧妙避免其比预期值大1
	if (minus_output_state == enabled)
	{
		// 如果启用负数显示，往内存中再存负数
		for (long i = 0; i <= temp.count; i++)
		{
			temp.data_array.push_back(0);
			temp.data_array[temp.count+1] = - temp.data_array[i];
		}
		temp.count = temp.count * 2;
	}
	return temp;
}


// 计算最大公约数函数
long getGreatestCommonDivisor(general_struct_1 temp)
{
	long data_amount = temp.count;				// 不可使用引用，避免count的值被冒泡排序函数所改变
	// 数据预处理1：输入数全部取绝对值，同时赋值给temp
	for (var i = 0; i < data_amount; i++)
		temp.data_array[i] = getAbsoluteData(temp.data_array[i]);
	// 数据预处理2：冒泡排序，选出最小值(函数返回值类型为结构体，可以函数全局使用temp，但count已失效）
	temp = getSortedData(temp, data_amount);
	// 数据预处理3：删除值为零的元素，容器大小相应缩减
	for (vector<var>::iterator iter = temp.data_array.begin(); iter != temp.data_array.end(); ++iter)
	{
		if (*iter == 0)
		{
			iter = temp.data_array.erase(iter);
			data_amount--;
			--iter;			// 由于删除了一个元素，将迭代器指针前移
		}
		else break;
		if (iter == temp.data_array.end()) break;	// 额外的判断，避免越界
	}
	//<---数据预处理结束--->
	for (var j = temp.data_array[0]; j > 0; j--)	// 选取最小数进行嵌套循环，j的最终结果为最大公约数
	{
		for (var k = data_amount - 1; k >= 0; k--)
		{
			// 判断是否能整除，若不能则直接break
			if ((double)temp.data_array[k] / j != (long)temp.data_array[k] / j)
				break;
			if (k == 0)		// 如果一直算到k=0，都没有break，则此时j为最大公约数
				return j;
		}
	}
	return abnormality;
}


// 生成随机数列的函数（by zzy_1988）
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
simplify_quadratic_radical_struct simplifyQuadraticRadical(long numscan)
{
	// 使用结构体传参
	simplify_quadratic_radical_struct temp;	// 定义temp结构体
	for (long i = numscan; i > 0; i--)
	{
		if ((double)numscan / i == (long)numscan / i and (double)sqrt(i) == (long)sqrt(i))
			// 第一个条件：确保i为numscan的整因数；第二个条件：确保i是最大的完全平方因数
		{
			temp.in_radical = numscan / i;	// 输出根号内剩余的数
			temp.out_radical = sqrt(i);	// 输出根号外分解出来的数
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


// 冒泡排序函数（从小到大）
general_struct_1 getSortedData(general_struct_1 temp, long& dataamount)
{
	for (int k = 0; k < dataamount; k++)
	{
		for (int j = dataamount - 1; j > 0;j--)
		{
			if (temp.data_array[j] < temp.data_array[j - 1])
			{
				swapData(temp.data_array[j - 1], temp.data_array[j]);	// 交换两个元素
				temp.count++;
			}
		}
	}
	return temp;
}


// 分数约分函数
simplify_fraction_struct getSimplifiedFraction(long& numerator, long& denominator)	// 传引用，减少内存占用 
{
	simplify_fraction_struct temp;				// 声明要返回的专用结构体
	general_struct_1 gcd;						// 公约数传参用此通用结构体
	// 数组赋值
	gcd.data_array.push_back(0);
	gcd.data_array.push_back(0);
	gcd.data_array[0] = numerator;
	gcd.data_array[1] = denominator;
	gcd.count = 2;
	// 调用公约数函数
	temp.greatest_common_divisor = getGreatestCommonDivisor(gcd);
	// 计算约分后的分子和分母
	temp.simplified_numerator = numerator / temp.greatest_common_divisor;
	temp.simplified_denominator = denominator / temp.greatest_common_divisor;
	// 判断分数是否显示负号
	if (temp.simplified_numerator * temp.simplified_denominator >= 0)
		temp.minus_display_state = disabled;
	else
		temp.minus_display_state = enabled;
	// 分子分母全部取绝对值
	temp.simplified_numerator = getAbsoluteData(temp.simplified_numerator);
	temp.simplified_denominator = getAbsoluteData(temp.simplified_denominator);
	// 默认启用整数显示（如果有特殊情况）
	temp.single_display_state = enabled;
	// 判断是否采用整数显示：如果最大公约数等于分母的绝对值，则启用整数显示
	if (temp.greatest_common_divisor == getAbsoluteData(denominator))
		temp.single_display_state = enabled;
	else
		temp.single_display_state = disabled;
	return temp;
}


// 分数显示函数
void displayFraction(simplify_fraction_struct temp)
{
	if (temp.simplified_numerator != 0)			// 分子若为0，直接显示0
	{
		if (temp.minus_display_state == enabled)
			cout << "-";
		if (temp.single_display_state == disabled)
			cout << temp.simplified_numerator << "/" << temp.simplified_denominator;
		else
			cout << temp.simplified_numerator;
	}
	else
		cout << "0";
}


// 取绝对值函数
template <typename T1>
T1 getAbsoluteData(T1 numscan)
{
	if (numscan < 0)
		numscan = -numscan;
	return numscan;
}


// 求和函数
long getSumData(vector<long> temp)
{
	long count = temp.size();
	long sum = 0;
	for (var i = 0; i < count; i++)
		sum = sum + temp[i];
	return sum;
}


// 以下都是miller_rabin算法分解质因数所需要的函数（by 倚剑笑紅尘）
map<long long, int>m;
long long Random(long long n)
{
	return ((double)rand() / RAND_MAX * n + 0.5);
}


long long q_mul(long long a, long long b, long long mod) // 快速乘法取模
{
	long long ans = 0;
	while (b)
	{
		if (b & 1)
		{
			ans += a;
		}
		b /= 2;
		a = (a + a) % mod;
	}
	return ans;
}


long long q_pow(long long a, long long b, long long mod) // 快速乘法下的快速幂
{
	long long ans = 1;
	while (b)
	{
		if (b & 1)
		{
			ans = q_mul(ans, a, mod);
		}
		b /= 2;
		a = q_mul(a, a, mod);
	}
	return ans;
}


bool witness(long long a, long long n)	// miller_rabin算法的精华
{
	long long tem = n - 1;
	int j = 0;
	while (tem % 2 == 0)
	{
		tem /= 2;
		j++;
	}

	long long x = q_pow(a, tem, n);		// 得到a^(n-1) mod n
	if (x == 1 || x == n - 1) return true;
	while (j--)
	{
		x = q_mul(x, x, n);
		if (x = n - 1) return true;
	}
	return false;
}


bool miller_rabin(long long n)  // 检验n是否是素数
{

	if (n == 2)
		return true;
	if (n < 2 || n % 2 == 0)
		return false;
	for (int i = 1; i <= times; i++)		// 做times次随机检验
	{
		long long a = Random(n - 2) + 1;	// 得到随机检验算子 a
		if (!witness(a, n))					// 用a检验n是否是素数
			return false;
	}
	return true;
}


long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}


long long pollard_rho(long long n, long long c)// 找到n的一个因子
{
	long long x, y, d, i = 1, k = 2;
	x = Random(n - 1) + 1;
	y = x;
	while (1)
	{
		i++;
		x = (q_mul(x, x, n) + c) % n;
		d = gcd(y - x, n);
		if (1 < d && d < n)
			return d;
		if (y == x)		// 找到循环，选取失败，重新来
			return n;
		if (i == k)		// 似乎是一个优化，但是不是很清楚
		{
			y = x;
			k <<= 1;
		}
	}
}


void find(long long n, long long c)
{
	if (n == 1)
		return;
	if (miller_rabin(n))
	{
		m[n]++;
		number++;
		return;
	}
	long long p = n;
	while (p >= n)
		p = pollard_rho(p, c--);
	find(p, c);
	find(n / p, c);
}


// 以下都是身份证验证码计算所需要的函数（by boshuzhang）
int _checkIDinput(char ID[])		// 检验身份证是否为18位 
{ 
	if (strlen(ID) == 18)	// 字符串最后一位/0 
		return 1;
	else return 0;
}


void _checkID(int IDNumber[], char ID[])
{
	int i = 0;	// i为计数器
	int checksum = 0;
	for ( ; i < 17; i++)
		checksum += IDNumber[i] * factor[i];
	if ( IDNumber[17] == check_table[checksum % 11] or (ID[17] == 'x' and check_table[checksum % 11] == 2))
		cout << "正确身份证号码/n";
	else cout << "错误身份证号码/n"; 
}


/*----------对象声明区----------*/
class action
{
	public:
	// 加载总控制台函数
	void showMasterConsole()
	{
		cout << "===============[总控制台]===============" << endl
			<< "1::解/分析二元一次方程" << endl
			<< "2::因数分解" << endl
			<< "3::找最小公倍数、最大公因数" << endl
			<< "4::判断完全平方数" << endl
			<< "5::数据排序" << endl
			<< "6::分数约分" << endl
			<< "7::二次根式化简" << endl
			<< "8::直线到直线距离计算" << endl
			<< "9::点到直线距离计算" << endl
			<< "10::点到点距离计算" << endl
			<< "11::计算平均数、中位数、众数、方差" << endl
			<< "12::计算加权平均数" << endl
			<< "13::生成随机数" << endl
			<< "14::二次函数解析式计算" << endl
			<< "15::分解质因数" << endl
			<< "16::身份证验证码计算" << endl
			// 备份
			/*
			<< "17::" << endl
			<< "17::" << endl
			<< "17::" << endl
			*/
			<< "0::显示总控制台" << endl;
	}
	// 显示错误信息函数
	void showInputErrorMsg()
	{
		cout << "系统消息：请输入正确的数。\n" << endl;
	}
};


class display_mult
{
	private:
	// 转储mult
	vector<long> numerator_constant_array;
	vector<long> numerator_radical_array;
	vector<long> denominator_constant_array;
	vector<long> denominator_radical_array;
	general_struct_1 gcd_tmp;	// 用于计算公约数
	long n_constant_merged = 0, d_constant_merged = 0;
	long gcd = 1;

	// 化简根式函数
	void simplifyRadical(vector<long>& temp, long& cst)
	{
		// 数据预处理：删除为0的元素
		for (var i = 0; i < temp.size(); i++)
		{
			if (temp[i] == 0)
			{
				temp.erase(temp.begin() + i);
				i--;
			}
		}
		// 检查容器是否有数据
		if (temp.empty()) return;
		simplify_quadratic_radical_struct sqr;
		long end_const = temp.size();	// 缓冲常量，避免temp.end()内存地址随元素的插入而改变
		// 计算+暂存
		for (var i = 0; i < end_const; i++)
		{
			sqr = simplifyQuadraticRadical(temp[i]);
			if (sqr.in_radical == 1)		// 若可以开完全平方，则加入常数项
			{
				cst = cst + sqr.out_radical;
				continue;
			}
			temp.push_back(sqr.out_radical);
			temp.push_back(sqr.in_radical);
		}
		temp.erase(temp.begin(), temp.begin() + end_const);	// 清除原数据
		for (int i = 0; i < temp.size(); i++)
			cout << temp[i] << endl;
	}
	
	// 合并根式函数
	void mergeRadical(vector<long>& temp)
	{
		// 检查容器是否有数据
		if (temp.empty()) return;
		for (var j = 1; j < temp.size(); j = j + 2)
		{
			for (var i = 1; i < temp.size(); i = i + 2)
			{
				if (j == i) continue;	// 避免错误计算
				if (temp[j] == temp[i])
				{
					temp[j - 1] = temp[j - 1] + temp[i - 1];
					temp.erase(temp.begin() + i - 1, temp.begin() + i + 1);	// 删除已被合并的数据
					// 计数器缩回
					i = i - 2;
					if (j > i)
						j = j - 2;	// j在i右边，j的指向随删除而改变
				}
			}
		}
		// 检查系数，删除系数为零的项
		for (var i = 0; i < temp.size(); i = i + 2)
		{
			if (temp[i] == 0)
			{
				temp.erase(temp.begin() + i, temp.begin() + i + 2);
				i = i - 2;
			}
		}
	}
	
	void selectCoefficient(vector<long> temp)
	{
		for (var i = 0; i < temp.size(); i = i + 2)
			gcd_tmp.data_array.push_back(temp[i]);
	}

	void displayLine(long cst, vector<long> vectmp, long gcd)
	{
			if (cst != 0)
				cout << cst / gcd << " ";
			for (var j = 0; j < vectmp.size(); j = j + 2)
			{
				// 前部分（系数）
				if (vectmp[j] == 0 || vectmp[j + 1] == 0) continue;
				if (vectmp[j] / gcd < 0)
					cout << "- ";
				else if (cst != 0)
					cout << "+ ";
				if (getAbsoluteData(vectmp[j] / gcd) != 1)
					cout << getAbsoluteData(vectmp[j] / gcd);
				// 后部分（根号）(不用考虑根号内为1的情况）
				cout << "√" << vectmp[j + 1];
			}
	}

	public:
	void setNumerator_constant(long nci)
	{
		numerator_constant_array.push_back(nci);
	}
	void setNumerator_radical(long nri)
	{
		if (nri < 0)
			cout << "error! minus-nums is not expected!" << endl;
		numerator_radical_array.push_back(getAbsoluteData(nri));
	}
	void setDenominator_constant(long dci)
	{
		denominator_constant_array.push_back(dci);
	}
	void setDenominator_radical(long dri)
	{
		if (dri < 0)
			cout << "error! minus-nums is not expected!" << endl;
		denominator_radical_array.push_back(getAbsoluteData(dri));
	}
	void displayMult() throw (runtime_error, bad_alloc)
	{
		n_constant_merged = getSumData(numerator_constant_array);
		d_constant_merged = getSumData(denominator_constant_array);
		simplifyRadical(numerator_radical_array, n_constant_merged);
		simplifyRadical(denominator_radical_array, d_constant_merged);
		mergeRadical(numerator_radical_array);
		mergeRadical(denominator_radical_array);
		gcd_tmp.data_array.push_back(n_constant_merged);
		gcd_tmp.data_array.push_back(d_constant_merged);
		selectCoefficient(numerator_radical_array);
		selectCoefficient(denominator_radical_array);
		gcd_tmp.count = gcd_tmp.data_array.size();
		gcd = getGreatestCommonDivisor(gcd_tmp);
		// 开始输出
		// 另：分母为零（异常处理）
		// 另：分子分母可整体约（eg.√2 + 5 / 2√2 + 10 = 1 /2）
		if (
		if (numerator_constant_array == denominator_constant_array && numerator_radical_array == denominator_radical_array)
		{
			// 上下完全一致
			cout << "1";
			return;
		}
		if (numerator_radical_array.empty() && n_constant_merged == 0)	// 检测分子
		{
			// 分子为零
			cout << "0";
			return;
		}
		if (d_constant_merged / gcd == 1 && denominator_radical_array.empty())
		{
			// 分母为1
			displayLine(n_constant_merged, numerator_radical_array, gcd);
			return;
		}
		displayLine(n_constant_merged, numerator_radical_array, gcd);
		cout << " / ";
		displayLine(d_constant_merged, denominator_radical_array, gcd);
	}
	//~display_mult();  // 析构函数
};


/*----------全局变量/结构体/对象声明区/杂项区2----------*/
long double pretime;
bool speedTestState = enabled;		// 避免多次测速
long long SwitchNum;
clock_t start, stop;			// 初始化计时函数

/*----------主函数----------*/
int main(void)
{
	action action;
	// 加载总控制台
	action.showMasterConsole();
Select_Num_Scan:
	cout << endl;
	cout << "[输入]";
	cin >> SwitchNum;
	cout << "====================" << endl << endl;
	switch (SwitchNum)
	{
	case 1:		// 解/分析二元一次方程
	{
		float* a = new float;		// 用于方程的输入
		float* b = new float;
		float* c = new float;
		float* Delta = new float;
		general_struct_1 factor_a, factor_c;

		// int m1, d1, m2, d2, m3, d3, mid4, mid5, mid6, d = 0; //
		// 分数运算需要用到的在这里定义，暂时还用不到
		// float mid7, mid8, mid9; //
		// 用于分数除法，暂时还用不到

		cout << "{!}程序启动，方程类型：ax^2+bx+c=0 \n" << endl;
	A_Scan:
		printf("{!}请输入a的值。 \n");
		printf("[a]");
		cin >> *a;
		if (*a == 0)
		{
			cout << "∵a=0，∴该方程不属于二元一次方程，请重新输入a的值." << endl;
			goto A_Scan;
		}
		else
			goto B_Scan;
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
		*Delta = pow(*b, 2) - 4 * *a * *c;
		if (*Delta >= 0)
		{
			cout << "由韦达定理，\nx(1)+x(2) = -b/a = " << -*b / *a << "." << endl
				 << "x(1)x(2) = c/a = " << *c / *a << "." << endl
				 << "|x(1)-x(2)| = " << getAbsoluteData(sqrt(*Delta)) / pow(*a, 2) << endl << endl;
		}
		cout << "[解法1：因式分解法(实验性，bug可能较多)]" << endl;
		// 开始a的因数计算，只需要正值即可
		factor_a = getFactor(*a, disabled);
		// 开始*c的因数计算，正负值都要计算，先讨论*c的正负性
		if (*c >= 0)
			factor_c = getFactor(*c, enabled);
		else	// 计算*c的负数因数
			factor_c = getFactor(-*c, enabled);	// 传入c的相反数，使c始终为正
		// 因数计算完成，开始for循环+if条件匹配
		for (int i = 0; i <= factor_c.count; i++)
		{
			for (int j = 0; j <= factor_a.count; j++)
			{
				if (factor_a.data_array[j] * (*c / factor_c.data_array[i]) + factor_c.data_array[i] * (*a / factor_a.data_array[j]) == *b)//触发输出的条件
				{
					// ！！！开始输出 Output
					if (factor_c.data_array[i] == *c / factor_c.data_array[i] and factor_a.data_array[j] == *a / factor_a.data_array[j]) //输出完全平方
					{
						cout << "( ";
						if (factor_a.data_array[j] != 1) /////1
							cout << factor_a.data_array[j];
						if (factor_c.data_array[i] < 0)
							cout << "x " << factor_c.data_array[i] << " ) ^ 2 = 0" << endl;
						else
							cout << "x + " << factor_c.data_array[i] << " ) ^ 2 = 0" << endl;
						goto EqualRoot_Output;
					}

					cout << "( ";
					if (factor_a.data_array[j] != 1) /////1
						cout << factor_a.data_array[j];
					if (factor_c.data_array[i] < 0)
						cout << "x " << factor_c.data_array[i] << " ) " << "( ";
					else
						cout << "x + " << factor_c.data_array[i] << " ) " << "( ";
					if (*a / factor_a.data_array[j] != 1) /////2
						cout << *a / factor_a.data_array[j];
					if (*c / factor_c.data_array[i] < 0)
						cout << "x " << *c / factor_c.data_array[i] << " ) = 0" << endl;
					else
						cout << "x + " << *c / factor_c.data_array[i] << " ) = 0" << endl;
					//line 2 output
					if (factor_a.data_array[j] != 1) /////1
						cout << factor_a.data_array[j];
					if (factor_c.data_array[i] < 0)
						cout << "x " << factor_c.data_array[i] << " = 0，或 ";
					else
						cout << "x + " << factor_c.data_array[i] << " = 0，或 ";
					if (*a / factor_a.data_array[j] != 1) /////2
						cout << *a / factor_a.data_array[j];
					if (*c / factor_c.data_array[i] < 0)
						cout << "x " << *c / factor_c.data_array[i] << " = 0" << endl;
					else
						cout << "x + " << *c / factor_c.data_array[i] << " = 0" << endl;
					// <---输出最终结果--->
					if ((float)-FZC[i] / FZA[j] == (float)(-*c / FZC[i]) / (*a / FZA[j]))	// 以等根形式输出结果
					{
					EqualRoot_Output:
						cout << "∴x(1)=x(2)=";
						displayFraction(getSimplifiedFraction(FZC[i], FZA[j]));
						cout << "." << endl << endl;
					}
					else	// 以不等根形式输出结果
					{
						cout << "∴x(1)=";
						displayFraction(getSimplifiedFraction(FZC[i], FZA[j]));
						cout << "，x(2)=";
						// 暂存，防止G++抽风
						long tmp1 = -*c / FZC[i];
						long tmp2 = *a / FZA[j];
						displayFraction(getSimplifiedFraction(tmp1, tmp2));
						cout << "." << endl << endl;
					}
					goto Method_2;	// 跳出两层for循环
				}		// if
			}			// for Aj
		}				// for Ci

		cout << "{!}该方程不可因式分解!" << endl << endl;
		
	Method_2:
		cout << "[解法2：公式法]" << endl;
		printf("Δ=%g^2-4×%g×%g=%g. \n", *b, *a, *c, *Delta);
		if (*Delta > 0)	// 如果判别式大于零
		{
			if (sqrt(*Delta) == (int)sqrt(*Delta))	// 是完全平方数
			{
				cout << "∵Δ>0，∴方程有两个不相等的实数根." << endl;
				cout << "∴x(1)=";
				// 中间量，避免安卓端Linux的G++出现蜜汁编译错误
				long temp1 = -1 * *b + sqrt(*Delta);
				long temp2 = -1 * *b - sqrt(*Delta);
				long temp3 = 2 * *a;
				displayFraction(getSimplifiedFraction(temp1, temp3));
				cout << ",∴x(2)=";
				displayFraction(getSimplifiedFraction(temp2, temp3));
				cout << "." << endl;
			}
			else	// 不是完全平方数
			{
				display_mult displayx1, displayx2;
				displayx1.setNumerator_constant(- *b);
				displayx1.setNumerator_radical(*Delta);
				displayx1.setDenominator_constant(2 * *a);
				displayx1.displayMult();
				/*simplify_quadratic_radical_struct delta_simped;
				general_struct_1 temp;
				delta_simped = simplifyQuadraticRadical(*Delta);
				temp.count = 3;
				for (int i = 0; i < 3; i++)	// 内存初始化
					temp.data_array.push_back(0);
				// 元素赋值
				temp.data_array[0] = - *b;
				temp.data_array[1] = 2 * *a;
				temp.data_array[2] = delta_simped.out_radical;
				long gcd = getGreatestCommonDivisor(temp);
				cout << "∵Δ>0，∴方程有两个不相等的实数根." << endl;
				for (int i = 0; i < 2; i++)	// 循环输出
				{
					printf("∴x(%d) = ", i + 1);
					if ((2 * *a / gcd) < 0)	// 判断式子前是否显示负号
						cout << "-";
					cout << "(" << -*b / gcd;		// 分子元素1
					if (i == 0)				// 分子元素1与分子元素2之间的加减号
						cout << "+";
					else
						cout << "-";
					if (delta_simped.out_radical / gcd != 1)
						cout << delta_simped.out_radical / gcd;	// 分子元素2（根号外）
					cout << "√";			// 根号
					cout << delta_simped.in_radical;
					cout << ")/";			// 分数线
					cout << getAbsoluteData(2 * *a / gcd) << endl;*/
	 	}
		}
		else	// 判别式不大于零
		{
			if (*Delta == 0)	// 如果判别式为零，则不需要判定Δ是否为完全平方
			{
				cout << "∵Δ=0，∴方程有两个相等的实数根." << endl;
				printf("∴x(1)=x(2)=%g. \n", (-1 * *b + sqrt(*Delta)) / (2 * *a));
			}
			else		// 判别式为负，无实数根
				cout << "∵Δ<0,∴方程没有实数根.\n{!}计算中止." << endl;
		}				// else
						// 分数模块（暂不准备开发）
						/* }//来自if mid1 = 0,1,2,3,4,5,6,7,8,9 为假的判断//
		   else { std::cout <<
		   "输入分数请用“/”作为分数线 " << std::endl;
		   std::cout << "请输入a的值 " << std::endl;
		   scanf("%d/%d", &m1, &d1); std::cout << "请输入*b的值 "
		   << std::endl; scanf("%d/%d", &m2, &d2); std::cout <<
		   "请输入c的值 " << std::endl; scanf("%d/%d", &m3, &d3);
		   }			*/
		   //释放内存
		delete a, b, c, Delta;
		goto Select_Num_Scan;
	}						// case1


	case 2:		// 因数分解
	{
		general_struct_1 factor;
		if (speedTestState == enabled) // 避免重复测速
		{
			cout << "{!}程序开始执行。\n[正在测速，请稍侯。调试信息请忽略。]" << endl;
			start = clock();	// 开始测速
			// 调用函数
			factor = getFactor(10000000, disabled);
			stop = clock();		// 停止测速
			pretime = (float)(stop - start) / CLOCKS_PER_SEC;
			cout << "Time=" << pretime << endl << "测速完成。" << endl << endl;
			speedTestState = disabled;
		}
		// 测速结束
		long double* predicttime = new long double;
		double* duration = new double;
		long* numscan = new long;
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
		*predicttime = (pretime / 10000000) * *numscan;
		cout << "[预计耗时]" << *predicttime << " sec." << endl << endl;
		cout << fixed << setprecision(0);	// 锁定浮点数显示，不使用科学计数法，小数不显示
		if (*predicttime >= 60)
		{
Select_BigTask_Scan_Default:
			cout << "你输入的数预计运算时间大于一分钟，检测到大型任务，是否继续？" << endl;
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
			goto PrimeNum_Output;
		else
			goto Default_Output;
Default_Output:
		// 调用函数(不启用负数输出)
		factor = getFactor(*numscan, disabled);
		// 开始输出
		for (long i = 0; i <= factor.count; i++)
			printf("[整因数 %ld ] = %ld\n", i + 1, factor.data_array[i]);
PrimeNum_Output:
		if (factor.count <= 2)
			cout << "{!}该数是质数。" << endl;
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
		delete numscan, predicttime;
		goto Select_Num_Scan;
	}						// case 2


	case 3:		// 找最小公倍数、最大公因数
	{
		general_struct_1 temp;
	Case3_Scan:
		cout << "[数据的数量] = " << endl;
		cin >> temp.count;
		for (long i = 0; i < temp.count; i++)
		{
		printf("[输入数据%ld] = ", i + 1);
		temp.data_array.push_back(0);
		cin >> temp.data_array[i];
		}
		// 调用函数，输出
//		cout << "最小公倍数为：" << getLowestCommonMultiple(temp) << endl;
		cout << "最大公约数为：" << getGreatestCommonDivisor(temp) << endl;
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
			cout << "该数是完全平方数。开方值为：" << sqrt(*numscan) << "." << endl;
		else
			cout << "该数不是完全平方数。" << endl;
		delete numscan;
		goto Select_Num_Scan;
	}						// case 4


	case 5:		// 数据排序
	{
		general_struct_1 input;
		long* numamount = new long;
	Case5_Scan:
		cout << "请输入数据的数量" << endl << "[数量]";
		cin >> *numamount;
		cout << "请依次输入各个数据" << endl;
		for (int i = 0; i < *numamount; i++)	// 输入数据
		{
			printf("[输入数%ld] = ", i + 1);
			input.data_array.push_back(0);		// 容器内存初始化
			cin >> input.data_array[i];
		}
		input = getSortedData(input, *numamount);
		cout << endl << "从小到大排序结果为：" << endl;		// 计算完毕，输出结果
		for (int m = 0; m < *numamount; m++)
		{
			printf("[输出数%ld] = %ld\n", m + 1, input.data_array[m]);
		}
		printf("共进行了%ld次交换。\n", input.count);
		delete numamount;
		goto Select_Num_Scan;
	}


	case 6:		// 分数约分
	{
		long* numscan1 = new long;
		long* numscan2 = new long;
		simplify_fraction_struct simplified;
		cout << "请输入两个正整数，分别作为分子和分母。" << endl
			<< "[分子]";
		cin >> *numscan1;
		cout << "[分母]";
		cin >> *numscan2;
		cout << endl;
		simplified = getSimplifiedFraction(*numscan1, *numscan2);
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
		simplify_quadratic_radical_struct returnNums;
		returnNums = simplifyQuadraticRadical(*numscan);
		cout << "[因数分解] " << *numscan << " = " << pow(returnNums.out_radical, 2) << " * "
			<< *numscan / pow(returnNums.out_radical, 2) << endl;
		cout << "[化简结果]" << "√" << *numscan << " = ";
		if (returnNums.out_radical != 1)
			cout << returnNums.out_radical;
		if (returnNums.in_radical != 1)
			cout << "√" << returnNums.in_radical;
		cout << endl;	//空一行
		delete numscan;
		goto Select_Num_Scan;
	}


	case 8:		// 直线到直线距离计算
	{
		long k, b1, b2;
		cout << "已知两条平行直线y=kx+b，请依次输入k、b1、b2的值." << endl;
		cin >> k >> b1 >> b2;
		cout << "两直线距离为：";
		display_mult display;
		display.setNumerator_constant(k);
		display.setNumerator_radical(b1);
		display.setDenominator_constant(b2);
		display.displayMult();
		/*simplify_quadratic_radical_struct returnNums = simplifyQuadraticRadical(pow(k, 2) + 1);
		displayFraction(getSimplifiedFraction(getAbsoluteData(b1 - b2) / sqrt(pow(k, 2) + 1)));*/
		cout << endl;	// 空一行
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
				(*max)++;
		}
			(*min)++;
			for (int i = 0;i < 3;i++)
				(*max)++;
		// 开始调用，生成随机数
		for (long i = 0;i < *randnumamount;i++)
		{
			*randnum = getRandData(*min, *max);
			printf("[输出数%ld] = ", i + 1);
			cout << *randnum << endl;
		}


		delete max, min, randnum, randnumamount;
		goto Select_Num_Scan;
	}


	case 14:	// 二次函数解析式计算
	{
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
		long x_numerator, x_denominator, y_numerator, y_denominator;				// 声明x轴、y轴坐标
		// 开始运算，赋值
		x_numerator = -b;
		x_denominator = 2 * a;
		y_numerator = 4 * a * c - b * b;
		y_denominator = 4 * a;
		// 调用函数
		cout << "对称轴(顶点坐标) : ( ";
		displayFraction(getSimplifiedFraction(x_numerator, x_denominator));
		cout << " , ";
		displayFraction(getSimplifiedFraction(y_numerator, y_denominator));
		cout << " )" << endl;
		goto Select_Num_Scan;
	}


	case 15:		// 分解质因数（by 倚剑笑紅尘）
	{
		long long tar;
		cout << "输入一个正整数（值域：long long）" << endl;
		cin >> tar;
		number = 0;
		m.clear();
		find(tar, 2137342);
		printf("%lld = ", tar);
		if (m.empty())
			printf("%lld\n", tar);
		for (map<long long, int>::iterator iter = m.begin(); iter != m.end();)
		{
			printf("%lld^%d", iter->first, iter->second);
			if ((++iter) != m.end())
				printf(" * ");
		}
		printf("\n");
		goto Select_Num_Scan;
	}


	case 16:	// 身份证验证码计算（by boshuzhang）
	{
		char ID[19];
		int IDNumber[19];
		cout << "[输入身份证号码]";
		cin >> ID;    
		while(!_checkIDinput(ID))  // 防止输入过程中位数输入错误   
		{
			cout << "错误ID，请重新输入" << endl; 
			cout << "[输入身份证号码]";
			cin >> ID;   
		} 
		for (int i = 0; i < 18; i++)// 相当于类型转换
			IDNumber[i] = ID[i] - 48; 
		_checkID(IDNumber, ID);
		goto Select_Num_Scan;
	}


	case 1024:	// 开发者测试
	{
		cout << "[开发者测试]" << endl;
		cout << "1.根式化简\n0.退出\n";
		long tmp;
		cin >> tmp;
		for (; ; )
		{
			switch (tmp)
			{
			case 1:
			{
				display_mult display;
				long nca, nra, dca, dra, nc, nr, dc, dr;
				cout << "分子->常数\n"
					<< "分子->根号\n"
					<< "分母->常数\n"
					<< "分母->根号\n";
				cin >> nca >> nra >> dca >> dra;
				cout << "分子->常数 --- begin" << endl;
				for (var i = 0; i < nca; i++)
				{
					cin >> nc;
					display.setNumerator_constant(nc);
				}
				cout << "=== end" << endl;
				cout << "分子->根号 --- begin" << endl;
				for (var i = 0; i < nra; i++)
				{
					cin >> nr;
					display.setNumerator_radical(nr);
				}
				cout << "=== end" << endl;
				// ----------
				cout << "分母->常数 --- begin" << endl;
				for (var i = 0; i < dca; i++)
				{
					cin >> dc;
					display.setDenominator_constant(dc);
				}
				cout << "=== end" << endl;
				cout << "分母->根号 --- begin" << endl;
				for (var i = 0; i < dra; i++)
				{
					cin >> dr;
					display.setDenominator_radical(dr);
				}
				cout << "=== end" << endl;
				display.displayMult();
				cout << endl;
			}

			case 0:
			{
				goto Select_Num_Scan;
			}
			
			default:
			{
			action.showInputErrorMsg();
			goto Select_Num_Scan;
			}
			}
		}
	}


	case 0:		// 显示控制台
	{
		action.showMasterConsole();
		goto Select_Num_Scan;
	}						// case 0


	default:	// 输入错误
	{
		action.showInputErrorMsg();
		goto Select_Num_Scan;
	}						// default
	}						// switch
	return 0;
}							// main

/*C语言printf格式化字符串类型（by 低调额低调额）：
1、%d 十进制有符号整数。
2、%u 十进制无符号整数。
3、%ld 输出long整数 。
4、%s 字符串。
5、%c 单个字符。
6、%p 指针的值。
7、%e 指数形式的浮点数。
8、%x, %X 无符号以十六进制表示的整数。
9、%0 无符号以八进制表示的整数。
10、%g 自动选择合适的表示法。
*/

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
