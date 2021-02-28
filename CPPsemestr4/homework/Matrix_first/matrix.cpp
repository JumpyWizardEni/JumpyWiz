#include "matrix.hpp"

bool SparseMatrix::areSame(float a, float b) const
{
    return (((a - b) < EPSILON) && ((b - a) < EPSILON));
}

SparseMatrix::MatrixNode* SparseMatrix::newNode(MatrixNode *prev, MatrixNode *next, int oldRow, int oldColumn, float oldNumber) const
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

SparseMatrix::SparseMatrix(size_t reqRowsSize, size_t reqColumsSize)
{
    this->rowsSize = reqRowsSize;
    this->columnsSize = reqColumsSize;
    root = NULL;
}

SparseMatrix::SparseMatrix(const SparseMatrix & oldMatrix)
{
    float number;
    root = NULL;
    rowsSize = oldMatrix.rowsSize;
    columnsSize = oldMatrix.columnsSize;
    for (size_t i = 0; i < rowsSize; ++i) {
        for (size_t j = 0; j < columnsSize; ++j) {
            number = oldMatrix.getNumber(i, j);
            if (!areSame(number, 0.0)) {
                setNumber(i, j, number);
            }
        }
    }
}

SparseMatrix::~SparseMatrix()
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
float SparseMatrix::getNumber(int row, int column) const
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return 0;
    }
    while(currentNode != NULL) {
        if ((currentNode->row == row) && (currentNode->column == column)) {
            return currentNode->number;
        }
        currentNode = currentNode->nextNode;
    } 
    return 0;
}

void SparseMatrix::setNumber(int row, int column, float number)
{
    if (root == NULL) {
        if (areSame(number, 0.0)) {
            return;
        }
        root = newNode(NULL, NULL, row, column, number);
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
    newNode(currentNode, NULL, row, column, number);
}

size_t SparseMatrix::getRowsSize() const
{
    return rowsSize;
}

size_t SparseMatrix::getColumnsSize() const
{
    return columnsSize;
}

bool SparseMatrix::operator ==(const SparseMatrix & secondMatrix) const
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

bool SparseMatrix::operator !=(const SparseMatrix & s) const
{
    return !(*this == s);
}

SparseMatrix SparseMatrix::operator +(const SparseMatrix & s) const
{
    float firstMtxNum;
    float secondMtxNum;
    SparseMatrix temp(rowsSize, columnsSize);
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

SparseMatrix SparseMatrix::operator *(const SparseMatrix & s) const
{
    float number;
    SparseMatrix temp(rowsSize, s.columnsSize);
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

SparseMatrix & SparseMatrix::operator =(const SparseMatrix & oldMatrix) 
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return *this;
    }
    while (currentNode != NULL) {
        setNumber(currentNode->row, currentNode->column, currentNode->number);
    }
    return *this;
} 

SparseMatrix & SparseMatrix::operator +(int position) 
{      
    MatrixNode *currentNode = root;
    if (root != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        newNode(currentNode, NULL, position, -1, 0);
        
        return *this;
    }
    currentNode = newNode(NULL, NULL, position, -1, 0);
    root = currentNode;
    return *this;
    
}

SparseMatrix::MatrixNode & SparseMatrix::operator *() 
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        if (areSame(currentNode->number, 0)) {
            return *currentNode;
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

SparseMatrix::MatrixNode & SparseMatrix::MatrixNode::operator +(int position) 
{
    this->column = position;
    return *this;
}

float & SparseMatrix::MatrixNode::operator *() 
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

const SparseMatrix::MatrixNode & SparseMatrix::operator *() const
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
const SparseMatrix & SparseMatrix::operator +(int position) const 
{
    MatrixNode *currentNode = root;
    if (currentNode == NULL) {
        return *this;
    }
    while (currentNode->nextNode != NULL) {
        currentNode = currentNode->nextNode;
    }
    newNode(currentNode, NULL, position, -1, 0);
    return *this;
}

const SparseMatrix::MatrixNode & SparseMatrix::MatrixNode::operator +(int position) const
{
    if(this->column != -2) {
        this->prevNode->column = position;
    }
    return *this;
}
float SparseMatrix::MatrixNode::operator *() const 
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
        if ((currentNode->row == newRow) && (currentNode->column == newColumn) && (currentNode != this->prevNode))
        {
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

SparseMatrix::MatrixNode & SparseMatrix::operator [](int position)// (matrix[x])[y]
{
    MatrixNode *currentNode = root;
    if (currentNode != NULL) {
        while(currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }
        if (areSame(currentNode->number, 0)) {
            return *currentNode;
        }
        currentNode = newNode(currentNode, NULL, position, -1, 0);
        return *currentNode;
    }
    currentNode = newNode(NULL, NULL, position, -1, 0);
    root = currentNode;
    return *currentNode;
}

float & SparseMatrix::MatrixNode::operator [](int position)
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

const SparseMatrix::MatrixNode & SparseMatrix::operator [](int position) const 
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

float SparseMatrix::MatrixNode::operator [](int position) const
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