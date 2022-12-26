//========================================================================
// sort-int-directed-tests.c
//========================================================================
// This file contains the tests for the sort function with ints

#include "ece2400-stdlib.h"
#include "sort-directed-test.h"
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
// Less functor
//------------------------------------------------------------------------
class IntLess {
 public:
  bool operator()( int a, int b )
  {
    return a < b;
  }
};

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

  if ( !__n || ( __n ==  1 ) ) test_case_helper<int,IntFunc,IntCmp>(1,&mk_int,int_less);
  // three different ways to pass in a compare function: function pointer, functor, and lambda
  if ( !__n || ( __n ==  2 ) ) test_case_five_element<int,IntFunc,IntCmp>(2,&mk_int,int_less);
  if ( !__n || ( __n ==  3 ) ) test_case_five_element<int,IntFunc,IntLess>(2,&mk_int,IntLess());
  if ( !__n || ( __n ==  4 ) ) test_case_five_element<int,IntFunc,IntCmp>(2,&mk_int,
                                                     []( int a, int b ){ return a < b; } );
  if ( !__n || ( __n ==  5 ) ) test_case_empty<int,IntFunc,IntCmp>(3,&mk_int,int_less);
  if ( !__n || ( __n ==  6 ) ) test_case_one_element<int,IntFunc,IntCmp>(4,&mk_int,int_less);
  if ( !__n || ( __n ==  7 ) ) test_case_two_elements<int,IntFunc,IntCmp>(5,&mk_int,int_less);
  if ( !__n || ( __n ==  8 ) ) test_case_three_elements<int,IntFunc,IntCmp>(6,&mk_int,int_less);
  if ( !__n || ( __n ==  9 ) ) test_case_even_size_array<int,IntFunc,IntCmp>(7,&mk_int,int_less);
  if ( !__n || ( __n == 10 ) ) test_case_odd_size_array<int,IntFunc,IntCmp>(8,&mk_int,int_less);
  if ( !__n || ( __n == 11 ) ) test_case_almost_sorted<int,IntFunc,IntCmp>(9,&mk_int,int_less);
  if ( !__n || ( __n == 12 ) ) test_case_sorted_ascending<int,IntFunc,IntCmp>(10,&mk_int,int_less);
  if ( !__n || ( __n == 13 ) ) test_case_sorted_descending<int,IntFunc,IntCmp>(11,&mk_int,int_less);
  if ( !__n || ( __n == 14 ) ) test_case_few_unique<int,IntFunc,IntCmp>(12,&mk_int,int_less);

  std::printf("\n");
  return __failed;
}
// clang-format on
