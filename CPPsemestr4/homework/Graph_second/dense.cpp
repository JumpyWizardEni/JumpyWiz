#include "dense.hpp"
#include <cstring>

bool IterableDenseMatrix::areSame(float a, float b)
{
    return (((a - b) < EPSILON) && ((b - a) < EPSILON));
}

IterableDenseMatrix::IterableDenseMatrix(size_t neededSize)
{
    if (neededSize == 0) {
        throw std::length_error(
            "IterableDenseMatrix(size_t neededSize): Size must be > 0");
    }
    size = neededSize;
    elements = (float **)malloc(size * sizeof(*elements));
    for (size_t i = 0; i < size; i++) {
        elements[i] = (float *)malloc(size * sizeof(**elements));
    }
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            elements[i][j] = 0;
        }
    }
};

IterableDenseMatrix::IterableDenseMatrix(const IterableDenseMatrix &oldMatrix)
{
    size = oldMatrix.size;
    elements = (float **)malloc(size * sizeof(*elements));
    for (size_t i = 0; i < size; i++) {
        elements[i] = (float *)malloc(size * sizeof(**elements));
    }
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            elements[i][j] = oldMatrix.elements[i][j];
        }
    }
}

IterableDenseMatrix::~IterableDenseMatrix()
{
    for (size_t i = 0; i < size; i++) {
        free(elements[i]);
    }
    free(elements);
}

IterableDenseMatrix &IterableDenseMatrix::operator=(
    const IterableDenseMatrix &oldMatrix)
{
    size = oldMatrix.size;
    elements = (float **)malloc(size * sizeof(*elements));
    for (size_t i = 0; i < size; i++) {
        elements[i] = (float *)malloc(size * sizeof(**elements));
    }
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            elements[i][j] = oldMatrix.elements[i][j];
        }
    }
    return *this;
}

IterableDenseMatrix::Proxy IterableDenseMatrix::operator[](size_t row)
{
    if (row >= size) {
        throw std::out_of_range(
            "IterableDenseMatrix::operator[](size_t row): Row is out of range");
    }
    return Proxy(*this, row);
}

IterableDenseMatrix::Proxy::Proxy(IterableDenseMatrix &mtx, size_t row_)
    : parent(mtx), row(row_)
{
}

float &IterableDenseMatrix::Proxy::operator[](size_t column)
{
    if (column >= parent.size) {
        throw std::out_of_range(
            "IterableDenseMatrix::Proxy::operator[](size_t column): Column is "
            "out of range");
    }
    return parent.elements[row][column];
}

Iterator IterableDenseMatrix::iterateRows(size_t row) const
{  // from 0 to size - 1
    if (row >= size) {
        throw std::out_of_range(
            "IterableDenseMatrix::iterateRows(size_t row): Row is out of "
            "range");
    }
    return Iterator(new DenseIteratorRows(&(elements[row]), 0, size));
}

Iterator IterableDenseMatrix::iterateColumns(size_t column) const
{  // from 0 to size - 1
    if (column >= size) {
        throw std::out_of_range(
            "IterableDenseMatrix::iterateColumns(size_t column): Column is out "
            "of range");
    }
    return Iterator(
        new DenseIteratorColumns(elements, &elements[size], column, size));
}

Iterator IterableDenseMatrix::lastInRow() const
{
    return Iterator(new DenseIteratorRows(elements, size, size));
}
Iterator IterableDenseMatrix::lastInColumn() const
{
    return Iterator(
        new DenseIteratorColumns(&elements[size], &elements[size], size, size));
}

size_t IterableDenseMatrix::getSize() const { return size; }

IterableDenseMatrix::DenseIteratorRows::DenseIteratorRows(float **ptr,
                                                          size_t row,
                                                          size_t size_)
{
    pointer = ptr;
    offset = row;
    size = size_;
}
IterableDenseMatrix::DenseIteratorRows::DenseIteratorRows(
    const DenseIteratorRows &oldIter)
{
    pointer = oldIter.pointer;
    offset = oldIter.offset;
    size = oldIter.size;
}

IterableDenseMatrix::DenseIteratorRows::~DenseIteratorRows() {}

IterableDenseMatrix::DenseIteratorColumns::DenseIteratorColumns(float **ptr,
                                                                float **last,
                                                                size_t col,
                                                                size_t size_)
{
    pointer = ptr;
    lastElement = last;
    offset = col;
    size = size_;
}

IterableDenseMatrix::DenseIteratorColumns::DenseIteratorColumns(
    const DenseIteratorColumns &oldIter)
{
    pointer = oldIter.pointer;
    lastElement = oldIter.lastElement;
    offset = oldIter.offset;
    size = oldIter.size;
}

IterableDenseMatrix::DenseIteratorColumns::~DenseIteratorColumns() {}

IteratorBaseClass &IterableDenseMatrix::DenseIteratorRows::operator++()
{
    do {
        offset++;
    } while (areSame(*(*pointer + offset), 0.0) && (offset < size));
    return *this;
}

IteratorBaseClass &IterableDenseMatrix::DenseIteratorRows::operator++(int)
{
    do {
        offset++;
    } while (areSame(*(*pointer + offset), 0.0) && (offset < size));
    return *this;
}

IteratorBaseClass &IterableDenseMatrix::DenseIteratorColumns::operator++()
{
    do {
        pointer++;
    } while ((pointer != lastElement) && areSame(*(*pointer + offset), 0.0));
    return *this;
}
IteratorBaseClass &IterableDenseMatrix::DenseIteratorColumns::operator++(int)
{
    do {
        pointer++;
    } while ((pointer != lastElement) && areSame(*(*pointer + offset), 0.0));
    return *this;
}

const float &IterableDenseMatrix::DenseIteratorRows::operator*() const
{
    return *(*pointer + offset);
}
const float *IterableDenseMatrix::DenseIteratorRows::operator->() const
{
    return *pointer;
}

const float &IterableDenseMatrix::DenseIteratorColumns::operator*() const
{
    return *(*pointer + offset);
}
const float *IterableDenseMatrix::DenseIteratorColumns::operator->() const
{
    return *pointer + offset;
}

bool IterableDenseMatrix::DenseIteratorRows::operator==(
    const IteratorBaseClass &secIterator) const
{
    return offset == secIterator.offset;
}
bool IterableDenseMatrix::DenseIteratorRows::operator!=(
    const IteratorBaseClass &secIterator) const
{
    return offset != secIterator.offset;
}

bool IterableDenseMatrix::DenseIteratorColumns::operator==(
    const IteratorBaseClass &secIterator) const
{
    return pointer == secIterator.pointer;
}
bool IterableDenseMatrix::DenseIteratorColumns::operator!=(
    const IteratorBaseClass &secIterator) const
{
    return pointer != secIterator.pointer;
}

IteratorBaseClass *IterableDenseMatrix::DenseIteratorRows::copy() const
{
    return new DenseIteratorRows(pointer, offset, size);
}

IteratorBaseClass *IterableDenseMatrix::DenseIteratorColumns::copy() const
{
    return new DenseIteratorColumns(pointer, lastElement, offset, size);
}

IteratorBaseClass::~IteratorBaseClass() {}

IterableSquareMatrix::~IterableSquareMatrix() {}