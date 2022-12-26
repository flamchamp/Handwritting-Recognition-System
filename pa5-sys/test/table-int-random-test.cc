//========================================================================
// table-int-random-test.cc
//========================================================================
// This file contains random tests for Table<int>

#include "Table.h"
#include "table-random-test.h"

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
// Hash free function
//------------------------------------------------------------------------
int int_hash( int a )
{
  return a;
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  typedef int (IntFunc)(int);
  typedef int (*IntHash)( int );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( !__n || ( __n ==  1 ) ) test_case_add_random<int,IntFunc,IntHash>(1,&mk_int,int_hash);
  if ( !__n || ( __n ==  2 ) ) test_case_copy_random<int,IntFunc,IntHash>(2,&mk_int,int_hash);

  std::printf("\n");
  return __failed;
}
// clang-format on
