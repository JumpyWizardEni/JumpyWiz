#include "matrix.hpp"

bool SparceMatrix::areSame(double a, double b) const
{
    return (((a - b) < EPSILON) && ((b - a) < EPSILON));
}

SparceMatrix::SparceMatrix(size_t reqRowsSize, size_t reqColumsSize)
{
    this->rowsSize = reqRowsSize;
    this->columnsSize = reqColumsSize;
    notNullNumbersSize = 0;
    root = NULL;
}

SparceMatrix::SparceMatrix(const SparceMatrix & oldMatrix)
{
    for (size_t i = 0; i < rowsSize; ++i) {
        for (size_t j = 0; j < columnsSize; ++j) {
            setNumber(i, j, oldMatrix.getNumber(i, j));
        }
    }
}

SparceMatrix::~SparceMatrix()
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return;
    }
    while(currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }

    while(currentNode->prevNode != NULL) {
        currentNode  = currentNode->prevNode;
        delete currentNode->nextNode;
    }
    delete currentNode;
}

//If there is saved number != 0 at (row, column), then result == number, else result == 0 
float SparceMatrix::getNumber(int row, int column) const
{
    MatrixNode *currentNode = root;
    while(currentNode != NULL) {
        if ((currentNode->row == row) && (currentNode->column == column)) {
            return currentNode->number;
        }
        currentNode = currentNode->nextNode;
    } 
    return 0;
}

void SparceMatrix::setNumber(int row, int column, double number)
{
    if (root == NULL) {
        if (areSame(number, 0.0)) {
            return;
        }
        root = new MatrixNode;
        root->number = number;
        root->row = row;
        root->column = column;
        root->nextNode = NULL;
        root->prevNode = NULL;
        return;
    }
    MatrixNode *currentNode = root;
    MatrixNode *tail;
    do {
        if ((currentNode->row == row) && (currentNode->column == column)) {
            if (areSame(number, 0.0)) {//If number == 0, we dont need this number in the matrix
                currentNode->prevNode->nextNode = currentNode->nextNode;
                currentNode->nextNode->prevNode = currentNode->prevNode;
                delete currentNode;
                return;
            }
            currentNode -> number = number;//There is another number at this place
            return;
        }
        tail = currentNode;
        currentNode = currentNode->nextNode;
    } while(currentNode != NULL);
    //Add number at (row, column)
    currentNode = tail;
    currentNode->nextNode = new MatrixNode;
    currentNode->nextNode->prevNode = currentNode;
    currentNode = currentNode->nextNode;
    currentNode->nextNode = NULL;
    currentNode->row = row;
    currentNode->column = column;
    currentNode->number = number;
}

size_t SparceMatrix::getRowsSize() const
{
    return rowsSize;
}

size_t SparceMatrix::getColumnsSize() const
{
    return columnsSize;
}

bool SparceMatrix::operator ==(const SparceMatrix & secondMatrix) const
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while(currentNode->nextNode != NULL) {
            if (!areSame(currentNode->number, secondMatrix.getNumber(currentNode->row, currentNode->column))) {
                return false;
            }
            currentNode  = currentNode->nextNode;
        }
    }
    currentNode = secondMatrix.root;
    if (currentNode != NULL) {
        while(currentNode->nextNode != NULL) {
            if (!areSame(currentNode->number, getNumber(currentNode->row, currentNode->column))) {
                return false;
            }
            currentNode  = currentNode->nextNode;
        }
    }
    return true;
}

bool SparceMatrix::operator !=(const SparceMatrix & s) const
{
    return !(*this == s);
}

