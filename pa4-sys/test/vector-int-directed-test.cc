//========================================================================
// vector-int-directed-test.cc
//========================================================================
// This file contains directed tests for VectorInt-related functions.

#include "VectorInt.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// test_case_1_simple_push_back
//------------------------------------------------------------------------
// A simple test case that tests default constructor, push_back, and at.

void test_case_1_simple_push_back()
{
  std::printf( "\n%s\n", __func__ );

  // Use the default constructor
  VectorInt vec;

  // Check size of empty vector
  ECE2400_CHECK_INT_EQ( vec.size(), 0 );

  // Push back some values
  int data[] = {0xc01d, 0xdead, 0x2bad};
  for ( int v : data )
    vec.push_back( v );

  // Check value and size
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_INT_EQ( vec.at( i ), data[i] );

  ECE2400_CHECK_INT_EQ( vec.size(), 3 );
}

//------------------------------------------------------------------------
// test_case_2_at_out_of_bound
//------------------------------------------------------------------------
// Test that exception is properly thrown when at is out of bound.

void test_case_2_at_out_of_bound()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;

  // empty vector

  bool flag = false;
  try {
    vec.at( 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // push back some values

  vec.push_back( 0 );
  vec.push_back( 9 );

  // right at the boundary

  flag = false;
  try {
    vec.at( 2 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // beyond the boundary

  flag = false;
  try {
    vec.at( 5 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_3_construct
//------------------------------------------------------------------------
// A simple test case that tests non-default constructor.

void test_case_3_construct()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector from an array
  int       data[] = {0, 1, 2, 3, 4, 5, 6, 7};
  VectorInt vec    = VectorInt( data, 8 );

  // Modify the array to test deepcopy
  for ( int& v : data )
    v = 0xDeadFace;

  // Check that the value inside the vector is not modified
  for ( auto i = 0; i < 8; i++ )
    ECE2400_CHECK_INT_EQ( vec.at( i ), i );

  ECE2400_CHECK_INT_EQ( vec.size(), 8 );
}

//------------------------------------------------------------------------
// test_case_4_find_simple
//------------------------------------------------------------------------
// A simple test case that tests contains.

void test_case_4_find_simple()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector from array
  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );

  // Search for value, expecting success
  ECE2400_CHECK_TRUE( vec.contains( 1 ) );
  ECE2400_CHECK_TRUE( vec.contains( 9 ) );
  ECE2400_CHECK_TRUE( vec.contains( 5 ) );
  ECE2400_CHECK_TRUE( vec.contains( 0 ) );
  ECE2400_CHECK_TRUE( vec.contains( 4 ) );
  ECE2400_CHECK_TRUE( vec.contains( 2 ) );
  ECE2400_CHECK_TRUE( vec.contains( 3 ) );

  // Search for value, expecting failure
  ECE2400_CHECK_FALSE( vec.contains( 6 ) );
  ECE2400_CHECK_FALSE( vec.contains( 7 ) );
  ECE2400_CHECK_FALSE( vec.contains( 8 ) );
}

//------------------------------------------------------------------------
// test_case_5_find_empty
//------------------------------------------------------------------------
// A simple test case that tests contains for an empty vector.

void test_case_5_find_empty()
{
  std::printf( "\n%s\n", __func__ );

  // Construct an empty vector
  VectorInt vec;

  // Search for value, expecting failure
  for ( int i = 0; i < 10; i++ )
    ECE2400_CHECK_FALSE( vec.contains( i ) );
}

//------------------------------------------------------------------------
// test_case_6_find_closest_linear
//------------------------------------------------------------------------
// A simple test case that tests copy constructor and assignment operator.

void test_case_6_find_closest_linear()
{
  std::printf( "\n%s\n", __func__ );

  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );

  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 6 ), 5 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 9 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 8 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 11 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 7 ), 9 );
}

//------------------------------------------------------------------------
// test_case_7_find_closest_linear_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_7_find_closest_linear_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;

  // find_closest_linear on empty vector
  bool flag = false;
  try {
    vec.find_closest_linear( 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_8_find_closest_binary
//------------------------------------------------------------------------
// A simple test case that tests copy constructor and assignment operator.

void test_case_8_find_closest_binary()
{
  std::printf( "\n%s\n", __func__ );

  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );
  vec.sort();

  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 6, 4 ), 5 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 9, 4 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 3, 4 ), 3 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 4, 4 ), 4 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 6, 4 ), 5 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 8, 4 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 11, 4 ), 9 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 7, 4 ), 5 );
}

