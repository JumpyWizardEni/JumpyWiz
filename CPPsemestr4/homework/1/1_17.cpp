#include <cstdio>

struct S {
int x;
    S(int n) { x = n; printf(" Cons "); }
    S(const S & a) { x = a.x; printf(" Copy "); }
    ~S() { printf("Des "); }
};
S f( S & y ) {//нет Copy
    y = S(3);//Cons Des
    return y;//Copy 
}
int main () {
    S s(1);//Cons
    f (s);//Des
    printf("%d ", s.x);//3
    return 0;//Des
}