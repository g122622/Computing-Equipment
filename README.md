## **工程名称：计算工具**

**日期：20200121**

**版本：v1.4.4（目前作者学业繁忙，更新较为缓慢）**

**开发平台：Windows：Microsoft Visual Studio；Android：c4droid**

**同步平台：Github**

**开放源代码状态：闭源**

1.temp.count可以不传入，由函数用sizeof自行判断数量

2.增加点到直线距离计算、点到点、直线到直线

3.增加三角形面积计算(多种方法)

4.增加各种其他几何运算(包括立体图形如圆锥，知二推其他)

5.用字符串数据类型实现分数的输入、格式化赋给结构体，分数输入函数化

6.韦达定理增加x1-x2的计算（代码输出示例如下）
```c++
    请输入其中两个已知量（输入格式：[字母标识类型，不区分大小写]+[值]+[回车Enter]+[字母标识类型，不区分大小写]+[值]+[回车Enter]（L：母线长；H：圆锥的高；D：底面周长；S：侧面展开面积；A：侧面展开扇形圆心角度数；R：底面半径）
```

这个程序为解决初中阶段各种繁琐的数学运算而设计。

这是我在学习之余写的程序，下面是所有源代码。

未经允许严禁私自转载！严禁私改版权！

使用本程序内的算法需征得我的授权。

除非这个算法是你自己独立写出来的qwq

之所以我不加密就是为了方便他人借鉴学习。

但这不意味着您可以“借鉴”走全部源代码作为自己的作品！

我很反感那种拿别人劳动成果盈利的人。

这里的盈利指利用别人的作品得到的各种好处。

如果你不这么觉得，→_→我只能鄙视你。

### **更新日志ChangeLog：**
v1.1.0 改变因数计算先后顺序，让等待时间更符合认知习惯。

v1.1.1 修改无限循环的阈值到20000，避免特殊情况。

v1.2.0 找因数修复复位bug;增加计算位数。

v1.2.1 文案优化。

v1.2.2 增加完成颜色。

v1.3.0 增加了找因数的预估测速功能。

v1.4.0 优化找因数的运算速度，提高约50%;对显示进行优化，不会显示1和数字本身。

v1.4.1 找因数的测速优化，格式优化;二元一次方程增加a=0时的判别功能;程序开头输入数错误时会出现提示了。

v1.4.2 修复了找因数中输入2时显示有因数的bug。

v1.4.3 缩减方程部分代码体积;找因数中增加了质数显示;修复找因数中输入0时显示有因数的bug。

v1.4.4 因数分解增加大型任务判断模块。

v2.0.0 1.代码优化，终于没有warning了;2.优化找因数大型任务判断部分的交互;3.优化方程输入a=0时的交互;4.优化方程步骤的显示;5.找因数增加输入为负数时的提示;6.switch分支结构的判断数据类型改为long long，输入更耐艹;

加入代码历史版本


bug反馈1:无法消除小数显示限制

bug反馈2:a为小于等于-2的数时，无法分解。解决:当检测到a为负数时，触发if，调转abc的符号。

bug反馈3:二元一次方程依次输入1,2,0时无法分解

bug反馈4:二元一次方程依次输入-1,12,0时无法分解

bug反馈5:二元一次方程依次输入3,8,0时闪退

bug反馈6:二元一次方程依次输入-3,8,0时闪退

！！！可能触发重大隐蔽bug:因式分解在使用整数变量(int,long)等时，若无强制类型转换小数，则会导致输出异常
