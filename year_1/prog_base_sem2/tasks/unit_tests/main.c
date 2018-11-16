#include <stdlib.h> //cmocka unit-tests
#include <stddef.h> //cmocka unit-tests
#include <stdarg.h> //cmocka unit-tests
#include <setjmp.h> //cmocka unit-tests

#include <cmocka.h> //cmocka unit-tests

#include "set.h" //main logic functions & defines

//Test for Set_new function.
static void new_void_MemoryAllocated(void ** state)
{
    Set_T * testSet = Set_new(TESTSIZE_EMPTY);
    assert_non_null(testSet);
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_getSize function.
static void getSize_oneNumber_isLengthNotZero(void ** state)
{
    Set_T * testSet = Set_new(TESTSIZE_FILLED);
    assert_int_not_equal(Set_getSize(testSet), 0);
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_getValueAt & Set_setValueAt function.
static void getValueAt_fiveNumbersAndIndex_isValueOnIndexCorrect(void ** state)
{
    int testIndex = 3, testValue;
    Set_T * testSet = Set_new(TESTSIZE_FILLED);
    //Fill the set and assign to testValue element on the testIndex
    for(int i = 0; i < Set_getSize(testSet); i++)
    {
        Set_setValueAt(testSet, i, i);
        if(i == testIndex)
            testValue = i;
    }
    assert_in_range(Set_getValueAt(testSet, testIndex), 0, INT_MAX); //The set consists of unsigned int`s
    assert_int_equal(Set_getValueAt(testSet, testIndex), testValue);
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_fill function.
static void fill_void_isSetFilledWithUnsigned(void ** state)
{
    Set_T * testSet = Set_new(TESTSIZE_FILLED);
    Set_fill(testSet);
    for(int i = 0; i < Set_getSize(testSet); i++)
    {
        assert_in_range(Set_getValueAt(testSet, i), 0, INT_MAX);
    }
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_removeValueAt function.
static void removeValueAt_fiveNumbers_isValueRemoved(void ** state)
{
    Set_T * testSet = Set_new(TESTSIZE_FILLED);
    Set_fill(testSet);
    Set_removeValueAt(testSet, 0);
    assert_int_equal(Set_getSize(testSet), TESTSIZE_FILLED - 1);
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_removeValueAt function.
static void removeValueAt_fiveNumbers_isReturnedValueCorrect(void ** state)
{
    Set_T * testSet = Set_new(TESTSIZE_FILLED);
    Set_fill(testSet);
    int originValue = Set_getValueAt(testSet, 0);
    int testValue = Set_removeValueAt(testSet, 0);
    assert_int_equal(originValue, testValue);
    //Free allocated memory.
    Set_delete(testSet);
}
//Test for Set_union function.
static void union_eightNumbersTwoArrays_isUnionCorrect(void ** state)
{
    int correctUnion[] = {0,1,2,3,4,5,6,7};
    Set_T * firstTestSet = Set_new(TESTSIZE_FILLED_4);
    Set_T * secondTestSet = Set_new(TESTSIZE_FILLED_4);
    //fill the firstTestSet with '0-3'
    for(int i = 0, j = 0; i < TESTSIZE_FILLED_4; i++, j++)
        Set_setValueAt(firstTestSet, i, j);
    //fill the secondTestSet with '4-7'
    for(int i = 0, j = 4; i < TESTSIZE_FILLED_4; i++, j++)
        Set_setValueAt(secondTestSet, i, j);
    //calculate the union from the first and the second set
    Set_T * unionSet = Set_union(firstTestSet, secondTestSet);
    //Compare the correctUnion and the unionSet
    for(int i = 0; i < Set_getSize(unionSet); i++)
        assert_int_equal(Set_getValueAt(unionSet, i), correctUnion[i]);
    //Free allocated memory
    Set_delete(firstTestSet);
    Set_delete(secondTestSet);
    Set_delete(unionSet);
}
//Test for Set_intersection function.
static void intersection_eightNumbersTwoArrays_isIntersectionCorrect(void ** state)
{
    int correctIntersection[] = {4,5};
    Set_T * firstTestSet = Set_new(TESTSIZE_FILLED_4);
    Set_T * secondTestSet = Set_new(TESTSIZE_FILLED_4);
    //fill the firstTestSet with '2-5'
    for(int i = 0, j = 2; i < Set_getSize(firstTestSet); i++, j++)
        Set_setValueAt(firstTestSet, i, j);
    //Fill the firstTestSet with '4-8'
    for(int i = 0, j = 4; i < Set_getSize(secondTestSet); i++, j++)
        Set_setValueAt(secondTestSet, i, j);
    //Calculate the intersection set.
    Set_T * intersectionSet = Set_intersection(firstTestSet, secondTestSet);
    //Compare correct answer with calculated intersectionSet
    for(int i = 0; i < Set_getSize(intersectionSet); i++)
        assert_int_equal(Set_getValueAt(intersectionSet, i), correctIntersection[i]);
    //Free allocated memory
    Set_delete(intersectionSet);
    Set_delete(firstTestSet);
    Set_delete(secondTestSet);
}
//Test for Set_difference function.
static void difference_eightNumbersTwoArrays_isDifferenceCorrect(void ** state)
{
    int correctDifference[] = {0,1,2};
    Set_T * firstTestSet = Set_new(TESTSIZE_FILLED_4);
    Set_T * secondTestSet = Set_new(TESTSIZE_FILLED_4);
    //fill the firstTestSet with '0-3'
    for(int i = 0, j = 0; i < Set_getSize(firstTestSet); i++, j++)
        Set_setValueAt(firstTestSet, i, j);
    //Fill the firstTestSet with '3-6'
    for(int i = 0, j = 3; i < Set_getSize(secondTestSet); i++, j++)
        Set_setValueAt(secondTestSet, i, j);
    //Calculate the difference set.
    Set_T * differenceSet = Set_difference(firstTestSet, secondTestSet);
    //Compare correct answer with calculated differenceSet
    for(int i = 0; i < Set_getSize(differenceSet); i++)
        assert_int_equal(Set_getValueAt(differenceSet, i), correctDifference[i]);
    //Free allocated memory
    Set_delete(differenceSet);
    Set_delete(firstTestSet);
    Set_delete(secondTestSet);
}

int main()
{
    //Set console default size.
    system(CONSOLE_SIZE);
    //Execute unit-tests.
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_MemoryAllocated),
        cmocka_unit_test(getSize_oneNumber_isLengthNotZero),
        cmocka_unit_test(getValueAt_fiveNumbersAndIndex_isValueOnIndexCorrect),
        cmocka_unit_test(fill_void_isSetFilledWithUnsigned),
        cmocka_unit_test(removeValueAt_fiveNumbers_isValueRemoved),
        cmocka_unit_test(removeValueAt_fiveNumbers_isReturnedValueCorrect),
        cmocka_unit_test(union_eightNumbersTwoArrays_isUnionCorrect),
        cmocka_unit_test(intersection_eightNumbersTwoArrays_isIntersectionCorrect),
        cmocka_unit_test(difference_eightNumbersTwoArrays_isDifferenceCorrect),
    };
    return (cmocka_run_group_tests(tests, NULL, NULL));
}
