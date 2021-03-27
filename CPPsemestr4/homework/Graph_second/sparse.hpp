#include <cstring>
#include "interface.hpp"
class IterableSparseMatrix : public IterableSquareMatrix {
private:
    struct MatrixNode {
        int row;
        int column;
        float number;
        MatrixNode *nextNode;
        MatrixNode *prevNode;
        float &operator[](int);
        float operator[](int) const;
        MatrixNode &operator+(int);
        float &operator*();
        const MatrixNode &operator+(int) const;
        float operator*() const;
    };
    class SparseIteratorRows : public IteratorBaseClass {
    public:
        SparseIteratorRows(float **, float **, size_t, size_t);
        SparseIteratorRows(const SparseIteratorRows &);
        ~SparseIteratorRows();
        IteratorBaseClass &operator++() override;
        IteratorBaseClass &operator++(int) override;
        bool operator==(const IteratorBaseClass &secIterator) const override;
        bool operator!=(const IteratorBaseClass &secIterator) const override;
        const float &operator*() const override;
        const float *operator->() const override;
        IteratorBaseClass *copy() const override;
    };
    class SparseIteratorColumns : public IteratorBaseClass {
    public:
        SparseIteratorColumns(float **, float **, size_t, size_t);
        SparseIteratorColumns(const SparseIteratorColumns &);
        ~SparseIteratorColumns();
        IteratorBaseClass &operator++() override;
        IteratorBaseClass &operator++(int) override;
        bool operator==(const IteratorBaseClass &secIterator) const override;
        bool operator!=(const IteratorBaseClass &secIterator) const override;
        const float &operator*() const override;
        const float *operator->() const override;
        IteratorBaseClass *copy() const override;
    };
    MatrixNode *root;
    size_t size;
    bool areSame(float, float) const;
    MatrixNode *newNode(MatrixNode *, MatrixNode *, int, int, float) const;

public:
    IterableSparseMatrix(size_t);
    IterableSparseMatrix(const IterableSparseMatrix &);
    ~IterableSparseMatrix();

    float getNumber(int, int) const;
    void setNumber(int, int, float);
    size_t getSize() const;
    bool operator==(const IterableSparseMatrix &) const;
    bool operator!=(const IterableSparseMatrix &) const;
    IterableSparseMatrix operator+(const IterableSparseMatrix &) const;
    IterableSparseMatrix &operator=(const IterableSparseMatrix &);
    IterableSparseMatrix operator*(const IterableSparseMatrix &)const;
    MatrixNode &operator*();
    IterableSparseMatrix &operator+(int);
    const MatrixNode &operator*() const;
    const IterableSparseMatrix &operator+(int) const;
    MatrixNode &operator[](int);
    const MatrixNode &operator[](int) const;

    Iterator iterateRows(size_t) const;
    Iterator iterateColumns(size_t) const;
    Iterator lastInRow() const;
    Iterator lastInColumn() const;
};
