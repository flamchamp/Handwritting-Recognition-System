//========================================================================
// sort-int-directed-test.cc
//========================================================================

#include "ece2400-stdlib.h"
#include "sort-int.h"
#include <cstring>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------
// Simple test case for sort_int.

void test_case_1_simple()
{
  std::printf( "\n%s\n", __func__ );

  int arr[] = {11, 7};
  sort_int( arr, 2 );
  ECE2400_CHECK_INT_EQ( arr[0], 7 );
  ECE2400_CHECK_INT_EQ( arr[1], 11 );
}

//------------------------------------------------------------------------
// test_case_2_empty
//------------------------------------------------------------------------
// A simple test case that tests sorting an empty array.

void test_case_2_empty()
{
  std::printf( "\n%s\n", __func__ );

  int* arr     = NULL;
  int* arr_ref = NULL;
  sort_int( arr, 0 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, 0 ), 0 );

  int* arr2     = NULL;
  int* arr2_ref = NULL;
  sort_int( arr2, 0 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, 0 ), 0 );
}

//------------------------------------------------------------------------
// test_case_3_one_element
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_3_one_element()
{
  std::printf( "\n%s\n", __func__ );

  int arr[]     = {3};
  int arr_ref[] = {3};
  sort_int( arr, 1 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( arr ) ), 0 );

  int arr2[]     = {5};
  int arr2_ref[] = {5};
  sort_int( arr2, 1 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, sizeof( arr2 ) ), 0 );

  int arr3[]     = {4};
  int arr3_ref[] = {4};
  sort_int( arr3, 1 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr3, arr3_ref, sizeof( arr3 ) ), 0 );
}

//------------------------------------------------------------------------
// test_case_4_almost_sorted
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_4_almost_sorted()
{
  std::printf( "\n%s\n", __func__ );

  int arr[]     = {4, 3, 5, 6, 10};
  int arr_ref[] = {3, 4, 5, 6, 10};
  sort_int( arr, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( arr ) ), 0 );

  int arr2[]     = {0, 2, 9, 5, 13};
  int arr2_ref[] = {0, 2, 5, 9, 13};
  sort_int( arr2, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, sizeof( arr2 ) ), 0 );
}

//------------------------------------------------------------------------
// test_case_5_sorted
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_5_sorted()
{
  std::printf( "\n%s\n", __func__ );

  int arr[]     = {3, 4, 5, 6, 10};
  int arr_ref[] = {3, 4, 5, 6, 10};
  sort_int( arr, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( arr ) ), 0 );

  int arr2[]     = {0, 2, 5, 9, 13};
  int arr2_ref[] = {0, 2, 5, 9, 13};
  sort_int( arr2, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, sizeof( arr2 ) ), 0 );

  int arr3[]     = {2, 32, 140, 500, 1000};
  int arr3_ref[] = {2, 32, 140, 500, 1000};
  sort_int( arr3, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr3, arr3_ref, sizeof( arr3 ) ), 0 );
}

//------------------------------------------------------------------------
// test_case_6_reversed
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_6_reversed()
{
  std::printf( "\n%s\n", __func__ );

  int arr[]     = {10, 6, 5, 4, 3};
  int arr_ref[] = {3, 4, 5, 6, 10};
  sort_int( arr, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( arr ) ), 0 );

  int arr2[]     = {13, 9, 5, 2, 1};
  int arr2_ref[] = {1, 2, 5, 9, 13};
  sort_int( arr2, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, sizeof( arr2 ) ), 0 );

  int arr3[]     = {1000, 500, 140, 32, 1};
  int arr3_ref[] = {1, 32, 140, 500, 1000};
  sort_int( arr3, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr3, arr3_ref, sizeof( arr3 ) ), 0 );
}

//------------------------------------------------------------------------
// test_case_7_few_unique
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_7_few_unique()
{
  std::printf( "\n%s\n", __func__ );

  int arr[]     = {3, 4, 4, 3, 4};
  int arr_ref[] = {3, 3, 4, 4, 4};
  sort_int( arr, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( arr ) ), 0 );

  int arr2[]     = {25, 5, 5, 5, 25};
  int arr2_ref[] = {5, 5, 5, 25, 25};
  sort_int( arr2, 5 );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr2, arr2_ref, sizeof( arr2 ) ), 0 );
}

//------------------------------------------------------------------------
// test_case_8_large_reversed
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_8_large_reversed()
{
  std::printf( "\n%s\n", __func__ );

  int  size    = 10000;
  int* arr     = new int[size];
  int* arr_ref = new int[size];

  for ( int i = 0; i < size; i++ ) {
    arr[i]     = size - i;
    arr_ref[i] = i + 1;
  }

  sort_int( arr, size );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( int ) * size ), 0 );

  delete[] arr;
  delete[] arr_ref;
}

void test_case_9_less_simple()
{
  printf( "\n%s\n", __func__ );
  int arr[] = {24, 47, 5, 32, 586, 23, 15, 5, 59, 7};
  sort_int( arr, 10 );
  ECE2400_CHECK_INT_EQ( arr[0], 5 );
  ECE2400_CHECK_INT_EQ( arr[1], 5 );
  ECE2400_CHECK_INT_EQ( arr[2], 7 );
  ECE2400_CHECK_INT_EQ( arr[3], 15 );
  ECE2400_CHECK_INT_EQ( arr[4], 23 );
  ECE2400_CHECK_INT_EQ( arr[5], 24 );
  ECE2400_CHECK_INT_EQ( arr[6], 32 );
  ECE2400_CHECK_INT_EQ( arr[7], 47 );
  ECE2400_CHECK_INT_EQ( arr[8], 59 );
  ECE2400_CHECK_INT_EQ( arr[9], 586 );
}

void test_case_10_empty()
{
  printf( "\n%s\n", __func__ );
  int* arr = NULL;
  sort_int( arr, 0 );
  ECE2400_CHECK_TRUE( arr == NULL );
}

void test_case_11_one_value()
{
  printf( "\n%s\n", __func__ );
  int arr[] = {11};
  sort_int( arr, 1 );
  ECE2400_CHECK_INT_EQ( arr[0], 11 );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_simple();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_empty();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_one_element();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_almost_sorted();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_sorted();
  if ( ( __n == 0 ) || ( __n == 6  ) ) test_case_6_reversed();
  if ( ( __n == 0 ) || ( __n == 7  ) ) test_case_7_few_unique();
  if ( ( __n == 0 ) || ( __n == 8  ) ) test_case_8_large_reversed();
  if ( ( __n <= 0 ) || ( __n == 9 ) ) test_case_9_less_simple();
  if ( ( __n <= 0 ) || ( __n == 10 ) ) test_case_10_empty();
  if ( ( __n <= 0 ) || ( __n == 11 ) ) test_case_11_one_value();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  return __failed;
}
// clang-format on
