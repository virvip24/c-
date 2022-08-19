// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
/*内联函数*/
//编译阶段C++编译器会在调用内联函数的地方直接展开，没有函数压栈的开销。“空间换时间”
//内联函数实在执行函数过程中遇到函数名时不返回调用函数，而是在函数名所在地写上函数的代码
//将函数规模很小且使用频繁的函数声明为内联函数
//优化速度
inline int add(int a, int b)
{
    return a + b;
}
/*类*/
//https://blog.csdn.net/qq_40395874/article/details/123359358?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165914616616782388031185%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165914616616782388031185&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-2-123359358-null-null.142^v35^new_blog_fixed_pos&utm_term=C%2B%2B%20%E7%B1%BB%E7%9A%84%E4%BD%BF%E7%94%A8&spm=1018.2226.3001.4187
class Stock {
private:
    double share_value; // 实时单价
    double total_value; // 总价
    void set_tot();
public:
    long shares; // 持有的数
    void update(double price);
    void show();
}; // 注意类声明以分号结尾

void Stock::update(double price) {
    share_value = price;
    set_tot();
}
inline void Stock::set_tot() {
    total_value = shares * share_value;
}
void Stock::show() {
    std::cout 
        << "Shares: " << shares << std::endl
        << "Share Price: $" << share_value << std::endl
        << "Total Worth: $" << total_value << std::endl;
}
/*继承*/
//https://blog.csdn.net/strongman028/article/details/107330346?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165925832316782390549573%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165925832316782390549573&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-107330346-null-null.142^v35^new_blog_fixed_pos&utm_term=C%2B%2B%E7%BB%A7%E6%89%BF%E7%9A%84%E5%AE%9E%E9%99%85%E5%BA%94%E7%94%A8&spm=1018.2226.3001.4187
//提高代码的复用率，继承将会是一个非常有效的解决办法，我们可以将show和hide封装成一个一级基础类BaseDailog，然后将size封装成三个二级基础类SmallDailog、MediumDailog和LargeDailog，它们都继承于BaseDailog类。
class BaseDailog {
public:
    void show();							// 展示弹窗
    void hide();							// 隐藏弹窗
};
void BaseDailog::show() {
    std::cout
        << "User Dailog: " << "show " << std::endl;
}
void BaseDailog::hide() {
}
class SmallDailog : public BaseDailog{
public:
    int size = 0;
};
class LargeDailog : public BaseDailog {
public:
    int size = 1;
};
//功能弹窗类的代码实现
class UserDailog : public LargeDailog {
public:
    void setUserInfo();
};
void UserDailog::setUserInfo() {
    std::cout
        << "User Dailog: " <<"Size: " << size << std::endl;
}
/*多态*/
//https://blog.csdn.net/weixin_54509036/article/details/120633485?ops_request_misc=&request_id=&biz_id=102&utm_term=C++%E5%A4%9A%E6%80%81%E7%9A%84%E5%AE%9E%E9%99%85%E5%BA%94%E7%94%A8&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-7-120633485.142^v39^pc_rank_34_ecpm0&spm=1018.2226.3001.4187
//使用多态实现计算器
//实现计算机抽象类 任何功能都不写，只写两个操作数
class AbstractCalculator
{
public:
    virtual int Getresult()
    {
        return 0;
    }
    int m_Num1;
    int m_Num2;
};
class AddCalculator :public AbstractCalculator
{
public:
    int Getresult()
    {
        return m_Num1 + m_Num2;
    }
};
class SubCalculator :public AbstractCalculator

{
public:
    int Getresult()
    {
        return m_Num1 - m_Num2;
    }
};
class MulCalculator :public AbstractCalculator
{
public:
    int Getresult()
    {
        return m_Num1 * m_Num2;
    }
};
void test02()
{
    AddCalculator b;
    b.m_Num1 = 10;
    b.m_Num2 = 20;
    std::cout << b.Getresult() << std::endl;

    AbstractCalculator* pA = &b;
    std::cout << pA->Getresult() << std::endl;//如果没用virtual声明为虚函数，这里会输出0

    //用new方式
    AbstractCalculator* abc = new AddCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 20;
    std::cout << abc->Getresult() << std::endl;
    delete abc;//不会删除指针本身，即仍然可以使用该指针去指向其他int 类型的变量。new 和 delete 一定需要成对的使用否则极易发生内存泄漏。
  
    abc = new SubCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 20;
    std::cout << abc->Getresult() << std::endl;
    delete abc;
   
    abc = new MulCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 20;
    std::cout << abc->Getresult() << std::endl;
    delete abc;
}
/*模板*/

