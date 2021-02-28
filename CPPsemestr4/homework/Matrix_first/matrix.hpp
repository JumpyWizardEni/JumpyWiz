#include <cstring>
#include <iostream>


#define EPSILON 0.001

class SparseMatrix {
private: 
    struct MatrixNode{
        int row;
        int column;
        float number;
        MatrixNode *nextNode;
        MatrixNode *prevNode;
        float & operator [](int);
        float operator [](int) const;
        MatrixNode & operator +(int);
        float & operator *();
        const MatrixNode & operator +(int) const;
        float operator *() const;
    };   
    MatrixNode *root;
    size_t rowsSize;
    size_t columnsSize;
    bool areSame(float, float) const;
    MatrixNode* newNode(MatrixNode *, MatrixNode *, int, int, float) const;
public:
    SparseMatrix(size_t, size_t);
    SparseMatrix(const SparseMatrix &);
    ~SparseMatrix();
    float getNumber(int, int) const;
    void setNumber(int, int, float);
    size_t getRowsSize() const;
    size_t getColumnsSize() const;
    bool operator ==(const SparseMatrix &) const;
    bool operator !=(const SparseMatrix &) const;
    SparseMatrix operator +(const SparseMatrix &) const;
    SparseMatrix & operator =(const SparseMatrix &);
    SparseMatrix operator *(const SparseMatrix &) const;
    MatrixNode & operator *();
    SparseMatrix & operator +(int);
    const MatrixNode & operator *() const;
    const SparseMatrix & operator +(int) const;
    MatrixNode & operator [](int);
    const MatrixNode & operator [](int) const;
};