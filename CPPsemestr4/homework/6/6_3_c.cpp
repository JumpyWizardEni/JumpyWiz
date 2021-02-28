#include <iostream>
using namespace std;


class A {
public:
    static int i;
    void f() const {
        if (i < 0)
        g(i);
        cout << "f ()" << endl;
    }
    void g(int n) const{
        i = n;
        f();
        cout << "g ()" << endl;
    }
};
int A::i = 1;
int main () {
    const A a;
    a.g(2);
    return 0;
}



// class A {
//     static int i;
//     void f() const {
//         if (i < 0)
//             g(i);
//         cout << "f ()" << endl;
//     }
//     void g(int & n) {
//         i = n;
//         f();
//         cout << "g ()" << endl;
//     }
// };

// int A::i = 1;

// int main () {
//     const A a;
//     a.g(2);
//     return 0;
// }