//函数模板//https://blog.csdn.net/m0_61886762/article/details/123844022
template<class type>
type Sum(type x, type y)
{
    return x + y;     //此代码可以用于任何相同数据的求和
}
//类模板//https://blog.csdn.net/weixin_54907221/article/details/118609012?ops_request_misc=&request_id=&biz_id=102&utm_term=C++%E7%B1%BB%E6%A8%A1%E6%9D%BF%E5%AE%9E%E9%99%85%E5%BA%94%E7%94%A8&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-118609012.142^v40^pc_rank_34_ecpm0,185^v2^control&spm=1018.2226.3001.4187
//采用class来定义模板参数类型，后来为了避免 class 在声明类和模板的使用可能给人带来混淆，所以引入了 typename 这个关键字。
//模板定义语法中关键字 class 与 typename 的作用完全一样。
//不同的是typename 还有另外一个作用为：使用嵌套依赖类型(nested depended name)
using namespace std;
template<typename agetype, typename nametype>
//在申明模板之后紧跟着一个类，就是类模板了
class person
{
public:
    person(agetype age, nametype name)
    {
        this->m_age = age;
        this->m_name = name;
    }
    void showperson()
    {
        cout << "年龄为" << this->m_age << "\t" 
             << "姓名为" << this->m_name << endl;
    }
    agetype m_age;
    nametype m_name;

};
void test01()
{//<>为模板的参数列表，和类中的构造函数中的参数一一对应
    person<int, string> p1(18, "李华");
    p1.showperson();
}

/*STL*/
#include <vector>
#include <deque>
#include <algorithm> 
//容器vector deque//https://blog.csdn.net/m0_51487301/article/details/118727781?spm=1001.2101.3001.6650.7&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7ERate-7-118727781-blog-83725343.pc_relevant_multi_platform_featuressortv2removedup&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7ERate-7-118727781-blog-83725343.pc_relevant_multi_platform_featuressortv2removedup&utm_relevant_index=14
//有5名选手：选手12345，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
using namespace std;
//创建选手类
class Person {
public:
    string m_name;	//定义类变量 
    int m_score;

    Person(string name, int score) {	//构造函数调用表达式 
        this->m_name = name;		//this是个指针，所以引用要用-> 
        this->m_score = score;
    }
};

//创建存放选手名单和分数信息的vector容器
void creatPerson(vector<Person>& v) {
    string nameList = "ABCDE";		//选手名单 
    for (int i = 0; i < 5; i++) {
        string name = "选手";
        name += nameList[i];
        int score = 0;
        Person p(name, score);	//选手实例化
        v.push_back(p);
    }
}

//打分并求平均分
void setScore(vector<Person>& v) {
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {	//对每名选手 打分
        deque<int> d;	//创建一个deque容器存放分数
        for (int i = 0; i < 10; i++) {
            int score = i;		
            d.push_back(score);
        }
        sort(d.begin(), d.end());		//对十名评委的打分进行排序
        d.pop_front();			//去掉一个最低分 
        d.pop_back(); 			//去掉一个最高分
        int sum = 0;
        for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++) {
            sum += *dit;	//遍历deque容器中的每个元素并相加 
        }
        int avg = sum / d.size();	//得出平均数
        it->m_score = avg;		//将平均数存入vector容器中 

    }
}
//显示选手得分
void showScore(vector<Person>& v) {
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
        cout << it->m_name << "的得分为" << it->m_score << endl;	//输出每位选手的得分 
    }
}

//当数据以键值对形式存在，可以考虑用 容器map 或 multimap
//公司今天招聘了5个员工（ABCDEFGHIJ），指派员工在那个部门工作
//员工信息有 : 姓名 工资组成；部门分为：策划、研发
//通过multimap进行信息的插入 key(部门编号) value(员工)
//分部门显示员工信息

#include <map>

#define CEHUA  0
#define YANFA  1

class Worker
{
public:
    string m_Name;
    int m_Salary;
};

void createWorker(vector<Worker>& v)
{
    string nameSeed = "ABCDE";
    for (int i = 0; i < 5; i++)
    {
        Worker worker;
        worker.m_Name = "员工";
        worker.m_Name += nameSeed[i];

        worker.m_Salary = rand() % 10000 + 10000; // 10000 ~ 19999
        //将员工放入到容器中
        v.push_back(worker);
    }
}

//员工分组
void setGroup(vector<Worker>& v, multimap<int, Worker>& m)
{
    for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
    {
        //产生随机部门编号
        int deptId = rand() % 2; // CEHUA  0 YANFA  1

        //将员工插入到分组中，//用匿名对组插入
        m.insert(make_pair(deptId, *it)); //pair创建对组：key部门编号，value具体员工
    }
}

