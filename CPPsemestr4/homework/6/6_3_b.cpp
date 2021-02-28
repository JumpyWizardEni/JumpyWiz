#include <iostream>
using namespace std;

class A {
public:
    static int i;
    void f() const{
        if (i >= 0)
            i = -1, g();
        cout << "f()" << endl;
    }
    void g() const{
        f();
        cout << "g()" << endl;
    }
};
int A::i = 1;
int main () {
    A::i = 1;
    const A a;
    a.f();
    a.i = 0;
    cout<<A::i;
    return 0;
}


// class A {
//     static int i;
//     void f() {
//         if (i >= 0)
//         i = -1, g();
//         cout << "f()" << endl;
//     }
//     void g() {
//         f();
//         cout << "g()" << endl;
//     }
// };
// int A::i = 1;

// int main () {
//     A::i = 1;
//     const A a;
//     a.f();
//     a.i = 0;
//     return 0;
// }