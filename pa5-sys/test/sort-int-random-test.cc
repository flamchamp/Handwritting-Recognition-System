//========================================================================
// sort-int-random-tests.c
//========================================================================
// This file contains the tests for the sort function with ints

#include "ece2400-stdlib.h"
#include "sort-random-test.h"
#include "sort.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// Object Creation Function
//------------------------------------------------------------------------
// All of the generic test functions are templated by an "object
// creation" function which should take as a parameter an integer and
// return a newly created object. For integers, the object creation
// function can just be the identity function.

int mk_int( int x )
{
  return x;
}

//------------------------------------------------------------------------
// Less free function
//------------------------------------------------------------------------
bool int_less( int a, int b )
{
  return a < b;
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  typedef int (IntFunc)(int);
  typedef bool (*IntCmp)( int, int );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( !__n || ( __n == 1 ) ) test_case_random<int,IntFunc,IntCmp>(1,&mk_int,int_less);
  if ( !__n || ( __n == 2 ) ) test_case_random_few_unique<int,IntFunc,IntCmp>(2,&mk_int,int_less);

  std::printf("\n");
  return __failed;
}
// clang-format on