void showWorkerByGourp(multimap<int, Worker>& m)
{
    // 0  A  B  C   1  D  E   2  F G ...
    cout << "策划部门：" << endl;

    multimap<int, Worker>::iterator pos = m.find(CEHUA);
    int count = m.count(CEHUA); // 统计具体人数
    int index = 0;
    for (; pos != m.end() && index < count; pos++, index++)
    {
        cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Salary << endl;
    }

    cout << "----------------------" << endl;
    cout << "研发部门： " << endl;
    pos = m.find(YANFA);
    count = m.count(YANFA); // 统计具体人数
    index = 0;
    for (; pos != m.end() && index < count; pos++, index++)
    {
        cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Salary << endl;
    }

}

int main()
{
    /*关键字new s一维数组*/
    std::cout << "new\n";
    int* arr2 = new int[3]{ 1,2 };//delete []arr2
    printf("%d %d %d\r\n", arr2[0], arr2[1], arr2[2]);

    std::cout << "获取数组大小\n";//动态创建(new)的基本数据类型数组无法取得数组大小
    int arr1[3]={ 1,2 };//delete []arr2
    std::cout << sizeof(arr1) / sizeof(arr1[0]) << std::endl;

    /*函数重载*/
    //同一个函数名对应不同的函数实现，每一类实现对应着一个函数体，名字相同，功能相同，只是<参数的类型>或<参数的个数>不同。多个同名函数只是函数类型（函数返回值类型）不同时，它们不是重载函数  
    
    std::cout << "数组指针\n";
    int arr3[6] = { 1,2,3,4,5,6 };;
    int* p1;
    p1 = arr3;// *p1 = &arr[0];
    printf("%d %d %d\r\n", *(p1), *(p1 + 4), *(p1 + 5));

    std::cout << "指针访问二维数组：指向二维数组元素，指向一维数组\n";   
    int arr4[2][3] = {1,2,3,4,5,6};
    int(*p2)[3];
    p2= arr4;
    printf("%d %d %d\r\n", (*p2)[0], *(p2[1] + 1), *(p2[1] + 2));

    /*引用*/
    //引用可以看做是数据的一个别名，通过这个别名和原来的名字都能够找到这份数据，类似于window中的快捷方式。
    //int a;
    //int& b = a;//a和b表示相同的变量，具有相同的地址。

    /*面向对象*/
    //类也是一种数据类型。
    //声明类同时定义对象
    //类是C++中对于C语言中的结构体的延伸
    
    /*类*/
    // 声明 Stock 变量
    Stock sally;
    sally.shares = 100;
    sally.update(5);//单价2*数量100
    sally.show();

    /*继承*/
    //实现代码和数据的复用，复用的实现在已有的代码和数据的基础上扩展。
    //多重继承在中小型项目中较少使用，在Java、C#等语言中直接取消多继承, 以避免复杂性.
    UserDailog user;  
    user.setUserInfo();
    user.size = 2;
    user.setUserInfo();
    user.show();
    /*多态*/
    //在 C++中，用父类型别的指针指向其子类的实例，然后通过父类的指针调用实际子类的成员函数，大大提高编程的效率和灵活性，即C++多态性
    test02();

    /*运算符重载*/

    /*IO流*/
    std::cout << "请输入数字" << std::endl;
    char c;
    while ((c = std::cin.get()) != EOF)//循环读取，直到换行
    {
        std::cout << c;
        break;
    }

    /*文件操作*/
    //eg：编写一个程序，将文件 i.txt 中的整数倒序输出到 o.txt。（12 34 56 78 90 -> 90 78 56 34 12）

    /*模板*/
    //泛型程序设计在实现时不指定具体要操作的数据的类型的程序设计方法的一种算法，指的是算法只要实现一遍，就能适用于多种数据类型，优势在于代码复用，减少重复代码的编写
    //模板是泛型的基础，是创建泛型类或函数的蓝图或公式。
    //函数模板
    int r1 = Sum(15, 10);    //两个为int类型的数据之和
    std::cout << "数字之和r1为" << r1 << std::endl;
    float r2 = Sum(15.1, 10.2);
    std::cout << "数字之和r2为" << r2 << std::endl;
    //类模板
    test01();

    /*STL*/
    //容器vector deque
    vector<Person> v;	//声明一个vector容器
    creatPerson(v);
    setScore(v);
    showScore(v);

    srand((unsigned int)time(NULL));

    //容器multimap
    //1、创建员工
    vector<Worker>vWorker;
    createWorker(vWorker);

    //2、员工分组
    multimap<int, Worker>mWorker;
    setGroup(vWorker, mWorker);


    //3、分组显示员工
    showWorkerByGourp(mWorker);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