//------------------------------------------------------------------------
// test_case_9_find_closest_binary_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_9_find_closest_binary_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;
  vec.sort();

  // find_closest_linear on empty vector
  bool flag = false;
  try {
    vec.find_closest_binary( 0, 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_10_find_closest_binary_unsorted
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_10_find_closest_binary_unsorted()
{
  std::printf( "\n%s\n", __func__ );

  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );

  // find_closest_linear on empty vector
  bool flag = false;
  try {
    ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 6, 4 ), 5 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  vec.sort();
  flag = false;
  try {
    ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 6, 4 ), 5 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_FALSE( flag );

  vec.push_back( 7 );
  flag = false;
  try {
    ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 6, 4 ), 5 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_11_sort_simple
//------------------------------------------------------------------------
// A simple sort test.

void test_case_11_sort_simple()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector
  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );

  // Sort the vector and input array
  ece2400::sort( data, 8 );
  vec.sort();

  for ( int i = 0; i < 8; i++ )
    ECE2400_CHECK_INT_EQ( vec.at( i ), data[i] );
}

//------------------------------------------------------------------------
// test_case_12_subscript
//------------------------------------------------------------------------
// A simple test for the subscript operator.

void test_case_12_subscript()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector from array
  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 8 );

  // Check the value using subscript operator
  for ( int i = 0; i < 8; i++ )
    ECE2400_CHECK_INT_EQ( vec[i], data[i] );
}

//------------------------------------------------------------------------
// test_case_13_copy
//------------------------------------------------------------------------
// A simple test case that tests copy constructor.

void test_case_13_copy()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;

  int data[]  = {0xbeef, 0xcafe, 0xf00d, 0xface};
  int data0[] = {0xface, 0xbeef, 0xbeef, 0xc001};
  int data1[] = {0xcafe, 0xba11, 0xb00c, 0xc0de};

  // Push back to vec
  for ( int v : data )
    vec0.push_back( v );

  // Copy constructor
  VectorInt vec1( vec0 );

  // Push different values to vec0 and vec1
  for ( int v : data0 )
    vec0.push_back( v );

  for ( int v : data1 )
    vec1.push_back( v );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec0[i], data[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec1[i], data[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i + 4 ), data0[i] );
    ECE2400_CHECK_INT_EQ( vec0[i + 4], data0[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i + 4 ), data1[i] );
    ECE2400_CHECK_INT_EQ( vec1[i + 4], data1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_14_assignment_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a empty vector.

void test_case_14_assignment_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;
  VectorInt vec1;

  int data[]  = {0xBeef, 0xCafe, 0xF00d, 0xFace};
  int data0[] = {0xFace, 0xBeef, 0xBeef, 0xC001};
  int data1[] = {0xCafe, 0xBa11, 0xb00c, 0xC0de};

  // Push back to vec0
  for ( int v : data )
    vec0.push_back( v );

  // Assignment operator
  vec1 = vec0;

  // Push different values to vec0 and vec1
  for ( int v : data0 )
    vec0.push_back( v );

  for ( int v : data1 )
    vec1.push_back( v );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec0[i], data[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec1[i], data[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i + 4 ), data0[i] );
    ECE2400_CHECK_INT_EQ( vec0[i + 4], data0[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i + 4 ), data1[i] );
    ECE2400_CHECK_INT_EQ( vec1[i + 4], data1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_15_assignment_non_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a non-empty vector.

void test_case_15_assignment_non_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;
  VectorInt vec1;

  int data[]  = {0xbeef, 0xcafe, 0xf00d, 0xface};
  int data0[] = {0xface, 0xbeef, 0xbeef, 0xc001};
  int data1[] = {0xcafe, 0xba11, 0xb00c, 0xc0de};

  // Push back to vec0
  for ( int v : data )
    vec0.push_back( v );

  // Push back some values to vec1
  for ( int i = 0; i < 10; i++ )
    vec1.push_back( i );

  // Assignment operator
  vec1 = vec0;

  // Push different values to vec0 and vec1
  for ( int v : data0 )
    vec0.push_back( v );

  for ( int v : data1 )
    vec1.push_back( v );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec0[i], data[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i ), data[i] );
    ECE2400_CHECK_INT_EQ( vec1[i], data[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_INT_EQ( vec0.at( i + 4 ), data0[i] );
    ECE2400_CHECK_INT_EQ( vec0[i + 4], data0[i] );
    ECE2400_CHECK_INT_EQ( vec1.at( i + 4 ), data1[i] );
    ECE2400_CHECK_INT_EQ( vec1[i + 4], data1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_16_general
//------------------------------------------------------------------------
// A generic test case.

void test_case_16_general()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a new vector_int_t

  VectorInt vec;

  // Push data into the data structure

  for ( int i = 0; i < 5; i++ )
    vec.push_back( 100 + i );

  for ( int i = 5; i < 10; i++ )
    vec.push_back( 200 + i );

  for ( int i = 10; i < 20; i++ )
    vec.push_back( 300 + i );

  for ( int i = 20; i < 30; i++ )
    vec.push_back( 400 + i );

  // Test data

  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_INT_EQ( 100 + i, vec.at( i ) );

  for ( int i = 5; i < 10; i++ )
    ECE2400_CHECK_INT_EQ( 200 + i, vec.at( i ) );

  for ( int i = 10; i < 20; i++ )
    ECE2400_CHECK_INT_EQ( 300 + i, vec.at( i ) );

  for ( int i = 20; i < 30; i++ )
    ECE2400_CHECK_INT_EQ( 400 + i, vec.at( i ) );

  // Test size

  ECE2400_CHECK_INT_EQ( vec.size(), 30 );

  // Test at and contains, expecting successful

  for ( int i = 0; i < 5; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( 100 + i ) );
    ECE2400_CHECK_INT_EQ( vec.at( i ), 100 + i );
  }

  for ( int i = 5; i < 10; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( 200 + i ) );
    ECE2400_CHECK_INT_EQ( vec.at( i ), 200 + i );
  }

  for ( int i = 10; i < 20; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( 300 + i ) );
    ECE2400_CHECK_INT_EQ( vec.at( i ), 300 + i );
  }

  for ( int i = 20; i < 30; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( 400 + i ) );
    ECE2400_CHECK_INT_EQ( vec.at( i ), 400 + i );
  }

  // Test contains, expecting not successful

  for ( int i = 1000; i < 2000; i++ )
    ECE2400_CHECK_FALSE( vec.contains( i ) );

  // Test find_closest_linear

  for ( int i = 0; i < 100; i++ )
    ECE2400_CHECK_INT_EQ( vec.find_closest_linear( i ), 100 );

  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 250 ), 209 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 350 ), 319 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_linear( 450 ), 429 );
}

