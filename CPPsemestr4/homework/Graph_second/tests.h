#include <cxxtest/TestSuite.h>
#include "dense.hpp"

class MyTest : public CxxTest::TestSuite
{
public:
    void testDenseMatrixIterator(void)
    {
        IterableDenseMatrix matrix1(3);
        Iterator it = matrix1.iterateColumns(0);
        matrix1[0][0] = 1;
        matrix1[0][1] = 2;
        matrix1[0][2] = 3;
        matrix1[1][0] = 4;
        matrix1[1][1] = 5;
        matrix1[1][2] = 6;
        matrix1[2][0] = 7;
        matrix1[2][1] = 8;
        matrix1[2][2] = 9;
        size_t i = 0;
        for (it = matrix1.iterateColumns(0); it != matrix1.lastInColumn(); ++it) {
            TS_ASSERT_DELTA(matrix1[i][0], *it,EPSILON);
            i++;
        }
        i = 0;
        Iterator it2 = matrix1.iterateRows(0);
        for (it = matrix1.iterateRows(0); it != matrix1.lastInRow(); ++it) {
            TS_ASSERT_DELTA(matrix1[0][i], *it,EPSILON);
            i++;
        }

    }
   
};