#include <cstdio>

struct S {
    int x;
    S (int n) 
    { 
        x = n; 
        printf (" Cons "); 
    }
    S (const S & a) 
    { 
        x = a.x; 
        printf (" Copy "); 
    }
    ~S ( ) 
    { 
        printf ("Des "); 
    }
};

S f(S y) {
    y = S(3);//Cons Des
    return y;//Copy Des
}

int main () {
    S s (1);//Cons
    f (s);//Copy Des
    printf ("%d ", s.x);//1
    return 0;//Des
}