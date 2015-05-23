#include <string>
#include <queue>
#include <vector>
#include <iostream>

struct Node
{
    Node(int value, const std::string& name)
        : _value(value),
          _name(name)
    {}

    friend bool operator < (const Node& n1, const Node& n2)
    {
        return n1._value > n2._value;
    }

    int _value;
    std::string _name;
};

/*
bool operator < (const Node& n1, const Node& n2)
{
    return n1._value > n2._value;
}
*/

struct Compare
{
    bool operator() (const Node& node1, const Node& node2)
    {
        return node1._value > node2._value;
    }
};

template <class N>
bool compare (const N& node1, const N& node2)
{
    return node1._value > node2._value;
}

int func1()
{
    std::priority_queue<Node, std::vector<Node>, compare<Node> > queue;
    queue.push(Node(3, "abc"));
    queue.push(Node(4, "bcd"));
    queue.push(Node(5, "cde"));
    
    while (!queue.empty())
    {
        std::cout << queue.top()._name << " ";
        queue.pop();
    }
    std::cout << std::endl;
}

int func2()
{
    std::priority_queue<Node> queue;
    queue.push(Node(3, "abc"));
    queue.push(Node(4, "bcd"));
    queue.push(Node(5, "cde"));
    
    while (!queue.empty())
    {
        std::cout << queue.top()._name << " ";
        queue.pop();
    }
    std::cout << std::endl;
}

int main()
{
    func1();

    func2();
}
