//========================================================================
// sort-random-tests.h
//========================================================================
// This file contains generic random tests for the sort function. All of
// the generic test functions are templated by an "object creation"
// function which should take as a parameter an integer and return a
// newly created object. For integers, the object creation function can
// just be the identity function. For images, the object creation
// function can create a small image and initialize the pixels based on
// the given integer.

#include "sort.h"
#include "ece2400-stdlib.h"

#include <cstdio>
#include <cstdlib>
#include <cstddef>

//------------------------------------------------------------------------
// test_case_random
//------------------------------------------------------------------------
// Many random values

template < typename T, typename Func, typename CmpFunc >
void test_case_random( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  // Do 100 random tests

  for ( int i = 0; i < 100; i++ ) {

    // Choose a random size

    int size = std::rand() % 100;
    ECE2400_DEBUG( "size = %d\n", size );

    // Allocate space for our test array and reference array

    T* a     = new T[size];
    T* a_ref = new T[size];

    // Fill both arrays with random values

    for ( int j = 0; j < size; j++ ) {
      T value   = f( std::rand() % 250 );
      a[j]      = value;
      a_ref[j]  = value;
    }

    // Use our sort algorithm on test array

    sort( a, size, cmp );

    // Verify that we sorted things correctly

    for ( int j = 1; j < size; j++ )
      // a[j-1] <= a[j]
      ECE2400_CHECK_FALSE( cmp( a[j], a[j-1] ) );

    // Cleanup

    delete[] a;
    delete[] a_ref;
  }

}

//------------------------------------------------------------------------
// test_case_random_few_unique
//------------------------------------------------------------------------
// Many values, but few unique

template < typename T, typename Func, typename CmpFunc >
void test_case_random_few_unique( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  // Do 100 random tests

  for ( int i = 0; i < 100; i++ ) {

    // Choose a random size

    int size = std::rand() % 100;
    ECE2400_DEBUG( "size = %d\n", size );

    // Allocate space for our test array and reference array

    T* a     = new T[size];
    T* a_ref = new T[size];

    // Fill both arrays with random values

    for ( int j = 0; j < size; j++ ) {
      T value   = f( std::rand() % 10 );
      a[j]      = value;
      a_ref[j]  = value;
    }

    // Use our sort algorithm on test array

    sort( a, size, cmp );

    // Verify that we sorted things correctly

    for ( int j = 1; j < size; j++ )
      // a[j-1] <= a[j]
      ECE2400_CHECK_FALSE( cmp( a[j], a[j-1] ) );

    // Cleanup

    delete[] a;
    delete[] a_ref;
  }

}

