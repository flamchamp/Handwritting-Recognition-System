//========================================================================
// vector-directed-tests.h
//========================================================================
// This file contains generic directed tests for vectors. All of the
// generic test functions are templated by an "object creation" function
// which should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Vector.h"

#include <cstdio>

//------------------------------------------------------------------------
// test_case_simple_push_back
//------------------------------------------------------------------------
// A simple test case that tests default constructor, push_back, and at.

template < typename T, typename Func >
void test_case_simple_push_back( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Vector<T> vec;

  // Check size of empty vector
  ECE2400_CHECK_INT_EQ( vec.size(), 0 );

  // Push back some values
  T data[] = { f(10), f(11), f(12) };
  for ( T v : data )
    vec.push_back( v );

  // Check size
  ECE2400_CHECK_INT_EQ( vec.size(), 3 );

  // Check values
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_TRUE( vec.at(i) == data[i] );
}

//------------------------------------------------------------------------
// test_case_at_out_of_bound
//------------------------------------------------------------------------
// Test that exception is properly thrown when at is out of bound.

template < typename T, typename Func >
void test_case_at_out_of_bound( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Vector<T> vec;

  // empty vector

  bool flag = false;
  try {
    vec.at(0);
  }
  catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // push back some values

  vec.push_back(f(0));
  vec.push_back(f(9));

  ECE2400_CHECK_TRUE( vec.at(0) == f(0) );
  ECE2400_CHECK_TRUE( vec.at(1) == f(9) );

  // right at the boundary

  flag = false;
  try {
    vec.at(2);
  }
  catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // beyond the boundary

  flag = false;
  try {
    vec.at(5);
  }
  catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_construct
//------------------------------------------------------------------------
// A simple test case that tests non-default constructor.

template < typename T, typename Func >
void test_case_construct( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Test constructing from array with one element

  T a0[] = { f(10) };
  Vector<T> vec0( a0, 1 );

  ECE2400_CHECK_INT_EQ( vec0.size(),  1 );
  ECE2400_CHECK_TRUE( vec0.at(0) == f(10) );

  // Test constructing from array with two elements

  T a1[] = { f(10), f(11) };
  Vector<T> vec1( a1, 2 );

  ECE2400_CHECK_INT_EQ( vec1.size(), 2 );
  ECE2400_CHECK_TRUE( vec1.at(0) == f(10) );
  ECE2400_CHECK_TRUE( vec1.at(1) == f(11) );

  // Test constructing from array with three elements

  T a2[] = { f(10), f(11), f(12) };
  Vector<T> vec2( a2, 3 );

  ECE2400_CHECK_INT_EQ( vec2.size(), 3 );
  ECE2400_CHECK_TRUE( vec2.at(0) == f(10) );
  ECE2400_CHECK_TRUE( vec2.at(1) == f(11) );
  ECE2400_CHECK_TRUE( vec2.at(2) == f(12) );

  // Test constructing from array with eight elements

  T a3[] = { f(0), f(1), f(2), f(3), f(4), f(5), f(6), f(7) };
  Vector<T> vec3( a3, 8 );

  ECE2400_CHECK_INT_EQ( vec3.size(), 8 );

  for ( int i = 0; i < 8; i++ )
    ECE2400_CHECK_TRUE( vec3.at(i) == f(i) );
}

//------------------------------------------------------------------------
// test_case_construct_empty
//------------------------------------------------------------------------
// A simple test case that tests non-default constructor with empty array

template < typename T, typename Func >
void test_case_construct_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Test constructing from empty array

  T* a0 = nullptr;
  Vector<T> vec0( a0, 0 );

  ECE2400_CHECK_INT_EQ( vec0.size(), 0 );

  // Test constructing from empty array

  T a1[] = { f(10), f(11), f(12) };
  Vector<T> vec1( a1, 0 );

  ECE2400_CHECK_INT_EQ( vec1.size(), 0 );
}

//------------------------------------------------------------------------
// test_case_contains_simple
//------------------------------------------------------------------------
// A simple test case that tests contains.

