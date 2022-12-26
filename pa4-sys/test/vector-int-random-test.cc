//========================================================================
// vector-int-random-test.cc
//========================================================================
// This file contains random tests for VectorInt-related functions.

#include "VectorInt.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// test_case_1_push_back_random
//------------------------------------------------------------------------
// A random test case that tests push back.

void test_case_1_push_back_random()
{
  std::printf( "\n%s\n", __func__ );

  const unsigned int iterations = 10;

  for ( unsigned int i = 0; i < iterations; i++ ) {
    VectorInt vec;

    const unsigned int size = rand() % 1000;
    int*               data = new int[size];

    for ( unsigned int j = 0; j < size; j++ ) {
      int random = rand();
      vec.push_back( random );
      data[j] = random;
    }

    ECE2400_CHECK_INT_EQ( vec.size(), size );

    // Check vector against array that has same elements
    //  at the same index
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.at( j ), data[j] );
      ECE2400_CHECK_INT_EQ( vec[j], data[j] );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_2_copy_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_2_copy_random()
{
  std::printf( "\n%s\n", __func__ );

  const int iterations = 10;

  for ( int i = 0; i < iterations; i++ ) {
    VectorInt vec;
    VectorInt vec0;

    const int size     = rand() % 1000;
    const int add_size = rand() % 1000;

    int* data = new int[size];
    // additional data to add onto vec0 and vec1
    int* data0 = new int[add_size];

    for ( int j = 0; j < size; j++ ) {
      int random = rand();
      vec.push_back( random );
      data[j] = random;
    }

    // Assignment operator
    vec0 = vec;

    // Copy constructor
    VectorInt vec1( vec0 );

    // Add more elements to vec0 and vec1
    for ( int j = 0; j < add_size; j++ ) {
      int random = rand();
      vec0.push_back( random );
      vec1.push_back( random );
      data0[j] = random;
    }

    ECE2400_CHECK_TRUE( vec.size() == size );
    ECE2400_CHECK_TRUE( vec0.size() == size + add_size );
    ECE2400_CHECK_TRUE( vec1.size() == size + add_size );

    // Check the copied elements
    for ( int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.at( j ), data[j] );
      ECE2400_CHECK_INT_EQ( vec[j], data[j] );
      ECE2400_CHECK_INT_EQ( vec0.at( j ), data[j] );
      ECE2400_CHECK_INT_EQ( vec0[j], data[j] );
      ECE2400_CHECK_INT_EQ( vec1.at( j ), data[j] );
      ECE2400_CHECK_INT_EQ( vec1[j], data[j] );
    }

    // Check additional elements for vec0 and vec1
    for ( int j = 0; j < add_size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec0.at( size + j ), data0[j] );
      ECE2400_CHECK_INT_EQ( vec0[size + j], data0[j] );
      ECE2400_CHECK_INT_EQ( vec1.at( size + j ), data0[j] );
      ECE2400_CHECK_INT_EQ( vec1[size + j], data0[j] );
    }

    delete[] data;
    delete[] data0;
  }
}

//------------------------------------------------------------------------
// test_case_3_array_construct_random
//------------------------------------------------------------------------
// A random test case that tests construct VectorInt from an array.

void test_case_3_array_construct_random()
{
  std::printf( "\n%s\n", __func__ );

  const unsigned int iterations = 10;

  for ( unsigned int i = 0; i < iterations; i++ ) {
    const unsigned int size = rand() % 1000;

    int* data = new int[size];

    for ( unsigned int j = 0; j < size; j++ ) {
      data[j] = j;
    }

    // Construct the vector from an array
    VectorInt vec( data, size );

    // Modify the array to test deepcopy
    for ( unsigned int j = 0; j < size; j++ ) {
      data[j] = size + 1;
    }

    // Check that the value inside the vector is not modified
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.at( j ), j );
      ECE2400_CHECK_INT_EQ( vec[j], j );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_4_find_closest_linear_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_4_find_closest_linear_random()
{
  std::printf( "\n%s\n", __func__ );

  const unsigned int iterations = 10;

  for ( unsigned int i = 0; i < iterations; i++ ) {
    const unsigned int size = rand() % 1000;

    int* data   = new int[size];
    int  offset = rand() % 10 + 10;

    for ( unsigned int j = 0; j < size; j++ ) {
      data[j] = j * offset;
    }

    VectorInt vec( data, size );

    // Check the closest value for the multiples of offset plus one
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.find_closest_linear( j * offset + 1 ),
                            j * offset );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_5_find_closest_binary_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_5_find_closest_binary_random()
{
  std::printf( "\n%s\n", __func__ );

  const unsigned int iterations = 10;

  for ( unsigned int i = 0; i < iterations; i++ ) {
    const unsigned int size = rand() % 1000;

    int* data   = new int[size];
    int  offset = rand() % 10 + 10;

    for ( unsigned int j = 0; j < size; j++ ) {
      data[j] = j * offset;
    }

    VectorInt vec( data, size );
    vec.sort();

    // Check the closest value for the multiples of offset plus one
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.find_closest_binary( j * offset + 1, 4 ),
                            j * offset );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_6_general_random
//------------------------------------------------------------------------

void test_case_6_general_random()
{
  printf( "\n%s\n", __func__ );

  const unsigned int iterations = 10;

  for ( unsigned int i = 0; i < iterations; i++ ) {
    const unsigned int size = rand() % 1000;
    int*               data = new int[size];
    VectorInt          vec;

    for ( unsigned int j = 0; j < size; j++ ) {
      data[j] = j;
      vec.push_back( j );

      ECE2400_CHECK_INT_EQ( vec.size(), j + 1 );
    }

    // Test at and contains, expecting successful
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_TRUE( vec.contains( j ) );
      ECE2400_CHECK_INT_EQ( vec.at( j ), j );
    }

    // Test contains, expecting not successful
    for ( unsigned int j = size; j < size * 2; j++ ) {
      ECE2400_CHECK_FALSE( vec.contains( j ) );
    }

    // Test find_closest_linear
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.find_closest_linear( j ), j );
    }

    // Test find_closets for values beyond 0 to size
    ECE2400_CHECK_INT_EQ( vec.find_closest_linear( size ), size - 1 );
    ECE2400_CHECK_INT_EQ( vec.find_closest_linear( -1 ), 0 );

    vec.sort();

    // Test find_closest_binary
    for ( unsigned int j = 0; j < size; j++ ) {
      ECE2400_CHECK_INT_EQ( vec.find_closest_binary( j, 4 ), j );
    }
    // Test find_closets for values beyond 0 to size
    ECE2400_CHECK_INT_EQ( vec.find_closest_binary( size, 4 ), size - 1 );
    ECE2400_CHECK_INT_EQ( vec.find_closest_binary( -1, 4 ), 0 );

    delete[] data;
  }
}

//'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
// Implement more test cases here.
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1 ) ) test_case_1_push_back_random();
  if ( ( __n == 0 ) || ( __n == 2 ) ) test_case_2_copy_random();
  if ( ( __n == 0 ) || ( __n == 3 ) ) test_case_3_array_construct_random();
  if ( ( __n == 0 ) || ( __n == 4 ) ) test_case_4_find_closest_linear_random();
  if ( ( __n == 0 ) || ( __n == 5 ) ) test_case_5_find_closest_binary_random();
  if ( ( __n == 0 ) || ( __n == 6 ) ) test_case_6_general_random();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return __failed;
}
// clang-format on
