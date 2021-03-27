#include "iterator.hpp"
Iterator Iterator::operator++()
{
    Iterator it(*this);
    iter->operator++();
    return it;
}

Iterator &Iterator::operator++(int)
{
    iter->operator++(1);
    return *this;
}

Iterator::Iterator(IteratorBaseClass *oldIter) {
    iter = oldIter;
}

Iterator::Iterator(const Iterator &oldIter) {
    iter = oldIter.iter->copy();
}

Iterator::~Iterator() {
    delete iter;
}


Iterator & Iterator::operator=(const Iterator &oldIter){
    delete iter;
    iter = oldIter.iter->copy();
    return *this;
}



const float &Iterator::operator*() const { return iter->operator*();}

const float *Iterator::operator->() const { return iter->operator->();}

bool Iterator::operator==(const Iterator &secIterator) const
{
    return iter->operator==(*(secIterator.iter));
}

bool Iterator::operator!=(const Iterator &secIterator) const
{
    return iter->operator!=(*(secIterator.iter));
}