template < typename T, typename Func >
void test_case_contains_simple( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a vector from array

  T data[] = { f(1), f(9), f(9), f(5), f(0), f(4), f(2), f(3) };
  Vector<T> vec( data, 8 );

  // Search for value, expecting success

  ECE2400_CHECK_TRUE( vec.contains(f(1)) );
  ECE2400_CHECK_TRUE( vec.contains(f(9)) );
  ECE2400_CHECK_TRUE( vec.contains(f(5)) );
  ECE2400_CHECK_TRUE( vec.contains(f(0)) );
  ECE2400_CHECK_TRUE( vec.contains(f(4)) );
  ECE2400_CHECK_TRUE( vec.contains(f(2)) );
  ECE2400_CHECK_TRUE( vec.contains(f(3)) );

  // Search for value, expecting failure

  ECE2400_CHECK_FALSE( vec.contains(f(6)) );
  ECE2400_CHECK_FALSE( vec.contains(f(7)) );
  ECE2400_CHECK_FALSE( vec.contains(f(8)) );
}

//------------------------------------------------------------------------
// test_case_contains_empty
//------------------------------------------------------------------------
// A simple test case that tests contains for an empty vector.

template < typename T, typename Func >
void test_case_contains_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct an empty vector
  Vector<T> vec;

  // Search for value, expecting failure
  for ( int i = 0; i < 10; i++ )
    ECE2400_CHECK_FALSE( vec.contains(f(i)) );
}

//------------------------------------------------------------------------
// test_case_find_closest_linear
//------------------------------------------------------------------------
// A simple test case that tests find_closest_linear.

template < typename T, typename Func, typename DistFunc >
void test_case_find_closest_linear( int test_case_num, Func f, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  T data[] = { f(40), f(20), f(60), f(10), f(30), f(50), f(70) };
  Vector<T> vec( data, 7 );

  // First find exact matches

  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(10), dist)  == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(20), dist)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(30), dist)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(40), dist)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(50), dist)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(60), dist)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(70), dist)  == f(70) );

  // Find near matches

  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(9),  dist)   == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(11), dist)  == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(19), dist)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(21), dist)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(29), dist)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(31), dist)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(39), dist)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(41), dist)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(49), dist)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(51), dist)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(59), dist)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(61), dist)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(69), dist)  == f(70) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear(f(71), dist)  == f(70) );
}

//------------------------------------------------------------------------
// test_case_find_closest_binary
//------------------------------------------------------------------------
// A simple test case that tests find_closest_binary.

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_find_closest_binary( int test_case_num, Func f, int k,
                                    DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  T data[] = { f(40), f(20), f(60), f(10), f(30), f(50), f(70) };
  Vector<T> vec( data, 7 );
  vec.sort( cmp );

  // First find exact matches
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(10), k, dist, cmp)  == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(20), k, dist, cmp)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(30), k, dist, cmp)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(40), k, dist, cmp)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(50), k, dist, cmp)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(60), k, dist, cmp)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(70), k, dist, cmp)  == f(70) );

  // Find near matches
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(9),  k, dist, cmp)   == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(11), k, dist, cmp)  == f(10) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(19), k, dist, cmp)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(21), k, dist, cmp)  == f(20) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(29), k, dist, cmp)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(31), k, dist, cmp)  == f(30) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(39), k, dist, cmp)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(41), k, dist, cmp)  == f(40) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(49), k, dist, cmp)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(51), k, dist, cmp)  == f(50) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(59), k, dist, cmp)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(61), k, dist, cmp)  == f(60) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(69), k, dist, cmp)  == f(70) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary(f(71), k, dist, cmp)  == f(70) );
}

//------------------------------------------------------------------------
// test_case_find_closest_linear_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling
// find_closest_linear on an empty vector.

