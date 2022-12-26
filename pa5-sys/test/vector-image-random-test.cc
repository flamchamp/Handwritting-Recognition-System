//========================================================================
// vector-image-random-test.cc
//========================================================================
// This file contains random tests for Vector<Image>

#include "Image.h"
#include "Vector.h"
#include "vector-random-test.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// Object Creation Functions
//------------------------------------------------------------------------
// All of the generic test functions are templated by an "object
// creation" function which should take as a parameter an integer and
// return a newly created object. For an Image, the object creation
// function can set each pixel value based on the given integer.

Image mk_1x1( int value )
{
  int         data[] = {value};
  Vector<int> vec( data, 1 );
  return Image( vec, 1, 1 );
}

Image mk_3x3( int value )
{
  int data[] = {value + 2, value + 1, value + 2, value + 1, value,
                value + 1, value + 2, value + 1, value + 2};

  Vector<int> vec( data, 9 );
  return Image( vec, 3, 3 );
}

//------------------------------------------------------------------------
// Image distance free function
//------------------------------------------------------------------------
int distance_euclidean( const Image& a, const Image& b )
{
  return a.distance( b );
}

//------------------------------------------------------------------------
// Image intensity free function
//------------------------------------------------------------------------
bool less_intensity( const Image& a, const Image& b )
{
  return a.get_intensity() < b.get_intensity();
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  typedef Image (ImgFunc)(int);
  typedef bool (*ImgCmp)( const Image&, const Image& );
  typedef int (*ImgDist)( const Image&, const Image& );

  std::printf("\n Testing with 1x1 images \n");

  if ( !__n || ( __n ==  1 ) ) test_case_push_back_random<Image>(1,&mk_1x1);
  if ( !__n || ( __n ==  2 ) ) test_case_copy_random<Image>(2,&mk_1x1);
  if ( !__n || ( __n ==  3 ) ) test_case_construct_random<Image>(3,&mk_1x1);
  if ( !__n || ( __n ==  4 ) ) test_case_find_closest_linear_random<Image,ImgFunc,ImgDist>(4,&mk_1x1,distance_euclidean);
  if ( !__n || ( __n ==  5 ) ) test_case_general_random<Image,ImgFunc,ImgDist,ImgCmp>(5,&mk_1x1,4,distance_euclidean,less_intensity);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n ==  6 ) ) test_case_push_back_random<Image>(6,&mk_3x3);
  if ( !__n || ( __n ==  7 ) ) test_case_copy_random<Image>(7,&mk_3x3);
  if ( !__n || ( __n ==  8 ) ) test_case_construct_random<Image>(8,&mk_3x3);
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest_linear_random<Image,ImgFunc,ImgDist>(9,&mk_3x3,distance_euclidean);
  if ( !__n || ( __n == 10 ) ) test_case_general_random<Image,ImgFunc,ImgDist,ImgCmp>(10,&mk_3x3,4,distance_euclidean,less_intensity);

  std::printf("\n");
  return __failed;
}
// clang-format on
