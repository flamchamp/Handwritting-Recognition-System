//========================================================================
// vector-int-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for VectorInt.

#include "VectorInt.h"
#include <stdio.h>

int main()
{
  VectorInt vec;
  vec.push_back( 19 );
  vec.push_back( 95 );
  vec.push_back( 4 );
  vec.push_back( 23 );
  vec.push_back( 7 );
  vec.push_back( 18 );
  vec.push_back( 20 );
  vec.push_back( 21 );
  vec.push_back( 22 );
  vec.push_back( 24 );
  vec.sort();

  printf( "Value stored at index 0 is %d\n", vec.at( 0 ) );
  printf( "Value stored at index 1 is %d\n", vec.at( 1 ) );
  printf( "Value stored at index 2 is %d\n", vec.at( 2 ) );
  printf( "Value stored at index 3 is %d\n", vec.at( 3 ) );
  printf( "Value stored at index 4 is %d\n", vec.at( 4 ) );
  printf( "Value stored at index 5 is %d\n", vec.at( 5 ) );
  printf( "Value stored at index 6 is %d\n", vec.at( 6 ) );
  printf( "Value stored at index 7 is %d\n", vec.at( 7 ) );
  printf( "Value stored at index 8 is %d\n", vec.at( 8 ) );
  printf( "Value stored at index 9 is %d\n", vec.at( 9 ) );
  vec.print();
  int v_find_closest = 95;
  int range_k        = 3;
  int closest_idx    = vec.find_closest_binary( v_find_closest, range_k );
  int v_at_idx       = vec.at( closest_idx );
  printf( "smallest binary index within %d of %d is %d\n", range_k,
          v_find_closest, closest_idx );
  printf( "the value closest to %d is %d\n", v_find_closest, v_at_idx );

  printf( "\n\n" );
  printf( "Vectore 2 test \n" );
  VectorInt vec2;
  vec2.push_back( 1 );
  vec2.push_back( 2 );
  vec2.push_back( 3 );
  vec2.push_back( 4 );
  vec2.push_back( 5 );
  vec2.push_back( 6 );
  vec2.push_back( 7 );
  vec2.push_back( 8 );
  vec2.push_back( 9 );
  vec2.push_back( 10 );
  vec2.push_back( 11 );
  vec2.push_back( 12 );
  vec2.push_back( 13 );
  vec2.push_back( 14 );
  // vec2.push_back( 15 );
  vec2.push_back( 16 );
  vec.sort();

  printf( "size of vec2 is %d\n", vec2.size() );
  vec2.print();
  int v_find_closest2 = 15;
  int range_k2        = 10;
  int closest_idx2    = vec2.find_closest_binary( v_find_closest2, range_k2 );
  int v_at_idx2       = vec2.at( closest_idx2 );
  printf( "smallest binary index within %d of %d is %d\n", range_k2,
          v_find_closest2, closest_idx2 );
  printf( "the value closest to %d is %d\n", v_find_closest2, v_at_idx2 );

  return 0;
}
