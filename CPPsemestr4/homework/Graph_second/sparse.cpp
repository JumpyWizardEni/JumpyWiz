#include "sparse.hpp"

bool IterableSparseMatrix::areSame(float a, float b) const
{
    return (((a - b) < EPSILON) && ((b - a) < EPSILON));
}

IterableSparseMatrix::MatrixNode *IterableSparseMatrix::newNode(
    MatrixNode *prev, MatrixNode *next, int oldRow, int oldColumn,
    float oldNumber) const
{
    MatrixNode *node = new MatrixNode;
    node->prevNode = prev;
    if (prev != NULL) {
        prev->nextNode = node;
    }
    node->nextNode = next;
    node->column = oldColumn;
    node->row = oldRow;
    node->number = oldNumber;
    return node;
}

IterableSparseMatrix::IterableSparseMatrix(size_t size_)
{
    this->size = size_;
    root = NULL;
}

IterableSparseMatrix::IterableSparseMatrix(
    const IterableSparseMatrix &oldMatrix)
{
    float number;
    root = NULL;
    size = oldMatrix.size;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            number = oldMatrix.getNumber(i, j);
            if (!areSame(number, 0.0)) {
                setNumber(i, j, number);
            }
        }
    }
}

IterableSparseMatrix::~IterableSparseMatrix()
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    while (currentNode->prevNode != NULL) {
        currentNode = currentNode->prevNode;
        delete currentNode->nextNode;
    }
    delete currentNode;
}

// If there is saved number != 0 at (row, column), then result == number, else
// result == 0
float IterableSparseMatrix::getNumber(int row, int column) const
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return 0;
    }
    while (currentNode != NULL) {
        if ((currentNode->row == row) && (currentNode->column == column)) {
            return currentNode->number;
        }
        currentNode = currentNode->nextNode;
    }
    return 0;
}

void IterableSparseMatrix::setNumber(int row, int column, float number)
{
    if (root == NULL) {
        root = newNode(NULL, NULL, row, column, number);
        return;
    }
    MatrixNode *currentNode = root;
    MatrixNode *tail;
    do {
        if ((currentNode->row == row) && (currentNode->column == column)) {
            currentNode->number = number;
            return;
        }
        tail = currentNode;
        currentNode = currentNode->nextNode;
    } while (currentNode != NULL);
    // Add number at (row, column)
    currentNode = tail;
    newNode(currentNode, NULL, row, column, number);
}

bool IterableSparseMatrix::operator==(
    const IterableSparseMatrix &secondMatrix) const
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            if (!areSame(currentNode->number,
                         secondMatrix.getNumber(currentNode->row,
                                                currentNode->column))) {
                return false;
            }
            currentNode = currentNode->nextNode;
        }
    }
    currentNode = secondMatrix.root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            if (!areSame(currentNode->number,
                         getNumber(currentNode->row, currentNode->column))) {
                return false;
            }
            currentNode = currentNode->nextNode;
        }
    }
    return true;
}

bool IterableSparseMatrix::operator!=(const IterableSparseMatrix &s) const
{
    return !(*this == s);
}

IterableSparseMatrix IterableSparseMatrix::operator+(
    const IterableSparseMatrix &s) const
{
    float firstMtxNum;
    float secondMtxNum;
    IterableSparseMatrix temp(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            firstMtxNum = getNumber(i, j);
            secondMtxNum = s.getNumber(i, j);
            if ((areSame(firstMtxNum, 0.0)) && (areSame(secondMtxNum, 0.0))) {
                continue;
            }
            temp.setNumber(i, j, firstMtxNum + secondMtxNum);
        }
    }
    return temp;
}

IterableSparseMatrix IterableSparseMatrix::operator*(
    const IterableSparseMatrix &s) const
{
    float number;
    IterableSparseMatrix temp(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            number = 0;
            for (size_t k = 0; k < size; ++k) {
                number += getNumber(i, k) * s.getNumber(k, j);
            }
            if ((areSame(number, 0.0))) {
                continue;
            }
            temp.setNumber(i, j, number);
        }
    }
    return temp;
}

