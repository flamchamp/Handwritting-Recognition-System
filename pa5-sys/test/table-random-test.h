//========================================================================
// table-random-test.h
//========================================================================
// This file contains generic random tests for tables. All of the generic
// test functions are templated by an "object creation" function which
// should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Table.h"
#include "ece2400-stdlib.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// test_case_add_random
//------------------------------------------------------------------------
// A random test case that tests push back.

template < typename T, typename Func, typename HashFunc >
void test_case_add_random( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 50; i++ ) {

    int k = (std::rand() % 20) + 10;
    Table<T,HashFunc> table( k, hash );

    int  size = std::rand() % 100;
    int* data = new int[size];

    ECE2400_DEBUG( "k = %d, size = %d\n", k, size );

    for ( int j = 0; j < size; j++ ) {
      int rand_int = std::rand() % 255;
      table.add( f(rand_int) );
      data[j] = rand_int;
    }

    ECE2400_CHECK_INT_EQ( table.size(), size );

    // Check table against array that has same elements

    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( table.contains( f(data[j]) ) );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_copy_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

template < typename T, typename Func, typename HashFunc >
void test_case_copy_random( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 50; i++ ) {

    int k0 = (std::rand() % 20) + 10;
    Table<T,HashFunc> table0( k0, hash );

    int k1 = (std::rand() % 20) + 10;
    Table<T,HashFunc> table1( k1, hash );

    int  size0 = std::rand() % 100;
    int  size1 = std::rand() % 100;
    int* data  = new int[size0+size1];

    ECE2400_DEBUG( "k = %d, k = %d, size = %d\n", k0, k1, size0+size1 );

    for ( int j = 0; j < size0; j++ ) {
      int rand_int = std::rand() % 255;
      table0.add( f(rand_int) );
      data[j] = rand_int;
    }

    // Assignment operator

    table1 = table0;

    // Copy constructor

    Table<T,HashFunc> table2( table1 );

    // Add more elements to table0 and table1

    for ( int j = size0; j < size0+size1; j++ ) {
      int rand_int = std::rand() % 255;
      table1.add( f(rand_int) );
      table2.add( f(rand_int) );
      data[j] = rand_int;
    }

    // Check size

    ECE2400_CHECK_INT_EQ( table0.size(), size0 );
    ECE2400_CHECK_INT_EQ( table1.size(), size0+size1 );
    ECE2400_CHECK_INT_EQ( table2.size(), size0+size1 );

    // Check table 0

    for ( int j = 0; j < size0; j++ )
      ECE2400_CHECK_TRUE( table0.contains( f(data[j]) ) );

    for ( int j = 0; j < size0+size1; j++ ) {
      ECE2400_CHECK_TRUE( table1.contains( f(data[j]) ) );
      ECE2400_CHECK_TRUE( table2.contains( f(data[j]) ) );
    }

    delete[] data;
  }
}

