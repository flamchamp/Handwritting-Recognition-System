//========================================================================
// vector-int-directed-test.cc
//========================================================================
// This file contains directed tests for Vector<int>

#include "Vector.h"
#include "vector-directed-test.h"

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
// Distance functor
//------------------------------------------------------------------------
class DistanceInt {
 public:
  int operator()( int a, int b )
  {
    if ( a < b ) {
      return b - a;
    }
    else {
      return a - b;
    }
  }
};

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
  typedef int (*IntDist)( int, int );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( !__n || ( __n ==  1 ) ) test_case_simple_push_back<int>(1,&mk_int);
  if ( !__n || ( __n ==  2 ) ) test_case_at_out_of_bound<int>(2,&mk_int);
  if ( !__n || ( __n ==  3 ) ) test_case_construct<int>(3,&mk_int);
  if ( !__n || ( __n ==  4 ) ) test_case_construct_empty<int>(4,&mk_int);
  if ( !__n || ( __n ==  5 ) ) test_case_contains_simple<int>(5,&mk_int);
  if ( !__n || ( __n ==  6 ) ) test_case_contains_empty<int>(6,&mk_int);
  // three different ways to pass in a distance function: function pointer, functor, and lambda
  if ( !__n || ( __n ==  7 ) ) test_case_find_closest_linear<int,IntFunc,IntDist>(7,&mk_int,int_dist);
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_linear<int,IntFunc,DistanceInt>(8,&mk_int,DistanceInt());
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest_linear<int,IntFunc,IntDist>(9,&mk_int,
                                 []( int a, int b ){ return ( a < b ) ? ( b - a ) : ( a - b ); } );
  if ( !__n || ( __n == 10 ) ) test_case_find_closest_linear_empty<int,IntFunc,IntDist>(10,&mk_int,int_dist);
  // three different ways to pass in a compare function: function pointer, functor, and lambda
  if ( !__n || ( __n == 11 ) ) test_case_sort_simple<int,IntFunc,IntCmp>(11,&mk_int,int_less);
  if ( !__n || ( __n == 12 ) ) test_case_sort_simple<int,IntFunc,IntLess>(12,&mk_int,IntLess());
  if ( !__n || ( __n == 13 ) ) test_case_sort_simple<int,IntFunc,IntCmp>(13,&mk_int,
                                                    []( int a, int b ){ return a < b; } );
  if ( !__n || ( __n == 14 ) ) test_case_find_closest_binary<int,IntFunc,IntDist,IntCmp>(14,&mk_int,4,int_dist,int_less);
  if ( !__n || ( __n == 15 ) ) test_case_find_closest_binary_empty<int,IntFunc,IntDist,IntCmp>(15,&mk_int,4,int_dist,int_less);
  if ( !__n || ( __n == 16 ) ) test_case_find_closest_binary_unsorted<int,IntFunc,IntDist,IntCmp>(16,&mk_int,4,int_dist,int_less);
  if ( !__n || ( __n == 17 ) ) test_case_subscript<int>(17,&mk_int);
  if ( !__n || ( __n == 18 ) ) test_case_copy_v1<int>(18,&mk_int);
  if ( !__n || ( __n == 19 ) ) test_case_copy_v2<int>(19,&mk_int);
  if ( !__n || ( __n == 20 ) ) test_case_copy_empty<int>(20,&mk_int);
  if ( !__n || ( __n == 21 ) ) test_case_assignment<int>(21,&mk_int);
  if ( !__n || ( __n == 22 ) ) test_case_assignment_to_empty<int>(22,&mk_int);
  if ( !__n || ( __n == 23 ) ) test_case_assignment_from_empty<int>(23,&mk_int);
  if ( !__n || ( __n == 24 ) ) test_case_assignment_empty<int>(24,&mk_int);
  if ( !__n || ( __n == 25 ) ) test_case_assignment_self<int>(25,&mk_int);
  if ( !__n || ( __n == 26 ) ) test_case_general<int,IntFunc,IntDist,IntCmp>(26,&mk_int,4,int_dist,int_less);

  std::printf("\n");
  return __failed;
}
// clang-format on