IterableSparseMatrix &IterableSparseMatrix::operator=(
    const IterableSparseMatrix &oldMatrix)
{
    MatrixNode *currentNode = oldMatrix.root;
    if (currentNode == NULL) {
        return *this;
    }
    while (currentNode != NULL) {
        setNumber(currentNode->row, currentNode->column, currentNode->number);
        currentNode = currentNode->nextNode;
    }
    return *this;
}

IterableSparseMatrix &IterableSparseMatrix::operator+(int position)
{
    MatrixNode *currentNode = root;
    if (root != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        if (currentNode->column == -1) {
            currentNode->row += position;
            return *this;
        }
        newNode(currentNode, NULL, position, -1, 0);

        return *this;
    }
    currentNode = newNode(NULL, NULL, position, -1, 0);
    root = currentNode;
    return *this;
}

IterableSparseMatrix::MatrixNode &IterableSparseMatrix::operator*()
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        if (currentNode->column != -1) {
            currentNode = newNode(currentNode, NULL, 0, -1, 0);
        }
        return *currentNode;
    }
    currentNode = newNode(NULL, NULL, 0, -1, 0);
    root = currentNode;
    return *currentNode;
}

IterableSparseMatrix::MatrixNode &IterableSparseMatrix::MatrixNode::operator+(
    int position)
{
    if (this->column == -1) {
        this->column = 0;
    }
    this->column += position;
    return *this;
}

float &IterableSparseMatrix::MatrixNode::operator*()
{
    MatrixNode *currentNode = this;
    int newRow = currentNode->row, newColumn = currentNode->column;
    if (newColumn == -1) {
        newColumn = 0;
    }
    while (currentNode != NULL) {
        if ((currentNode->row == newRow) &&
            (currentNode->column == newColumn) && (currentNode != this)) {
            this->prevNode->nextNode = NULL;
            delete this;
            return currentNode->number;
        }
        currentNode = currentNode->prevNode;
    }
    if (this->column == -1) {
        this->column = 0;
    }
    this->number = 0;
    return this->number;
}

const IterableSparseMatrix::MatrixNode &IterableSparseMatrix::operator*() const
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        currentNode = newNode(NULL, NULL, 0, -2, 0);
        return *currentNode;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    if (currentNode->column != -1) {
        currentNode = newNode(currentNode, NULL, 0, -1, 0);
    }
    newNode(currentNode, NULL, 0, 0, 0);
    return *currentNode->nextNode;
}
const IterableSparseMatrix &IterableSparseMatrix::operator+(int position) const
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return *this;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    if (currentNode->column == -1) {
        currentNode->row += position;
        return *this;
    }
    newNode(currentNode, NULL, position, -1, 0);
    return *this;
}

const IterableSparseMatrix::MatrixNode &IterableSparseMatrix::MatrixNode::
operator+(int position) const
{
    if (this->column != -2) {
        if (this->prevNode->column == -1) {
            this->prevNode->column = 0;
        }
        this->prevNode->column += position;
    }
    return *this;
}

float IterableSparseMatrix::MatrixNode::operator*() const
{
    if (this->column == -2) {
        delete this;
        return 0;
    }
    const MatrixNode *currentNode = this->prevNode;
    int newRow = currentNode->row, newColumn = currentNode->column;
    if (newColumn == -1) {
        newColumn = 0;
    }
    while (currentNode != NULL) {
        if ((currentNode->row == newRow) &&
            (currentNode->column == newColumn) &&
            (currentNode != this->prevNode)) {
            this->prevNode->prevNode->nextNode = NULL;
            delete this->prevNode;
            delete this;
            return currentNode->number;
        }
        currentNode = currentNode->prevNode;
    }
    this->prevNode->prevNode->nextNode = NULL;
    delete this->prevNode;
    delete this;
    return 0;
}

IterableSparseMatrix::MatrixNode &IterableSparseMatrix::operator[](
    int position)  // (matrix[x])[y]
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        currentNode = newNode(currentNode, NULL, position, -1, 0);
        return *currentNode;
    }
    currentNode = newNode(NULL, NULL, position, -1, 0);
    root = currentNode;
    return *currentNode;
}

