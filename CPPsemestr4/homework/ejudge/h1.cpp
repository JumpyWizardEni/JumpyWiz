#include <iostream>
using std::cout;
using std::endl;

class Queue 
{
private:
    size_t maxSize;
    size_t currentSize;
    int *numbers;
public:
    Queue(size_t size);
    Queue(const Queue & oldQueue);
    ~Queue();
    size_t size() const;
    size_t capacity() const;
    Queue & operator =(const Queue & oldQueue);
    Queue & operator <<(int number);
    Queue & operator >> (int & number);
};

int main()
{
    const Queue constQueue(10);
    cout << "constQueue current size: " << constQueue.size() << endl;
    cout << "constQueue max size: " << constQueue.capacity() << endl;
    Queue firstQueue(10);
    Queue secondQueue = Queue(10);
    cout << "firstQueue current size: " << firstQueue.size() << endl;
    cout << "firstQueue max size: " << firstQueue.capacity() << endl;
    cout << "secondQueue current size: " << secondQueue.size() << endl;
    cout << "secondQueue max size: " << secondQueue.capacity() << endl;
    firstQueue << 10 << 20;
    cout << "firstQueue size after adding 2 numbers: " << firstQueue.size() << endl;
    secondQueue = firstQueue;
    cout << "secondQueue size after adding 2 numbers: " << secondQueue.size() << endl;
    int num1, num2;
    firstQueue >> num1 >> num2;
    cout << "firstQueue size after extracting 2 numbers: " << firstQueue.size() << endl;
    cout << "First number: " << num1 << ", second number: " << num2 << endl;
    secondQueue >> num1 >> num2;
    cout << "secondQueue size after extracting 2 numbers: " << secondQueue.size() << endl;
    cout << "First number: " << num1 << ", second number: " << num2 << endl;
    return 0;
}

Queue::Queue(size_t size)
{
    maxSize = size;
    currentSize = 0;
    numbers = new int[size];
    for (size_t i = 0; i < size; ++i) {
        numbers[i] = 0;
    }
}

Queue::Queue(const Queue & oldQueue)
{
    maxSize = oldQueue.maxSize;
    currentSize = oldQueue.currentSize;
    numbers = new int[maxSize];
    for (size_t i = 0; i < maxSize; ++i) {
        numbers[i] = oldQueue.numbers[i];
    }
}

Queue::~Queue()
{
    delete[] numbers;
}

size_t Queue::size() const
{
    return currentSize;
}

size_t Queue::capacity() const
{
    return maxSize;
}

//Here we accept that this->maxSize = oldQueue.maxSize
Queue & Queue::operator =(const Queue & oldQueue)
{
    currentSize = oldQueue.currentSize;
    for (size_t i = 0; i < maxSize; ++i) {
        numbers[i] = oldQueue.numbers[i];
    };
    return *this;
}

Queue & Queue::operator <<(int number)
{
    numbers[currentSize] = number;
    currentSize++;
    return *this;
}

Queue & Queue::operator >> (int & number)
{
    number = numbers[0];
    for (size_t i = 0; i < currentSize - 1; ++i) {
        numbers[i] = numbers[i + 1];
    }
    currentSize--;
    return *this;
}