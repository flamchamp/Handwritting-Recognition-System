//========================================================================
// vector-random-test.h
//========================================================================
// This file contains generic random tests for vectors. All of the
// generic test functions are templated by an "object creation" function
// which should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Vector.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// test_case_push_back_random
//------------------------------------------------------------------------
// A random test case that tests push back.

template < typename T, typename Func >
void test_case_push_back_random( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    Vector<T> vec;

    int size = std::rand() % 100;
    T*  data = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    for ( int j = 0; j < size; j++ ) {
      T value = f(std::rand() % 250);
      vec.push_back( value );
      data[j] = value;
    }

    ECE2400_CHECK_INT_EQ( vec.size(), size );

    // Check vector against array that has same elements

    for ( int j = 0; j < size; j++ ) {
      ECE2400_CHECK_TRUE( vec.at(j) == data[j] );
      ECE2400_CHECK_TRUE( vec[j]    == data[j] );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_copy_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

template < typename T, typename Func >
void test_case_copy_random( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    Vector<T> vec0;
    Vector<T> vec1;

    int size  = std::rand() % 100;
    T*  data0 = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    for ( int j = 0; j < size; j++ ) {
      T value = f(std::rand() % 250);
      vec0.push_back( value );
      data0[j] = value;
    }

    // Assignment operator

    vec1 = vec0;

    // Copy constructor

    Vector<T> vec2( vec1 );

    // Add more elements to vec0 and vec1

    int size1 = std::rand() % 100;
    T*  data1 = new T[size1];

    for ( int j = 0; j < size1; j++ ) {
      T value = f(std::rand() % 250);
      vec1.push_back( value );
      vec2.push_back( value );
      data1[j] = value;
    }

    ECE2400_CHECK_INT_EQ( vec0.size(), size );
    ECE2400_CHECK_INT_EQ( vec1.size(), size + size1 );
    ECE2400_CHECK_INT_EQ( vec2.size(), size + size1 );

    // Check the copied elements

    for ( int j = 0; j < size; j++ ) {
      ECE2400_CHECK_TRUE( vec0.at(j) == data0[j] );
      ECE2400_CHECK_TRUE( vec1.at(j) == data0[j] );
      ECE2400_CHECK_TRUE( vec2.at(j) == data0[j] );
    }

    // Check additional elements for vec0 and vec1

    for ( int j = 0; j < size1; j++ ) {
      ECE2400_CHECK_TRUE( vec1.at( size + j ) == data1[j] );
      ECE2400_CHECK_TRUE( vec2.at( size + j ) == data1[j] );
    }

    delete[] data0;
    delete[] data1;
  }
}

//------------------------------------------------------------------------
// test_case_construct_random
//------------------------------------------------------------------------
// A random test case that tests construct Vector<T> from an array.

template < typename T, typename Func >
void test_case_construct_random( int test_case_num, Func f )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    int size = std::rand() % 100;
    T*  data = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    for ( int j = 0; j < size; j++ )
      data[j] = f(j);

    // Construct the vector from an array
    Vector<T> vec( data, size );

    // Modify the array to test deepcopy
    for ( int j = 0; j < size; j++ )
      data[j] = f(size+1);

    // Check that the value inside the vector is not modified
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.at(j) == f(j) );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_find_closest_linear_random
//------------------------------------------------------------------------
// A random test case that tests find_closest_linear

template < typename T, typename Func, typename DistFunc >
void test_case_find_closest_linear_random( int test_case_num, Func f, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    int size = std::rand() % 10;
    T*  data = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    int offset = rand() % 10 + 10;

    for ( int j = 0; j < size; j++ )
      data[j] = f(j*offset);

    Vector<T> vec( data, size );

    // Check the closest value for the multiples of offset plus one
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.find_closest_linear( f(j*offset+1), dist ) == f(j*offset) );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_find_closest_binary_random
//------------------------------------------------------------------------
// A random test case that tests find_closest_binary

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_find_closest_binary_random( int test_case_num, Func f, int k,
                                           DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    int size = std::rand() % 10;
    T*  data = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    int offset = rand() % 10 + 10;

    for ( int j = 0; j < size; j++ )
      data[j] = f(j*offset);

    Vector<T> vec( data, size );
    vec.sort( cmp );

    // Check the closest value for the multiples of offset plus one
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.find_closest_binary( f(j*offset+1), k, dist, cmp ) == f(j*offset) );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_general_random
//------------------------------------------------------------------------

template < typename T, typename Func, typename DistFunc, typename CmpFunc >
void test_case_general_random( int test_case_num, Func f, int k,
                               DistFunc dist, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 10; i++ ) {

    int size = std::rand() % 100;
    T*  data = new T[size];

    ECE2400_DEBUG( "size = %d\n", size );

    Vector<T> vec;

    for ( int j = 0; j < size; j++ ) {
      data[j] = f(j);
      vec.push_back(f(j));
      ECE2400_CHECK_INT_EQ( vec.size(), j+1 );
    }

    // Test at and contains, expecting successful
    for ( int j = 0; j < size; j++ ) {
      ECE2400_CHECK_TRUE( vec.contains(f(j)) );
      ECE2400_CHECK_TRUE( vec.at(j) == f(j) );
    }

    // Test contains, expecting not successful
    for ( int j = size; j < 2*size; j++ )
      ECE2400_CHECK_FALSE( vec.contains(f(j)) );

    // Test find_closest_linear
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.find_closest_linear(f(j), dist) == f(j) );

    // Test find_closets for value beyond size
    ECE2400_CHECK_TRUE( vec.find_closest_linear(f(size), dist) == f(size-1) );

    // Test find_closets for value 0
    ECE2400_CHECK_TRUE( vec.find_closest_linear(f(0), dist) == f(0) );

    // Test find_closest_binary
    vec.sort( cmp );
    for ( int j = 0; j < size; j++ ){
      //vec.print();
      // printf("size is %d\n", size);
      // printf("j is %d\n", j);
      // printf("f(j) is %d\n", f(j));
      // printf("k is %d\n", k);
      // printf("what bin returns is %d\n", vec.find_closest_binary(f(j), k, dist, cmp));
      ECE2400_CHECK_TRUE( vec.find_closest_binary(f(j), k, dist, cmp) == f(j) );
    }

    // Test find_closets for value beyond size
    ECE2400_CHECK_TRUE( vec.find_closest_binary(f(size), k, dist, cmp) == f(size-1) );

    // Test find_closets for value 0
    ECE2400_CHECK_TRUE( vec.find_closest_binary(f(0), k, dist, cmp) == f(0) );

    delete[] data;
  }
}

