//========================================================================
// vector-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for vector.

#include "Vector.h"
#include <cstdio>

int int_dist( int a, int b )
{
  if ( a < b ) {
    return b - a;
  }
  else {
    return a - b;
  }
}

bool int_less( int a, int b )
{
  return a < b;
}

int main()
{
  Vector<int> vec;
  vec.push_back( 19 );
  vec.push_back( 95 );
  vec.push_back( 4 );
  vec.push_back( 23 );
  vec.sort( int_less );

  std::printf( "Value stored at index 0 is %d\n", vec.at( 0 ) );
  std::printf( "Value stored at index 1 is %d\n", vec.at( 1 ) );
  std::printf( "Value stored at index 2 is %d\n", vec.at( 2 ) );
  std::printf( "Value stored at index 3 is %d\n", vec.at( 3 ) );
  int num = 20;
  std::printf( "find closest binary to %d is %d\n", num,
               vec.find_closest_binary( num, 5, int_dist, int_less ) );

  printf( "XXXXXXXXXXXXXXX TEST 2 XXXXXXXXXXXXXXX\n" );

  Vector<int> vec2;
  for ( int i = 0; i < 57; i++ ) {
    vec2.push_back( i );
  }
  vec2.print();
  int num2 = 3;
  // printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
  int bina = vec2.find_closest_binary( num2, 5, int_dist, int_less );
  // printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
  std::printf( "find closest binary to %d is %d\n", num2, bina );

  printf( "XXXXXXXXXXXXXXX TEST 3 XXXXXXXXXXXXXXX\n" );

  Vector<int> vec3;
  for ( int i = 10; i < 71; i = i + 10 ) {
    vec3.push_back( i );
  }
  vec3.print();
  int num3 = 71;
  printf( "val is %d\n", num3 );
  // printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
  int bina3 = vec3.find_closest_binary( num3, 4, int_dist, int_less );
  // printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
  std::printf( "find closest binary to %d is %d\n", num3, bina3 );

  printf( "XXXXXXXXXXXXXXX TEST 4 XXXXXXXXXXXXXXX\n" );

  Vector<int> vec4;
  for ( int i = 0; i < 5; i++ )
    vec4.push_back( 50 + i );

  for ( int i = 5; i < 10; i++ )
    vec4.push_back( 100 + i );

  for ( int i = 10; i < 20; i++ )
    vec4.push_back( 150 + i );

  for ( int i = 20; i < 30; i++ )
    vec4.push_back( 200 + i );

  vec4.print();

  int num4  = 125;
  int bina4 = vec4.find_closest_binary( num4, 4, int_dist, int_less );
  std::printf( "find closest binary to %d is %d\n", num4, bina4 );
  return 0;
}
