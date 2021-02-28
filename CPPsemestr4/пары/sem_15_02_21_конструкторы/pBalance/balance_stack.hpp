class Stack {
    char *buf;
    int size;
public:
    Stack();
    Stack(Stack & s);
    ~Stack();
    Stack & operator=(Stack & s);
    void push(char symbol);
    char pop();
};