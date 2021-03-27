#include "iterator.hpp"
#define EPSILON 0.001

class IterableSquareMatrix {
public:
    virtual Iterator iterateRows(size_t) const = 0;
    virtual Iterator iterateColumns(size_t) const = 0;
    virtual Iterator lastInRow() const = 0;
    virtual Iterator lastInColumn() const = 0;
    virtual size_t getSize() const = 0;
    virtual ~IterableSquareMatrix();
};