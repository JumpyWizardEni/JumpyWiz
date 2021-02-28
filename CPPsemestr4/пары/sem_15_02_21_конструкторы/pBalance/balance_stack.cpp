#include "balance_stack.hpp"
#include <cstdlib>
#include <cstring>

void Stack::push(char symbol) {
    this->size ++;
    this->buf = (char *)realloc(buf, size * sizeof(*buf));
    this->buf[size - 1] = symbol;
}

char Stack::pop() {
    char c = buf[size - 1];
    this->size --;
    return c;
}

Stack::Stack(Stack & s) {
    this->size = s.size;
    this->buf = (char *) malloc(s.size * sizeof(*buf));
    for (int i = 0; i < size; ++i) {
        this->buf[i] = s.buf[i];
    }
}

Stack::Stack() {
    this->size = 0;
    this->buf = NULL;
}

Stack::~Stack() {
    free(buf);
}

Stack & Stack::operator=(Stack & s) {
    buf = (char *)realloc(buf, s.size);
    size = s.size;
    memcpy(buf, s.buf, size * sizeof(*buf));
    return *this;
}