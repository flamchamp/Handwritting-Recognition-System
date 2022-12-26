//========================================================================
// vector-int-random-test.cc
//========================================================================
// This file contains random tests for Vector<int>

#include "Vector.h"
#include "vector-random-test.h"

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
// Distance free function
//------------------------------------------------------------------------
int int_dist( int a, int b )
{
  if ( a < b ) {
    return b - a;
  }
  else {
    return a - b;
  }
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
  typedef int (*IntDist)( int, int );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( !__n || ( __n ==  1 ) ) test_case_push_back_random<int>(1,&mk_int);
  if ( !__n || ( __n ==  2 ) ) test_case_copy_random<int>(2,&mk_int);
  if ( !__n || ( __n ==  3 ) ) test_case_construct_random<int>(3,&mk_int);
  if ( !__n || ( __n ==  4 ) ) test_case_find_closest_linear_random<int,IntFunc,IntDist>(4,&mk_int,int_dist);
  if ( !__n || ( __n ==  5 ) ) test_case_find_closest_binary_random<int,IntFunc,IntDist,IntCmp>(5,&mk_int,4,int_dist,int_less);
  if ( !__n || ( __n ==  6 ) ) test_case_general_random<int,IntFunc,IntDist,IntCmp>(6,&mk_int,4,int_dist,int_less);

  printf("\n");
  return __failed;
}
// clang-format on
