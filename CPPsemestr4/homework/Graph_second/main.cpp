class A {
public:
    virtual void a() {};
};

class B : public A {
public:
};

int main(int argc, char const *argv[])
{
    B p;
    p.a();
    return 0;
}