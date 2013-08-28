#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>


class Person {
private:
    std::string name;
public:
    Person():name("dyc"){}
    void print () const {
        std::cout << "no prefix print:" << name << std::endl;
    }
    void printWithPrefix (std::string prefix) const {
        std::cout << "with prefix print: " << prefix << name << std::endl;
    }
};

void foo (const std::vector<Person>& coll)
{
    using std::for_each;
    using std::bind2nd;
    using std::mem_fun_ref;

    // call member function print() for each element
    for_each (coll.begin(), coll.end(),
            mem_fun_ref(&Person::print));

    // call member function printWithPrefix() for each element
    // - "person: " is passed as an argument to the member function
    for_each (coll.begin(), coll.end(),
            bind2nd(mem_fun_ref(&Person::printWithPrefix),
                "  Person "));
}

void ptrfoo (const std::vector<Person*>& coll)
    // ^^^ pointer !
{
    using std::for_each;
    using std::bind2nd;
    using std::mem_fun;

    // call member function print() for each referred object
    for_each (coll.begin(), coll.end(),
            mem_fun(&Person::print));

    // call member function printWithPrefix() for each referred object
    // - "person: " is passed as an argument to the member function
    for_each (coll.begin(), coll.end(),
            bind2nd(mem_fun(&Person::printWithPrefix),
                "person: "));
}
// NOTICE:
//      use ptr_fun() for normal function with adapter

int main()
{
    std::vector<Person> coll(5);
    foo(coll);

    std::vector<Person*> coll2;
    coll2.push_back(new Person);
    ptrfoo(coll2);
}
