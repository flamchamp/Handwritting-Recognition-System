//========================================================================
// tree-int-directed-test.cc
//========================================================================
// This file contains directed tests for Tree<int>

#include "Tree.h"
#include "tree-directed-test.h"

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

  if ( !__n || ( __n ==  1 ) ) test_case_simple_add<int,IntFunc,IntCmp>(1,&mk_int,int_less);
  if ( !__n || ( __n ==  2 ) ) test_case_duplicate_add<int,IntFunc,IntCmp>(2,&mk_int,int_less);
  if ( !__n || ( __n ==  3 ) ) test_case_construct_empty<int,IntFunc,IntCmp>(3,&mk_int,int_less);
  if ( !__n || ( __n ==  4 ) ) test_case_contains_simple<int,IntFunc,IntCmp>(4,&mk_int,int_less);
  if ( !__n || ( __n ==  5 ) ) test_case_contains_empty<int,IntFunc,IntCmp>(5,&mk_int,int_less);
  if ( !__n || ( __n ==  6 ) ) test_case_find_closest_balanced_largeK<int,IntFunc,IntCmp,IntDist>(6,&mk_int,int_less,int_dist);
  if ( !__n || ( __n ==  7 ) ) test_case_find_closest_balanced_smallK<int,IntFunc,IntCmp,IntDist>(7,&mk_int,int_less,int_dist);
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_unbalanced_largeK<int,IntFunc,IntCmp,IntDist>(8,&mk_int,int_less,int_dist);
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest_unbalanced_smallK<int,IntFunc,IntCmp,IntDist>(9,&mk_int,int_less,int_dist);
  if ( !__n || ( __n == 10 ) ) test_case_to_vector_balanced<int,IntFunc,IntCmp>(10,&mk_int,int_less);
  if ( !__n || ( __n == 11 ) ) test_case_to_vector_unbalanced<int,IntFunc,IntCmp>(11,&mk_int,int_less);
  if ( !__n || ( __n == 12 ) ) test_case_to_vector_funky<int,IntFunc,IntCmp>(12,&mk_int,int_less);
  if ( !__n || ( __n == 13 ) ) test_case_copy_v1<int,IntFunc,IntCmp>(13,&mk_int,int_less);
  if ( !__n || ( __n == 14 ) ) test_case_copy_v2<int,IntFunc,IntCmp>(14,&mk_int,int_less);
  if ( !__n || ( __n == 15 ) ) test_case_copy_empty<int,IntFunc,IntCmp>(15,&mk_int,int_less);
  if ( !__n || ( __n == 16 ) ) test_case_assignment<int,IntFunc,IntCmp>(16,&mk_int,int_less);
  if ( !__n || ( __n == 17 ) ) test_case_assignment_to_empty<int,IntFunc,IntCmp>(17,&mk_int,int_less);
  if ( !__n || ( __n == 18 ) ) test_case_assignment_from_empty<int,IntFunc,IntCmp>(18,&mk_int,int_less);
  if ( !__n || ( __n == 19 ) ) test_case_assignment_empty<int,IntFunc,IntCmp>(19,&mk_int,int_less);
  if ( !__n || ( __n == 20 ) ) test_case_assignment_self<int,IntFunc,IntCmp>(20,&mk_int,int_less);
  if ( !__n || ( __n == 21 ) ) test_case_general<int,IntFunc,IntCmp>(21,&mk_int,int_less);
  if ( !__n || ( __n == 22 ) ) test_case_one_node<int,IntFunc,IntCmp,IntDist>(22,&mk_int,int_less,int_dist);
  if ( !__n || ( __n == 23 ) ) test_case_two_nodes<int,IntFunc,IntCmp,IntDist>(23,&mk_int,int_less,int_dist);
  if ( !__n || ( __n == 24 ) ) test_case_three_nodes<int,IntFunc,IntCmp,IntDist>(24,&mk_int,int_less,int_dist);
  if ( !__n || ( __n == 25 ) ) test_case_four_nodes<int,IntFunc,IntCmp,IntDist>(25,&mk_int,int_less,int_dist);

  std::printf("\n");
  return __failed;
}
// clang-format on
