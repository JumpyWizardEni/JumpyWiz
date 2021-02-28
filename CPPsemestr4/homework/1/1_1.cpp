#include <iostream>
using namespace std;

class A {
    int a, b;
    public:
        A (const A & x) {
            a = x.a;
            b = x.b;
            cout << 1;
        }
       
        A (int a = 0, int b = 0) {
            this -> a = a;
            b = a;
            cout << 2;
        }
        ~A () {
            cout << 3;
        }
};

void f () {
    A x (1);
    A y;
    A z = A (2.5, 4);
    A s = 6;
    A w = z;//конструктор
    x = z = w;//присваивание
}

int main() 
{
    f();
    return 0;
}