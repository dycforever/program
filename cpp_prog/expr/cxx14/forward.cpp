#include <iostream>
#include <memory>
#include <utility>
#include <array>

struct SingleArgClass {
    SingleArgClass(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
    SingleArgClass(int& n) { std::cout << "lvalue overload, n=" << n << "\n"; }
    SingleArgClass(const int& n)  { std::cout << "const lvalue overload, n=" << n << "\n"; }
};

class MultiArgClass {
public:
    template<class T1, class T2, class T3>
        MultiArgClass(T1&& t1, T2&& t2, T3&& t3) :
            a1_{std::forward<T1>(t1)},
            a2_{std::forward<T2>(t2)},
            a3_{std::forward<T3>(t3)}
    {
    }

private:
    SingleArgClass a1_, a2_, a3_;
};

template<class T, class U>
std::unique_ptr<T> make_unique_1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}
/* *******************
 * 说明：
 * 1. forward 不能改变值的 const 属性，所以 const int 无论如何不能匹配到 int& 或 int&&
 * 2. forward 能做的是把 非const 转发到 非const，const 转发到 const，减少 MultiArgClass 的工作量
 *
 * 所以，c++11之前，[non-const 左值] 匹配到 [非 const 引用]，[右值] 和 [const 左值] 匹配到 [const 引用]
 * 而现在，[non-const 左值] 匹配到 [非 const 引用]，[右值] 匹配到 [右值引用 &&], [const 左值] 匹配到 [const 引用]
 * std::move() 能把非 const 左值变成右值，但是不能把 const 左值变成右值
 *
 * 程序输出:
 *
 * rvalue overload, n=2
 * lvalue overload, n=1
 *
 * === multi-argument ===
 *
 * rvalue overload, n=2
 * lvalue overload, n=1
 * rvalue overload, n=3
 *
 * *********************/

int main() {
    auto p1 = make_unique_1<SingleArgClass>(2); // rvalue
    const int c = 3;
//    auto p2 = make_unique_1<SingleArgClass>(c); // 编译报错
//    auto p2 = make_unique_1<SingleArgClass>(std::forward<int>(c)); // 编译报错
    int i = 1;
    auto p3 = make_unique_1<SingleArgClass>(i); // lvalue

    std::cout << "\n=== multi-argument ===\n\n";
    auto t = make_unique<MultiArgClass>(2, i, c);
}