//------------------------------------------------------------------------
// test_case_17_self_assignment
//------------------------------------------------------------------------
// Test self assignment

void test_case_17_self_assignment()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;

  vec.push_back( 42 );
  vec.push_back( 43 );
  vec.push_back( 44 );
  vec.push_back( 45 );

  vec = vec;
}

//------------------------------------------------------------------------
// test_case_18_assign_twice
//------------------------------------------------------------------------
// Assign vec0 to vec1, vec1 to vec2

void test_case_18_assign_twice()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;
  VectorInt vec1;
  VectorInt vec2;

  vec0.push_back( 1 );
  vec0.push_back( 2 );
  vec0.push_back( 3 );
  vec1.push_back( 11 );
  vec1.push_back( 12 );
  vec2.push_back( 21 );
  vec2.push_back( 22 );

  vec1 = vec0;           // vec1 has 1, 2, 3
  vec1.push_back( 11 );  // vec1 has 1, 2, 3, 11
  vec2 = vec1;           // vec2 has 1, 2, 3, 11
  vec2.push_back( 22 );  // vec2 has 1, 2, 3, 11, 22

  ECE2400_CHECK_TRUE( vec0.size() == 3 );
  ECE2400_CHECK_TRUE( vec1.size() == 4 );
  ECE2400_CHECK_TRUE( vec2.size() == 5 );
  ECE2400_CHECK_INT_EQ( vec2.at( 0 ), 1 );
  ECE2400_CHECK_INT_EQ( vec2.at( 1 ), 2 );
  ECE2400_CHECK_INT_EQ( vec2.at( 2 ), 3 );
  ECE2400_CHECK_INT_EQ( vec2.at( 3 ), 11 );
  ECE2400_CHECK_INT_EQ( vec2.at( 4 ), 22 );
}

//------------------------------------------------------------------------
// test_case_19_copy_twice
//------------------------------------------------------------------------
// Copy vec0 to vec1, vec1 to vec2