float &IterableSparseMatrix::MatrixNode::operator[](int position)
{
    int row1 = this->row;
    MatrixNode *currentNode = this;
    while (currentNode != NULL) {
        if ((currentNode->column == position) && (currentNode->row == row1)) {
            this->prevNode->nextNode = NULL;
            delete this;
            return currentNode->number;
        }
        currentNode = currentNode->prevNode;
    }
    this->column = position;
    this->number = 0;
    return this->number;
}

const IterableSparseMatrix::MatrixNode &IterableSparseMatrix::operator[](
    int position) const
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        currentNode = newNode(NULL, NULL, position, -2, 0);
        return *currentNode;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    currentNode = newNode(currentNode, NULL, position, -1, 0);
    return *currentNode;
}

float IterableSparseMatrix::MatrixNode::operator[](int position) const
{
    const MatrixNode *currentNode = this;
    if (currentNode->column == -2) {
        delete this;
        return 0;
    }
    int newRow = currentNode->row;
    while (currentNode != NULL) {
        if ((currentNode->row == newRow) && (currentNode->column == position)) {
            this->prevNode->nextNode = NULL;
            delete this;
            return currentNode->number;
        }
        currentNode = currentNode->prevNode;
    }
    this->prevNode->nextNode = NULL;
    delete this;
    return 0;
}

Iterator IterableSparseMatrix::iterateRows(size_t) const {
    return Iterator (new SparseIteratorRows(root, size, ));
}
Iterator IterableSparseMatrix::iterateColumns(size_t) const{
    return Iterator (new );
}
Iterator IterableSparseMatrix::lastInRow() const{
    return Iterator (new );
}
Iterator IterableSparseMatrix::lastInColumn() const{
    return Iterator (new );
}

IterableSparseMatrix::SparseIteratorRows::SparseIteratorRows(float **, float **, size_t, size_t){

}

IterableSparseMatrix::SparseIteratorRows::SparseIteratorRows(const SparseIteratorRows &){

}

IterableSparseMatrix::SparseIteratorRows::~SparseIteratorRows(){

}

IteratorBaseClass &IterableSparseMatrix::SparseIteratorRows::operator++(){
    do {
        offset++;
    } while();
    return *this;
}

IteratorBaseClass &IterableSparseMatrix::SparseIteratorRows::operator++(int){
    return *this;
}

bool IterableSparseMatrix::SparseIteratorRows::operator==(const IteratorBaseClass &secIterator) const{
    return offset == secIterator.offset;

}

bool IterableSparseMatrix::SparseIteratorRows::operator!=(const IteratorBaseClass &secIterator) const{
    return offset != secIterator.offset;

}

const float &IterableSparseMatrix::SparseIteratorRows::operator*() const{
    return getNumber(, offset);
}

const float *IterableSparseMatrix::SparseIteratorRows::operator->() const{

}

IteratorBaseClass *IterableSparseMatrix::SparseIteratorRows::copy() const{

}


IterableSparseMatrix::SparseIteratorColumns::SparseIteratorColumns(float **, float **, size_t, size_t){

}

IterableSparseMatrix::SparseIteratorColumns::SparseIteratorColumns(const SparseIteratorColumns &){

}

IterableSparseMatrix::SparseIteratorColumns::~SparseIteratorColumns(){

}

IteratorBaseClass &IterableSparseMatrix::SparseIteratorColumns::operator++() {

}

IteratorBaseClass &IterableSparseMatrix::SparseIteratorColumns::operator++(int){

}

bool IterableSparseMatrix::SparseIteratorColumns::operator==(const IteratorBaseClass &secIterator) const{
}

bool IterableSparseMatrix::SparseIteratorColumns::operator!=(const IteratorBaseClass &secIterator) const{
}

const float &IterableSparseMatrix::SparseIteratorColumns::operator*() const{

}

const float *IterableSparseMatrix::SparseIteratorColumns::operator->() const{

}

IteratorBaseClass *IterableSparseMatrix::SparseIteratorColumns::copy() const{

}
