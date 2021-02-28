#include <cxxtest/TestSuite.h>
#include "matrix.hpp"
class MyTest : public CxxTest::TestSuite
{
public:
    //Tests getNumber and setNumber methods
    void testGetSetNumber(void)
    {
        SparceMatrix matrix1(2, 2);
        const SparceMatrix matrix2(2, 2);
        matrix1.setNumber(0, 0,     1.34);
        matrix1.setNumber(0, 1, 1023.566);
        matrix1.setNumber(1, 0,        4);
        matrix1.setNumber(1, 1,   123123);
        TS_ASSERT_DELTA(matrix1.getNumber(0, 0),     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(0, 1), 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(1, 0),        4, EPSILON);
        TS_ASSERT_DELTA(matrix1.getNumber(1, 1),   123123, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(0, 0),        0, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(1, 0),        0, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(0, 1),        0, EPSILON);
        TS_ASSERT_DELTA(matrix2.getNumber(1, 1),        0, EPSILON);
    }
    //Tests getRowsSize and getColumnsSize methods
    void testGetRowsColumnsSize(void) 
    {
        SparceMatrix matrix1(2, 10);
        const SparceMatrix matrix2(3, 6);
        TS_ASSERT_EQUALS(matrix1.getRowsSize(),     2);
        TS_ASSERT_EQUALS(matrix1.getColumnsSize(), 10);
        TS_ASSERT_EQUALS(matrix2.getRowsSize(),     3);
        TS_ASSERT_EQUALS(matrix2.getColumnsSize(),  6);
    }

    void testMatrixEquel(void)
    {
        SparceMatrix matrix1(2, 2);
        SparceMatrix matrix2(2, 2);
        const SparceMatrix matrix3(2, 2);
        const SparceMatrix matrix4(2, 2);
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
        SparceMatrix matrix1(2, 2);
        SparceMatrix matrix2(2, 2);
        const SparceMatrix matrix3(2, 2);
        const SparceMatrix matrix4(2, 2);

        matrix1.setNumber(0, 0,   1.34);
        matrix1.setNumber(0, 1, 1023.5);
        matrix1.setNumber(1, 0,      4);
        matrix1.setNumber(1, 1, 123123);
        matrix2.setNumber(0, 0,   1.34);
        matrix2.setNumber(0, 1, 1023.5);
        matrix2.setNumber(1, 0,      4);
        matrix2.setNumber(1, 1, 123123);

        SparceMatrix sum1 = matrix1 + matrix2;
        SparceMatrix sum2 = matrix2 + matrix3;
        SparceMatrix sum3 = matrix3 + matrix4;

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
        SparceMatrix matrix1(2, 3);
        SparceMatrix matrix2(3, 2);
        const SparceMatrix matrix3(2, 3);
        const SparceMatrix matrix4(3, 2);

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

        SparceMatrix mult1 = matrix1 * matrix2;
        SparceMatrix mult2 = matrix2 * matrix3;
        SparceMatrix mult3 = matrix3 * matrix4;

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
        SparceMatrix matrix1(2, 2);
        const SparceMatrix matrix2(2, 2);
        matrix1[0][0] =     1.34;
        matrix1[0][1] = 1023.566;
        matrix1[1][0] =        4;    
        matrix1[1][1] =   123123;
        TS_ASSERT_DELTA(matrix1[0][0],     1.34, EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 1023.566, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0],        4, EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1],   123123, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0],        0, EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1],        0, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0],        0, EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1],        0, EPSILON);
    }

    void testPointer(void)
    {
        SparceMatrix matrix1(2, 2);
        const SparceMatrix matrix2(2, 2);
        **matrix1                =     1.34;
        *(*matrix1 + 1)          = 1023.566;
        **(matrix1 + 1)          =        4;    
        *(*(matrix1 + 1) + 1)    =   123123;
        TS_ASSERT_DELTA(**matrix1            ,     1.34, EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1)      , 1023.566, EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1)      ,        4, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1),   123123, EPSILON);
        TS_ASSERT_DELTA(**matrix2            ,        0, EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1)      ,        0, EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1)      ,        0, EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1),        0, EPSILON);
    }
};