void test_case_19_copy_twice()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;

  vec0.push_back( 1 );
  vec0.push_back( 2 );
  vec0.push_back( 3 );

  VectorInt vec1 = vec0;  // vec1 has 1, 2, 3
  vec1.push_back( 11 );   // vec1 has 1, 2, 3, 11
  VectorInt vec2 = vec1;  // vec2 has 1, 2, 3, 11
  vec2.push_back( 22 );   // vec2 has 1, 2, 3, 11, 22

  ECE2400_CHECK_TRUE( vec0.size() == 3 );
  ECE2400_CHECK_TRUE( vec1.size() == 4 );
  ECE2400_CHECK_TRUE( vec2.size() == 5 );
  ECE2400_CHECK_INT_EQ( vec2.at( 0 ), 1 );
  ECE2400_CHECK_INT_EQ( vec2.at( 1 ), 2 );
  ECE2400_CHECK_INT_EQ( vec2.at( 2 ), 3 );
  ECE2400_CHECK_INT_EQ( vec2.at( 3 ), 11 );
  ECE2400_CHECK_INT_EQ( vec2.at( 4 ), 22 );
}

//------------------------------------------------------------------------
// test_case_20_assign_empty
//------------------------------------------------------------------------
// Assign an empty vector

void test_case_20_assign_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;
  VectorInt vec1;

  vec0.push_back( 1 );
  vec0.push_back( 2 );
  vec0.push_back( 3 );

  vec0 = vec1;

  ECE2400_CHECK_TRUE( vec0.size() == 0 );
  ECE2400_CHECK_TRUE( vec1.size() == 0 );
}

//------------------------------------------------------------------------
// test_case_21_copy_empty
//------------------------------------------------------------------------
// Copy an empty vector

void test_case_21_copy_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec0;

  VectorInt vec1 = vec0;

  ECE2400_CHECK_TRUE( vec0.size() == 0 );
  ECE2400_CHECK_TRUE( vec1.size() == 0 );
}

//'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
// Add more test cases here
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

void test_case_22_large_k()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;

  for ( int i = 0; i < 20; i++ ) {
    vec.push_back( i );
  }
  for ( int i = 21; i < 50; i++ ) {
    vec.push_back( i );
  }

  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 20 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 30 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 40 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 50 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 60 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 70 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 80 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 90 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 100 ), 19 );
}

void test_case_23_large_k_large_gap()
{
  std::printf( "\n%s\n", __func__ );

  VectorInt vec;

  for ( int i = 0; i < 20; i++ ) {
    vec.push_back( i );
    i = i + 19;
  }
  for ( int i = 21; i < 50; i++ ) {
    vec.push_back( i );
    i = i + 19;
  }

  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 20 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 30 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 40 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 50 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 60 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 70 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 80 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 90 ), 19 );
  ECE2400_CHECK_INT_EQ( vec.find_closest_binary( 20, 100 ), 19 );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_simple_push_back();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_at_out_of_bound();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_construct();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_find_simple();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_find_empty();
  if ( ( __n == 0 ) || ( __n == 6  ) ) test_case_6_find_closest_linear();
  if ( ( __n == 0 ) || ( __n == 7  ) ) test_case_7_find_closest_linear_empty();
  if ( ( __n == 0 ) || ( __n == 8  ) ) test_case_8_find_closest_binary();
  if ( ( __n == 0 ) || ( __n == 9  ) ) test_case_9_find_closest_binary_empty();
  if ( ( __n == 0 ) || ( __n == 10 ) ) test_case_10_find_closest_binary_unsorted();
  if ( ( __n == 0 ) || ( __n == 11 ) ) test_case_11_sort_simple();
  if ( ( __n == 0 ) || ( __n == 12 ) ) test_case_12_subscript();
  if ( ( __n == 0 ) || ( __n == 13 ) ) test_case_13_copy();
  if ( ( __n == 0 ) || ( __n == 14 ) ) test_case_14_assignment_empty();
  if ( ( __n == 0 ) || ( __n == 15 ) ) test_case_15_assignment_non_empty();
  if ( ( __n == 0 ) || ( __n == 16 ) ) test_case_16_general();
  if ( ( __n == 0 ) || ( __n == 17 ) ) test_case_17_self_assignment();
  if ( ( __n == 0 ) || ( __n == 18 ) ) test_case_18_assign_twice();
  if ( ( __n == 0 ) || ( __n == 19 ) ) test_case_19_copy_twice();
  if ( ( __n == 0 ) || ( __n == 20 ) ) test_case_20_assign_empty();
  if ( ( __n == 0 ) || ( __n == 21 ) ) test_case_21_copy_empty();
  if ( ( __n == 0 ) || ( __n == 22 ) ) test_case_22_large_k();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return __failed;
}
// clang-format on
