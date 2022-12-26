//========================================================================
// table-int-directed-test.cc
//========================================================================
// This file contains directed tests for Table<int>

#include "Table.h"
#include "table-directed-test.h"

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
  int operator()( int a, int b ) const
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
// Hash free function
//------------------------------------------------------------------------
int int_hash( int a )
{
  return a * ( INT_MAX / 255 );
}

//------------------------------------------------------------------------
// Hash functor
//------------------------------------------------------------------------
class HashInt {
 public:
  int operator()( int a ) const
  {
    return a * ( INT_MAX / 255 );
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
  typedef int (*IntDist)( int, int );
  typedef int (*IntHash)( int );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( !__n || ( __n ==  1 ) ) test_case_simple_add<int,IntFunc,IntHash>(1,&mk_int,int_hash);
  if ( !__n || ( __n ==  2 ) ) test_case_2bin_add<int,IntFunc,IntHash>(2,&mk_int,int_hash);
  if ( !__n || ( __n ==  3 ) ) test_case_duplicate_add<int,IntFunc,IntHash>(3,&mk_int,int_hash);
  if ( !__n || ( __n ==  4 ) ) test_case_empty_bin<int,IntFunc,IntHash>(4,&mk_int,int_hash);
  if ( !__n || ( __n ==  5 ) ) test_case_construct_empty<int,IntFunc,IntHash>(5,&mk_int,int_hash);
  if ( !__n || ( __n ==  6 ) ) test_case_contains_simple<int,IntFunc,IntHash>(6,&mk_int,int_hash);
  if ( !__n || ( __n ==  7 ) ) test_case_contains_empty<int,IntFunc,IntHash>(7,&mk_int,int_hash);
  // three ways to pass in the callables: free function, functor, and lambda
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest<int,IntFunc,IntDist,IntHash>(8,&mk_int,int_dist,int_hash);
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest<int,IntFunc,DistanceInt,HashInt>(9,&mk_int,DistanceInt(),HashInt());
  if ( !__n || ( __n == 10 ) ) test_case_find_closest<int,IntFunc,IntDist,IntHash>(10,&mk_int,
                                                     []( int a, int b ){ return ( a < b ) ? ( b - a ) : ( a - b ); },
                                                     []( int a ){ return a * ( INT_MAX / 255 ); } );
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_empty<int,IntFunc,IntDist,IntHash>(8,&mk_int,int_dist,int_hash);
  if ( !__n || ( __n == 11 ) ) test_case_to_vector<int,IntFunc,IntHash>(11,&mk_int,int_hash);
  if ( !__n || ( __n == 12 ) ) test_case_to_vector_rehash<int,IntFunc,IntHash>(12,&mk_int,int_hash);
  if ( !__n || ( __n == 13 ) ) test_case_to_vector_2rehash<int,IntFunc,IntHash>(13,&mk_int,int_hash);
  if ( !__n || ( __n == 14 ) ) test_case_copy_v1<int,IntFunc,IntHash>(14,&mk_int,int_hash);
  if ( !__n || ( __n == 15 ) ) test_case_copy_v2<int,IntFunc,IntHash>(15,&mk_int,int_hash);
  if ( !__n || ( __n == 16 ) ) test_case_copy_empty<int,IntFunc,IntHash>(16,&mk_int,int_hash);
  if ( !__n || ( __n == 17 ) ) test_case_assignment<int,IntFunc,IntHash>(17,&mk_int,int_hash);
  if ( !__n || ( __n == 18 ) ) test_case_assignment_diff_nbins<int,IntFunc,IntHash>(18,&mk_int,int_hash);
  if ( !__n || ( __n == 19 ) ) test_case_assignment_to_empty<int,IntFunc,IntHash>(19,&mk_int,int_hash);
  if ( !__n || ( __n == 20 ) ) test_case_assignment_from_empty<int,IntFunc,IntHash>(20,&mk_int,int_hash);
  if ( !__n || ( __n == 21 ) ) test_case_assignment_empty<int,IntFunc,IntHash>(21,&mk_int,int_hash);
  if ( !__n || ( __n == 22 ) ) test_case_assignment_self<int,IntFunc,IntHash>(22,&mk_int,int_hash);
  if ( !__n || ( __n == 23 ) ) test_case_general<int,IntFunc,IntHash>(23,&mk_int,int_hash);

  std::printf("\n");
  return __failed;
}
// clang-format on
