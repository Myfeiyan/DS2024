#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <iomanip> 
#include <random> 
#include <cmath>
#include "vector.cpp"
#include <chrono>

using namespace std;
// 定义复数类
class Complex
{
public:
    double real;
    double imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

 double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }
      bool operator<(const Complex& other) const {
        if (std::abs(module - other.module) < 1e-9) {
            return real < other.real || (std::abs(real - other.real) < 1e-9 && imag < other.imag);
        }
        return module < other.module;
    }
    bool operator>(const Complex& other) const {
        if (this->module == other.module) {
            return this->real > other.real;
        }
        return this->module > other.module;
    }

    bool operator!=(const Complex& other) const {
        return this->real != other.real || this->imag != other.imag;
    }

    bool operator==(const Complex& other) const {
        return this->real == other.real && this->imag == other.imag;
    }
};

// 区间查找算法
Vector<Complex> findM(const Vector<Complex> &arr, double m1, double m2)
{
    Vector<Complex> result;
    for (int i = 0; i < arr.size(); ++i)
    {
        double modulus = arr[i].modulus();
        if (modulus >= m1 && modulus < m2)
        {result.insert(arr[i]);}
    }
    return result;
}

void print(Complex &c)   //输出函数
{
    cout<<c.real<<"+" << c.imag << "i   ";
}

// 随机生成乱序复数向量
Vector<Complex> generateRandomVector(int n)
{
    Vector<Complex> A;
    srand(time(0));
    int uniqueSize = n - 2;
    Vector<Complex> A1;
    for (int i = 0; i < uniqueSize; ++i)
    {
         double real = (rand() % 200 - 100) / 10.0; // 实部在 -10 到 10 之间
         double imag = (rand() % 200 - 100) / 10.0; // 虚部在 -10 到 10 之间
        A1.insert(Complex(real, imag));
        A.insert(Complex(real, imag)); // 插入到最终的向量中
    }
    for (int i = uniqueSize; i < n; ++i)
    {
        int randomIndex = rand() % uniqueSize; // 从唯一元素中随机选择
        A.insert(A1[randomIndex]);
    }
    return A;
}
// 记录排序时间并输出结果
void measureSortingTime(const string &sortType, Vector<Complex> A)
{
    auto start = chrono::high_resolution_clock::now();
    if (sortType == "起泡排序")
    { A.bubbleSort(0, A.size()-1);}
    else if (sortType == "归并排序")
    {A.mergeSort(0, A.size()-1);}
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration_us = end - start;
    cout << sortType<<" time: " << duration_us.count() << " us" << endl;
}

int main()
{
    // 1. 生成一个无序的复数向量
    int n = 1000;
    Vector<Complex> A= generateRandomVector(n);
    Vector<Complex> A1 = A;//乱序数组A1
    Vector<Complex> A2 = A;
    Vector<Complex> A3 = A; // 逆序数组A3
    A2.sort();//顺序数组A2
    
   std::vector<Complex> generateRandomComplexVector(int n) {
    std::vector<Complex> vec;
    srand((unsigned)time(0));  // 设置随机数种子
    for (int i = 0; i < n; ++i) {
        double real = (rand() % 200 - 100) / 10.0;  // 随机生成 -10 到 10 的实数
        double imag = (rand() % 200 - 100) / 10.0;  // 随机生成 -10 到 10 的虚数
        vec.emplace_back(real, imag);
    }
    return vec;
}
    
    // 测试置乱
    A.unsort(0, A.size()-1);
    cout << "置乱后的复数向量:\n";
    A.traverse(print);cout << endl;
    // // 测试查找
    Complex search(1, 2); // 用以查找的复数
    Rank foundI = A.find(search);
    if (foundI != -1)
    { cout << "找到元素 " << search << " 在索引 " << foundI << endl;}
    else
    {cout << "未找到元素 " << search << endl;}
    // 测试插入
    A.insert(0, Complex(1, 2));
    cout << "插入元素 (1, 2) 后的复数向量:\n";
    A.traverse(print);cout << endl;
    // 测试删除
    A.remove(0); // 删除插入的元素
    cout << "删除元素后复数向量:\n";
    A.traverse(print);cout << endl;
    // 唯一化复数向量
    A.deduplicate();
    cout << "唯一化后的复数向量:\n";
    A.traverse(print);cout << endl;
    // 排序
    A.sort();
    cout << "排序后的复数向量:\n";
    A.traverse(print);cout << endl;
    // 测试区间查找
    double m1 = 3.0;  // 设置模的下界
    double m2 = 8.0; // 设置模的上界
    Vector<Complex> foundN = findM(A2, m1, m2);
    cout << "在区间 [" << m1 << ", " << m2 << "):的元素\n";
    foundN.traverse(print);cout<<endl;
    // 测试乱序向量
    cout << "乱序排序时间:" << endl;
    Vector<Complex> A12 = A1;
    measureSortingTime("起泡排序",A1);
    measureSortingTime("归并排序", A12);
    // 测试顺序
    cout << "顺序排序时间:" << endl;
    Vector<Complex> A22 = A2;
    measureSortingTime("起泡排序", A2);
    measureSortingTime("归并排序", A22);
    // 测试逆序向量
    cout << "逆序排序时间" << endl;
    Vector<Complex> A32 = A3;
    measureSortingTime("起泡排序", A3);
    measureSortingTime("归并排序", A32);
    
    return 0;
 }
