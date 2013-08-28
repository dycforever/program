#include <iostream>
#include <set>
using namespace std;

int main ()
{
    set<int> c;

    c.insert(1);
    c.insert(2);
    c.insert(4);
    c.insert(5);
    c.insert(6);

    // lower_bound means first elem >= $value
    // upper_bound means first elem > $value
    // equal_range means [ lower_bound(), upper_bound() )

    cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
    cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
    cout << "equal_range(3): " << *c.equal_range(3).first << " "
        << *c.equal_range(3).second << endl;
    cout << endl;
    // output:
    //      lower_bound(3): 4
    //      upper_bound(3): 4
    //      equal_range(3): 4 4
    
    cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
    cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
    cout << "equal_range(5): " << *c.equal_range(5).first << " "
        << *c.equal_range(5).second << endl;
    // output:
    //      lower_bound(5): 5
    //      upper_bound(5): 6
    //      equal_range(5): 5 6

}
