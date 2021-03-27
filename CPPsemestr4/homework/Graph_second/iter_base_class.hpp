#include <iostream>
class IteratorBaseClass {
    friend class IterableDenseMatrix;
    friend class IterableSparseMatrix;
protected:
    size_t offset;
    size_t size;
    float **pointer;
    float **lastElement;
    float *MatrixNode;
public:
    virtual IteratorBaseClass & operator++() = 0;
    virtual IteratorBaseClass & operator++(int) = 0;
    virtual const float & operator*() const = 0;
    virtual const float * operator->() const = 0;
    virtual bool operator==(const IteratorBaseClass &secIterator) const = 0;
    virtual bool operator!=(const IteratorBaseClass &secIterator) const = 0;
    virtual IteratorBaseClass * copy() const = 0;
    virtual ~IteratorBaseClass();
};