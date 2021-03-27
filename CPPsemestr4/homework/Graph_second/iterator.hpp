#include "iter_base_class.hpp"
class Iterator {
protected:
    IteratorBaseClass *iter;
public:
    Iterator(IteratorBaseClass *);
    Iterator(const Iterator &);
    ~Iterator();
    Iterator & operator=(const Iterator &);
    Iterator operator++();
    Iterator & operator++(int);
    const float & operator*() const;
    const float * operator->() const;
    bool operator==(const Iterator &secIterator) const;
    bool operator!=(const Iterator &secIterator) const;
};