SparceMatrix SparceMatrix::operator +(const SparceMatrix & s) const
{
    float firstMtxNum;
    float secondMtxNum;
    SparceMatrix temp(rowsSize, columnsSize);
    for (size_t i = 0; i < rowsSize; ++i) {
        for (size_t j = 0; j < columnsSize; ++j) {
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

SparceMatrix SparceMatrix::operator *(const SparceMatrix & s) const
{
    float number;
    SparceMatrix temp(rowsSize, s.columnsSize);
    for (size_t i = 0; i < rowsSize; ++i) {
        for (size_t j = 0; j < s.columnsSize; ++j) {
            number = 0;
            for(size_t k = 0; k < columnsSize; ++k) {
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

SparceMatrix & SparceMatrix::operator =(const SparceMatrix & oldMatrix) 
{
    for (size_t i = 0; i < rowsSize; ++i) {
        for (size_t j = 0; j < columnsSize; ++j) {
            setNumber(i, j, oldMatrix.getNumber(i, j));
        }
    }
    return *this;
} 

SparceMatrix & SparceMatrix::operator +(int position) 
{      
    MatrixNode *currentNode = root;
    if (root != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        currentNode->nextNode = new MatrixNode;
        currentNode->nextNode->prevNode = currentNode;
        currentNode = currentNode->nextNode;
        currentNode->row = position;
        currentNode->column = -1;
        currentNode->nextNode = NULL;
        return *this;
    }
    currentNode = new MatrixNode;
    currentNode->prevNode = NULL;
    currentNode->nextNode = NULL;
    currentNode->row = position;
    currentNode->column = -1;
    root = currentNode;
    return *this;
    
}

SparceMatrix::MatrixNode & SparceMatrix::operator *() 
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        if (currentNode->column != -1) {
            currentNode->nextNode = new MatrixNode;
            currentNode->nextNode->prevNode = currentNode;
            currentNode = currentNode->nextNode;
            currentNode->row = 0;
            currentNode->column = -1;
            currentNode->nextNode = NULL;
        }
        return *currentNode;

    }
    currentNode = new MatrixNode;
    currentNode->prevNode = NULL;
    currentNode->nextNode = NULL;
    currentNode->row = 0;
    currentNode->column = -1;
    root = currentNode;
    return *currentNode;
    
    
}

SparceMatrix::MatrixNode & SparceMatrix::MatrixNode::operator +(int position) 
{
    this->column = position;
    return *this;
}

float & SparceMatrix::MatrixNode::operator *() 
{
    MatrixNode *currentNode = this;
    int newRow = currentNode->row, newColumn = currentNode->column; 
    if (newColumn == -1) {
        newColumn = 0;
    }
    while (currentNode != NULL) {
        if ((currentNode->row == newRow) && (currentNode->column == newColumn) && (currentNode != this))
        {
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

SparceMatrix::MatrixNode & SparceMatrix::operator [](int position)// (matrix[x])[y]
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while(currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        currentNode->nextNode = new MatrixNode;
        currentNode->nextNode->prevNode = currentNode;
        currentNode = currentNode->nextNode;
        currentNode->row = position;
        currentNode->column = -1;
        currentNode->nextNode = NULL;
        return *currentNode;
    }
    currentNode = new MatrixNode;
    currentNode->prevNode = NULL;
    currentNode->nextNode = NULL;
    currentNode->row = position;
    currentNode->column = -1;
    root = currentNode;
    return *currentNode;
}

const SparceMatrix::MatrixNode & SparceMatrix::operator *() const
{
    MatrixNode *currentNode = NULL;
    return *currentNode;
}
const SparceMatrix & SparceMatrix::operator +(int position) const 
{
    return *this;
}

const SparceMatrix::MatrixNode & SparceMatrix::MatrixNode::operator +(int position) const
{
    return *this;
}
float SparceMatrix::MatrixNode::operator *() const 
{
    return 0;
}

float & SparceMatrix::MatrixNode::operator [](int position)
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

const SparceMatrix::MatrixNode & SparceMatrix::operator [](int position) const 
{
    MatrixNode *currentNode = NULL;
    return *currentNode;
}

float SparceMatrix::MatrixNode::operator [](int position) const
{
    return 0;
}