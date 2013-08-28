#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>

using namespace std;
using namespace boost;

struct Foo
{ 
    Foo( int _x ) : x(_x) {}
    ~Foo() { std::cout << "Destructing a Foo with x=" << x << "\n"; }
    int x;
};

typedef boost::shared_ptr<Foo> FooPtr;

weak_ptr<Foo> returnExpire() {
    boost::shared_ptr<Foo> ptrFoo(new Foo(0));
    return weak_ptr<Foo>(ptrFoo);
}

struct FooPtrOps
{
    bool operator()( const FooPtr & a, const FooPtr & b )
    { return a->x > b->x; }
    void operator()( const FooPtr & a )
    { std::cout << a->x << "\n"; }
};

int main()
{
    std::vector<FooPtr>         foo_vector;
    std::set<FooPtr,FooPtrOps>  foo_set; // NOT multiset!

    FooPtr foo_ptr( new Foo( 2 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset( new Foo( 1 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset( new Foo( 3 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset ( new Foo( 2 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    std::cout << "foo_vector:\n";
    std::for_each( foo_vector.begin(), foo_vector.end(), FooPtrOps() );

    std::cout << "\nfoo_set:\n"; 
    std::for_each( foo_set.begin(), foo_set.end(), FooPtrOps() );
    std::cout << "\n";

//    can not be:
//      boost::shared_ptr ptr(new int);
    boost::shared_ptr<void> ptrVoid(new int);
//    will core !
//
//    {
//    boost::scoped_ptr<Foo> sptr(ptrVoid.get());
//    }

    {
    Foo* rawFooPtr = new Foo(8714);
    boost::shared_ptr<Foo> ptrFoo(rawFooPtr);
    boost::shared_ptr<Foo> ptrFoo2(ptrFoo);
    boost::weak_ptr<Foo> wptr(ptrFoo2);
    cout << "wptr.use_count:" << wptr.use_count() << endl;
    }

    weak_ptr<Foo> expire = returnExpire();
    cout << "wptr.expired:" << expire.expired() << endl;

    //  Expected output:
    //
    //   foo_vector:
    //   2
    //   1
    //   3
    //   2
    //   
    //   foo_set:
    //   3
    //   2
    //   1
    //
    //   Destructing a Foo with x=2
    //   Destructing a Foo with x=1
    //   Destructing a Foo with x=3
    //   Destructing a Foo with x=2
    return 0;
}
