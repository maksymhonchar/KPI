#ifndef __PROJ_SE6
#define __PROJ_SE6

// a special number that we want to find. You can change it, whatever you want.
#define specialNumber 5

//This function fills an array with random numbers in range [0;100].
//@param int* arrBegin pointer to first element of array
//@param int* arrEnd pointer to last element of array
void initialize_array(int* arrBegin, int* arrEnd);

//This function looks for the first and last entry of number P.
//It returns index of the last entry of number P and refills a pointer *index1Ptr
//with value of index of first entry of number P.
//@param int* arrBegin pointer to first element of array
//@param int* arrEnd pointer to the last element of array
//@param int P a special number, that we are looking for
//@param int* index1Ptr index of first entry of number P
int findEntry(int* arrBegin, int* arrEnd, int P, int* index1Ptr);

//This function copies items from mas1 array to mas2 array in such way:
//it copies items, that are only in range [l;r]
//@param int mas1[] a source array
//@param int mas2[] a destination array
//@param int n Length of arrays. It is equal
//@param int l Left range 
//@param int r Right range
int copy(int mas1 [], int mas2 [], int n, int l, int r);

//This function multiplies values of index1 and index2, that we 
//get in findLastEntry function, and returns the result.
//@param int mas[] array, within we are searching index1 and index2 numbers
int multiplication(int mas []);

#endif