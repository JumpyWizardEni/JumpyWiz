#include "interface.hpp"
class IterableDenseMatrix : public IterableSquareMatrix {
private:
    float **elements;
    size_t size;
    static bool areSame(float, float);
    class DenseIteratorRows : public IteratorBaseClass {
    public:
        DenseIteratorRows(float **, size_t, size_t);
        DenseIteratorRows(const DenseIteratorRows &);
        ~DenseIteratorRows();
        IteratorBaseClass &operator++() override;
        IteratorBaseClass &operator++(int) override;
        bool operator==(const IteratorBaseClass &secIterator) const override;
        bool operator!=(const IteratorBaseClass &secIterator) const override;
        const float &operator*() const override;
        const float *operator->() const override;
        IteratorBaseClass *copy() const override;
    };
    class DenseIteratorColumns : public IteratorBaseClass {
    public:
        DenseIteratorColumns(float **, float **, size_t, size_t);
        DenseIteratorColumns(const DenseIteratorColumns &);
        ~DenseIteratorColumns();
        IteratorBaseClass &operator++() override;
        IteratorBaseClass &operator++(int) override;
        bool operator==(const IteratorBaseClass &secIterator) const override;
        bool operator!=(const IteratorBaseClass &secIterator) const override;
        const float &operator*() const override;
        const float *operator->() const override;
        IteratorBaseClass *copy() const override;
    };
    class Proxy {
        friend class IterableDenseMatrix;

    private:
        IterableDenseMatrix &parent;
        size_t row;
        Proxy(IterableDenseMatrix &, size_t);

    public:
        float &operator[](size_t);
    };

public:
    IterableDenseMatrix(size_t);
    IterableDenseMatrix(const IterableDenseMatrix &);
    ~IterableDenseMatrix();
    IterableDenseMatrix &operator=(const IterableDenseMatrix &);
    Proxy operator[](size_t);
    Iterator iterateRows(size_t) const;
    Iterator iterateColumns(size_t) const;
    Iterator lastInRow() const;
    Iterator lastInColumn() const;
    size_t getSize() const;
};