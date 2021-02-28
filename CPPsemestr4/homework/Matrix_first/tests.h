#include <cxxtest/TestSuite.h>
#include "matrix.hpp"
class MyTest : public CxxTest::TestSuite
{
public:
    //Tests getNumber and setNumber methods
    void testGetSetNumber(void)
    {
        SparseMatrix matrix1(2, 2);
        matrix1.setNumber(0, 0,     1.34);
        matrix1.setNumber(0, 1, 1023.566);
        matrix1.setNumber(1, 0,        4);
        matrix1.setNumber(1, 1,   123123);
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1.getNumber(0, 0),     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(0, 1), 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(1, 0),        4, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(1, 1),   123123, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(0, 0),     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(0, 1), 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(1, 0),        4, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(1, 1),   123123, EPSILON);
    }
    //Tests getRowsSize and getColumnsSize methods
    void testGetRowsColumnsSize(void) 
    {
        SparseMatrix matrix1(2, 10);
        const SparseMatrix matrix2(3, 6);
        TS_ASSERT_EQUALS(matrix1.getRowsSize(),     2);
        TS_ASSERT_EQUALS(matrix1.getColumnsSize(), 10);
        TS_ASSERT_EQUALS(matrix2.getRowsSize(),     3);
        TS_ASSERT_EQUALS(matrix2.getColumnsSize(),  6);
    }

    void testMatrixEquel(void)
    {
        SparseMatrix matrix1(2, 2);
        SparseMatrix matrix2(2, 2);
        const SparseMatrix matrix3(2, 2);
        const SparseMatrix matrix4(2, 2);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 == matrix3);
        TS_ASSERT(matrix3 == matrix4);
        matrix1.setNumber(0, 0,     1.34);
        matrix1.setNumber(0, 1, 1023.566);
        matrix1.setNumber(1, 0,        4);
        matrix1.setNumber(1, 1,   123123);
        matrix2.setNumber(0, 0,     1.34);
        matrix2.setNumber(0, 1, 1023.566);
        matrix2.setNumber(1, 0,        4);
        matrix2.setNumber(1, 1,   123123);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 != matrix3);
    }

    void testAssigmentPlus(void)
    {
        SparseMatrix matrix1(2, 2);
        SparseMatrix matrix2(2, 2);
        const SparseMatrix matrix3(2, 2);
        const SparseMatrix matrix4(2, 2);

        matrix1.setNumber(0, 0,   1.34);
        matrix1.setNumber(0, 1, 1023.5);
        matrix1.setNumber(1, 0,      4);
        matrix1.setNumber(1, 1, 123123);
        matrix2.setNumber(0, 0,   1.34);
        matrix2.setNumber(0, 1, 1023.5);
        matrix2.setNumber(1, 0,      4);
        matrix2.setNumber(1, 1, 123123);

        SparseMatrix sum1 = matrix1 + matrix2;
        SparseMatrix sum2 = matrix2 + matrix3;
        SparseMatrix sum3 = matrix3 + matrix4;

        TS_ASSERT_DELTA(sum1.getNumber(0, 0),   2.68, EPSILON);
        TS_ASSERT_DELTA(sum1.getNumber(0, 1),   2047, EPSILON);
        TS_ASSERT_DELTA(sum1.getNumber(1, 0),      8, EPSILON);
        TS_ASSERT_DELTA(sum1.getNumber(1, 1), 246246, EPSILON);
        TS_ASSERT_DELTA(sum2.getNumber(0, 0),   1.34, EPSILON);
        TS_ASSERT_DELTA(sum2.getNumber(0, 1), 1023.5, EPSILON);
        TS_ASSERT_DELTA(sum2.getNumber(1, 0),      4, EPSILON);
        TS_ASSERT_DELTA(sum2.getNumber(1, 1), 123123, EPSILON);
        TS_ASSERT_DELTA(sum3.getNumber(0, 0),      0, EPSILON);
        TS_ASSERT_DELTA(sum3.getNumber(0, 1),      0, EPSILON);
        TS_ASSERT_DELTA(sum3.getNumber(1, 0),      0, EPSILON);
        TS_ASSERT_DELTA(sum3.getNumber(1, 1),      0, EPSILON);

    }

    void testMultiplication(void)
    {
        SparseMatrix matrix1(2, 3);
        SparseMatrix matrix2(3, 2);
        const SparseMatrix matrix3(2, 3);
        const SparseMatrix matrix4(3, 2);

        matrix1.setNumber(0, 0,   2);
        matrix1.setNumber(0, 1,   3);
        matrix1.setNumber(0, 2,   4);
        matrix1.setNumber(1, 0,   5);
        matrix1.setNumber(1, 1,   4);
        matrix1.setNumber(1, 2,   5);
        matrix2.setNumber(0, 0,   1);
        matrix2.setNumber(0, 1,   2);
        matrix2.setNumber(1, 0, 1.5);
        matrix2.setNumber(1, 1,   3);
        matrix2.setNumber(2, 0,   1);
        matrix2.setNumber(2, 1,   1);

        SparseMatrix mult1 = matrix1 * matrix2;
        SparseMatrix mult2 = matrix2 * matrix3;
        SparseMatrix mult3 = matrix3 * matrix4;

        TS_ASSERT_DELTA(mult1.getNumber(0, 0), 10.5, EPSILON);
        TS_ASSERT_DELTA(mult1.getNumber(0, 1),   17, EPSILON);
        TS_ASSERT_DELTA(mult1.getNumber(1, 0),   16, EPSILON);
        TS_ASSERT_DELTA(mult1.getNumber(1, 1),   27, EPSILON);
        TS_ASSERT_DELTA(mult2.getNumber(0, 0),    0, EPSILON);
        TS_ASSERT_DELTA(mult2.getNumber(0, 1),    0, EPSILON);
        TS_ASSERT_DELTA(mult2.getNumber(1, 0),    0, EPSILON);
        TS_ASSERT_DELTA(mult2.getNumber(1, 1),    0, EPSILON);
        TS_ASSERT_DELTA(mult3.getNumber(0, 0),    0, EPSILON);
        TS_ASSERT_DELTA(mult3.getNumber(0, 1),    0, EPSILON);
        TS_ASSERT_DELTA(mult3.getNumber(1, 0),    0, EPSILON);
        TS_ASSERT_DELTA(mult3.getNumber(1, 1),    0, EPSILON);
    }

    void testIndexOperator(void)
    {
        SparseMatrix matrix1(2, 2);
        matrix1[0][0] =     1.34;
        matrix1[0][1] = 1023.566;
        matrix1[1][0] =        4;    
        matrix1[1][1] =   123123;
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0],     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0],        4, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1],   123123, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0],     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0],        4, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1],   123123, EPSILON);
    }

    void testPointer(void)
    {
        SparseMatrix matrix1(2, 2);
        **matrix1                =     1.34;
        *(*matrix1 + 1)          = 1023.566;
        **(matrix1 + 1)          =        4;    
        *(*(matrix1 + 1) + 1)    =   123123;
        const SparseMatrix matrix2 = matrix1; 
        TS_ASSERT_DELTA(**matrix1            ,     1.34, EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1)      , 1023.566, EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1)      ,        4, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1),   123123, EPSILON);
        TS_ASSERT_DELTA(**matrix2            ,     1.34, EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1)      , 1023.566, EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1)      ,        4, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1),   123123, EPSILON);
    }

    void testZeroObjects(void)
    {
        SparseMatrix matrix1(2, 2);
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0], 0, EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 0, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0], 0, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1], 0, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0], 0, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 0, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0], 0, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1], 0, EPSILON);
        TS_ASSERT_DELTA(**matrix1            , 0, EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1)      , 0, EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1)      , 0, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1), 0, EPSILON);
        TS_ASSERT_DELTA(**matrix2            , 0, EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1)      , 0, EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1)      , 0, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1), 0, EPSILON);
    }
};