#include <cstring>
#include <iostream>


#define EPSILON 0.001

class SparceMatrix {
private: 
    struct MatrixNode{
        float number;
        int row;
        int column;
        MatrixNode *nextNode;
        MatrixNode *prevNode;
        float & operator [](int position);
        float operator [](int position) const;
        MatrixNode & operator +(int position);
        float & operator *();
        const MatrixNode & operator +(int position) const;
        float operator *() const;
    };   
    MatrixNode *root;
    size_t notNullNumbersSize;
    size_t rowsSize;
    size_t columnsSize;
    bool areSame(double, double) const;
public:
    SparceMatrix(size_t, size_t);
    SparceMatrix(const SparceMatrix &);
    ~SparceMatrix();
    float getNumber(int, int) const;
    void setNumber(int, int, double);
    size_t getRowsSize() const;
    size_t getColumnsSize() const;
    bool operator ==(const SparceMatrix &) const;
    bool operator !=(const SparceMatrix &) const;
    SparceMatrix operator +(const SparceMatrix &) const;
    SparceMatrix & operator =(const SparceMatrix &);
    SparceMatrix operator *(const SparceMatrix &) const;
    MatrixNode & operator *();
    SparceMatrix & operator +(int position);
    const MatrixNode & operator *() const;
    const SparceMatrix & operator +(int position) const;
    MatrixNode & operator [](int position);
    const MatrixNode & operator [](int position) const;
};