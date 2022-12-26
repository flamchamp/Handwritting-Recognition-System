//========================================================================
// sort-int-random-test.cc
//========================================================================

#include "ece2400-stdlib.h"
#include "sort-int.h"
#include <cstdlib>
#include <cstring>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------

void test_case_1_simple()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0x8BadBeef );

  const int size = 1000;
  int*      a    = new int[size];
  int*      b    = new int[size];

  for ( int i = 0; i < size; i++ ) {
    int random_value = rand() % 10000;
    a[i]             = random_value;
    b[i]             = random_value;
  }

  sort_int( a, size );
  ece2400::sort( b, size );

  for ( int i = 0; i < size; i++ )
    ECE2400_CHECK_INT_EQ( a[i], b[i] );

  delete[] a;
  delete[] b;
}

//------------------------------------------------------------------------
// test_case_2_large
//------------------------------------------------------------------------

void test_case_2_large()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0xfaceb00c );

  int  size    = 10000;
  int* arr     = new int[size];
  int* arr_ref = new int[size];

  for ( int i = 0; i < size; i++ ) {
    int num = rand() % 100000;  // Generate random number

    arr[i]     = num;
    arr_ref[i] = num;
  }

  // Use the standard library qsort to sort the reference array

  ece2400::sort( arr_ref, size );

  sort_int( arr, size );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( int ) * size ), 0 );

  delete[] arr;
  delete[] arr_ref;
}

//------------------------------------------------------------------------
// test_case_3_few_unique
//------------------------------------------------------------------------

void test_case_3_few_unique()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0xbadc0de );

  int  size    = 10000;
  int* arr     = new int[size];
  int* arr_ref = new int[size];

  for ( int i = 0; i < size; i++ ) {
    int num = rand() % 10;  // Generate random number [0, 9]

    arr[i]     = num;
    arr_ref[i] = num;
  }

  // Use the standard library qsort to sort the reference array

  ece2400::sort( arr_ref, size );

  sort_int( arr, size );
  ECE2400_CHECK_INT_EQ( std::memcmp( arr, arr_ref, sizeof( int ) * size ), 0 );

  delete[] arr;
  delete[] arr_ref;
}

void test_case_4_simple()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8BadBeef );
  int size = 10;
  int arr[10];
  int arr2[10];
  for ( int i = 0; i < size; i++ ) {
    int x   = rand() % 100;
    arr[i]  = x;
    arr2[i] = x;
  }
  sort_int( arr, size );
  ece2400::sort( arr2, size );
  for ( int i = 0; i < size; i++ ) {
    ECE2400_CHECK_INT_EQ( arr[i], arr2[i] );
  }
}

void test_case_5_large()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8BadBeef );
  int size = 1000;
  int arr[1000];
  int arr2[1000];
  for ( int i = 0; i < size; i++ ) {
    int x   = rand() % 100;
    arr[i]  = x;
    arr2[i] = x;
  }
  sort_int( arr, size );
  ece2400::sort( arr2, size );
  for ( int i = 0; i < size; i++ ) {
    ECE2400_CHECK_INT_EQ( arr[i], arr2[i] );
  }
}

void test_case_6_huge()
{
  printf( "\n%s\n", __func__ );
  srand( 0x8BadBeef );
  int size = 10000;
  int arr[10000];
  int arr2[10000];
  for ( int i = 0; i < size; i++ ) {
    int x   = rand() % 100;
    arr[i]  = x;
    arr2[i] = x;
  }
  sort_int( arr, size );
  ece2400::sort( arr2, size );
  for ( int i = 0; i < size; i++ ) {
    ECE2400_CHECK_INT_EQ( arr[i], arr2[i] );
  }
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
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_large();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_few_unique();
  if ( ( __n <= 0 ) || ( __n == 4 ) ) test_case_4_simple();
  if ( ( __n <= 0 ) || ( __n == 5 ) ) test_case_5_large();
  if ( ( __n <= 0 ) || ( __n == 6 ) ) test_case_6_huge();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  return __failed;
}
// clang-format on
