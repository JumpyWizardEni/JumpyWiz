#include <iostream>
#include <string>
#include "balance_stack.hpp"
//символьный литерал имеет тип char
int main() {
    const char *s = "({)}";
    Stack stack;
    while (*s != 0) {
        if ((*s == '(') || (*s == '{')) {
            stack.push(*s);
        }
        else {
            char c = stack.pop();
            if (((c == '(') && (*s != ')')) || ((c == '{') && (*s != '}'))) {
                exit(1);
            }
        }
        s++;
    }


}