template < typename T, typename Func, typename DistFunc >
void test_case_find_closest_linear_empty( int test_case_num, Func f,
                                          DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Vector<T> vec;

  bool flag = false;
  try {
    vec.find_closest_linear( f(0), dist );
  }
  catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_find_closest_binary_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling
// find_closest_binary on an empty vector.

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_find_closest_binary_empty( int test_case_num, Func f, int k,
                                          DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Vector<T> vec;
  vec.sort( cmp );

  bool flag = false;
  try {
    vec.find_closest_binary( f(0), k, dist, cmp );
  }
  catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_find_closest_binary_unsorted
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling
// find_closest_binary on an unsorted vector.

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_find_closest_binary_unsorted( int test_case_num, Func f, int k,
                                          DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  T data[] = { f(40), f(20), f(60), f(10), f(30), f(50), f(70) };
  Vector<T> vec( data, 7 );

  bool flag = false;
  try {
    vec.find_closest_binary( f(0), k, dist, cmp );
  }
  catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  flag = false;
  vec.sort( cmp );
  try {
    vec.find_closest_binary( f(0), k, dist, cmp );
  }
  catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_FALSE( flag );

  vec.push_back( f(0) );
  flag = false;
  try {
    vec.find_closest_binary( f(0), k, dist, cmp );
  }
  catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_sort_simple
//------------------------------------------------------------------------
// A simple sort test.

template < typename T, typename Func, typename CmpFunc >
void test_case_sort_simple( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a vector
  T data[] = { f(1), f(9), f(9), f(5), f(0), f(4), f(2), f(3) };
  Vector<T> vec( data, 8 );

  // Sort the vector
  vec.sort( cmp );

  // Sorted reference array
  T ref[] = { f(0), f(1), f(2), f(3), f(4), f(5), f(9), f(9) };

  // Verify that we sorted things correctly
  for ( int i = 0; i < 8; i++ )
    ECE2400_CHECK_TRUE( vec.at(i) == ref[i] );
}

//------------------------------------------------------------------------
// test_case_subscript
//------------------------------------------------------------------------
// A simple test for the subscript operator.

template < typename T, typename Func >
void test_case_subscript( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a vector from array
  T data[] = { f(1), f(9), f(9), f(5), f(0), f(4), f(2), f(3) };
  Vector<T> vec( data, 8 );

  // Check the value using subscript operator
  for ( int i = 0; i < 8; i++ )
    ECE2400_CHECK_TRUE( vec[i] == data[i] );
}

//------------------------------------------------------------------------
// test_case_copy_v1
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with first syntax.

template < typename T, typename Func >
void test_case_copy_v1( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  Vector<T> vec0;
  for ( T v : data0 )
    vec0.push_back( v );

  // Copy constructor

  Vector<T> vec1( vec0 );

  // Push different values to vec0 and vec1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 8 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data0[i] );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i+4) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i+4) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_copy_v2
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with second syntax.

template < typename T, typename Func >
void test_case_copy_v2( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  Vector<T> vec0;
  for ( T v : data0 )
    vec0.push_back( v );

  // Copy constructor with second syntax

  Vector<T> vec1 = vec0;

  // Push different values to vec0 and vec1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 8 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data0[i] );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i+4) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i+4) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_copy_empty
//------------------------------------------------------------------------
// A simple test case that tests copy constructor from empty vector.

template < typename T, typename Func >
void test_case_copy_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Copy constructor

  Vector<T> vec0;
  Vector<T> vec1 = vec0;

  // Check both vectors are empty

  ECE2400_CHECK_INT_EQ( vec0.size(), 0 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 0 );

  // Push different values to vec0 and vec1

  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    vec0.push_back( v );

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 4 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_assignment
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a non-empty
// vector.

template < typename T, typename Func >
void test_case_assignment( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  Vector<T> vec0;
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    vec0.push_back( v );

  // Push back some values to vec1

  Vector<T> vec1;
  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( int i = 0; i < 10; i++ )
    vec1.push_back( f(i) );

  // Assignment operator

  vec1 = vec0;

  // Push different values to vec0 and vec1

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data1 )
    vec0.push_back( v );

  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 8 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data0[i] );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i+4) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i+4) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_to_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator to empty vector from
// non-empty vector.

template < typename T, typename Func >
void test_case_assignment_to_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  Vector<T> vec0;
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    vec0.push_back( v );

  // Assignment operator

  Vector<T> vec1;
  vec1 = vec0;

  // Push different values to vec0 and vec1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 8 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data0[i] );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i+4) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i+4) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_from_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty vector to
// non-empty vector.

template < typename T, typename Func >
void test_case_assignment_from_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  Vector<T> vec0;
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    vec0.push_back( v );

  // Assignment operator

  Vector<T> vec1;
  vec0 = vec1;

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 0 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 0 );

  // Push different values to vec0 and vec1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 4 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty vector to
// empty vector.

template < typename T, typename Func >
void test_case_assignment_empty( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Assignment operator

  Vector<T> vec0;
  Vector<T> vec1;

  vec0 = vec1;

  // Push different values to vec0 and vec1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    vec1.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 4 );
  ECE2400_CHECK_INT_EQ( vec1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at(i) == data1[i] );
    ECE2400_CHECK_TRUE( vec1.at(i) == data2[i] );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_self
//------------------------------------------------------------------------
// A simple test case that tests self assignment.

template < typename T, typename Func >
void test_case_assignment_self( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to vec0

  Vector<T> vec0;
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    vec0.push_back( v );

  // Assignment operator

  vec0 = vec0;

  // Push more values into vec0

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    vec0.push_back( v );

  // Check size

  ECE2400_CHECK_INT_EQ( vec0.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( vec0.at(i) == data0[i] );

  // Check the second 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( vec0.at(i+4) == data1[i] );
}

//------------------------------------------------------------------------
// test_case_general
//------------------------------------------------------------------------
// A generic test case.

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_general( int test_case_num, Func f, int k,
                        DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a new vector

  Vector<T> vec;

  // Push data into the data structure

  for ( int i = 0; i < 5; i++ )
    vec.push_back( f(50+i) );

  for ( int i = 5; i < 10; i++ )
    vec.push_back( f(100+i) );

  for ( int i = 10; i < 20; i++ )
    vec.push_back( f(150+i) );

  for ( int i = 20; i < 30; i++ )
    vec.push_back( f(200+i) );

  // Test data

  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_TRUE( f(50+i) == vec.at(i) );

  for ( int i = 5; i < 10; i++ )
    ECE2400_CHECK_TRUE( f(100+i) == vec.at(i) );

  for ( int i = 10; i < 20; i++ )
    ECE2400_CHECK_TRUE( f(150+i) == vec.at(i) );

  for ( int i = 20; i < 30; i++ )
    ECE2400_CHECK_TRUE( f(200+i) == vec.at(i) );

  // Test size

  ECE2400_CHECK_INT_EQ( vec.size(), 30 );

  // Test at and contains, expecting successful

  for ( int i = 0; i < 5; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( f(50+i) ) );
    ECE2400_CHECK_TRUE( vec.at(i) == f(50+i) );
  }

  for ( int i = 5; i < 10; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( f(100+i) ) );
    ECE2400_CHECK_TRUE( vec.at(i) == f(100+i) );
  }

  for ( int i = 10; i < 20; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( f(150+i) ) );
    ECE2400_CHECK_TRUE( vec.at(i) == f(150+i) );
  }

  for ( int i = 20; i < 30; i++ ) {
    ECE2400_CHECK_TRUE( vec.contains( f(200+i) ) );
    ECE2400_CHECK_TRUE( vec.at(i) == f(200+i) );
  }

  // Test contains, expecting not successful

  for ( int i = 0; i < 50; i++ )
    ECE2400_CHECK_FALSE( vec.contains( f(i) ) );

  // Test find_closest_linear

  for ( int i = 0; i < 50; i++ )
    ECE2400_CHECK_TRUE( vec.find_closest_linear( f(i), dist ) == f(50) );

  ECE2400_CHECK_TRUE( vec.find_closest_linear( f(75), dist ) == f(54) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( f(125), dist ) == f(109) );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( f(175), dist ) == f(169) );

  // Test find_closest_binary
  vec.sort( cmp );
  //vec.print();
  for ( int i = 0; i < 50; i++ ) {
    ECE2400_CHECK_TRUE( vec.find_closest_binary( f(i), k, dist, cmp ) == f(50) );
  }
  ECE2400_CHECK_TRUE( vec.find_closest_binary( f(75),  k, dist, cmp ) == f(54) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( f(125), k, dist, cmp ) == f(109) );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( f(175), k, dist, cmp ) == f(169) );
}

