//========================================================================
// tree-random-test.h
//========================================================================
// This file contains generic random tests for trees. All of the generic
// test functions are templated by an "object creation" function which
// should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Tree.h"
#include "ece2400-stdlib.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// count_unique
//------------------------------------------------------------------------
// yes this is O(N^2) ...

int count_unique( int* data, int size )
{
  int num_unique = 0;
  for ( int i = 0; i < size; i++ ) {
    bool unique = true;
    for ( int j = i+1; j < size; j++ ) {
      if ( data[i] == data[j] )
        unique = false;
    }
    if ( unique )
      num_unique++;
  }
  return num_unique;
}

//------------------------------------------------------------------------
// test_case_add_random
//------------------------------------------------------------------------
// A random test case that tests push back.

template < typename T, typename Func, typename CmpFunc >
void test_case_add_random( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 50; i++ ) {

    Tree<T,CmpFunc> tree( 42, cmp );

    int  size = std::rand() % 100;
    int* data = new int[size];

    ECE2400_DEBUG( "size = %d\n", size );

    for ( int j = 0; j < size; j++ ) {
      int rand_int = std::rand() % 250;
      tree.add( f(rand_int) );
      data[j] = rand_int;
    }

    int num_unique = count_unique( data, size );
    ECE2400_CHECK_INT_EQ( tree.size(), num_unique );

    // Check tree against array that has same elements

    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( tree.contains( f(data[j]) ) );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_copy_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

template < typename T, typename Func, typename CmpFunc >
void test_case_copy_random( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );
  std::srand( 0xdeadbeef );

  for ( int i = 0; i < 50; i++ ) {

    Tree<T,CmpFunc> tree0( 42, cmp );
    Tree<T,CmpFunc> tree1( 42, cmp );

    int  size0 = std::rand() % 100;
    int  size1 = std::rand() % 100;
    int* data  = new int[size0+size1];

    ECE2400_DEBUG( "size = %d\n", size0+size1 );

    for ( int j = 0; j < size0; j++ ) {
      int rand_int = std::rand() % 250;
      tree0.add( f(rand_int) );
      data[j] = rand_int;
    }

    // Assignment operator

    tree1 = tree0;

    // Copy constructor

    Tree<T,CmpFunc> tree2( tree1 );

    // Add more elements to tree0 and tree1

    for ( int j = size0; j < size0+size1; j++ ) {
      int rand_int = std::rand() % 250;
      tree1.add( f(rand_int) );
      tree2.add( f(rand_int) );
      data[j] = rand_int;
    }

    // Check size

    int num_unique0 = count_unique( data, size0 );
    ECE2400_CHECK_INT_EQ( tree0.size(), num_unique0 );

    int num_unique1 = count_unique( data, size0 + size1 );
    ECE2400_CHECK_INT_EQ( tree1.size(), num_unique1 );
    ECE2400_CHECK_INT_EQ( tree2.size(), num_unique1 );

    // Check tree 0

    for ( int j = 0; j < size0; j++ )
      ECE2400_CHECK_TRUE( tree0.contains( f(data[j]) ) );

    for ( int j = 0; j < size0+size1; j++ ) {
      ECE2400_CHECK_TRUE( tree1.contains( f(data[j]) ) );
      ECE2400_CHECK_TRUE( tree2.contains( f(data[j]) ) );
    }

    delete[] data;
  }
}

