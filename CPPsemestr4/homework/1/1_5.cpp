#include <iostream>

class B {
private:
    int number;
public:
    B(int a = 10) {
        number = a;
    }
    B(B & another_b) {
        number = another_b.number + 10;
    }
    int get() {
        return number;
    }
};






int main () {
    B b1, b2 = b1, b3 (b2);
    std::cout << b1.get() << b2.get() << b3.get () << std::endl;
    return 0;
}