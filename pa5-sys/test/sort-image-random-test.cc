//========================================================================
// sort-image-random-tests.c
//========================================================================
// This file contains the tests for the sort function with images

#include "Image.h"
#include "sort-random-test.h"
#include "sort.h"

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

  typedef Image (ImgFunc)(int);
  typedef bool (*ImgCmp)( const Image&, const Image& );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  std::printf("\n Testing with 1x1 images \n");

  if ( !__n || ( __n == 1 ) ) test_case_random<Image,ImgFunc,ImgCmp>(1,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 2 ) ) test_case_random_few_unique<Image,ImgFunc,ImgCmp>(2,&mk_1x1,less_intensity);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n == 3 ) ) test_case_random<Image,ImgFunc,ImgCmp>(3,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 4 ) ) test_case_random_few_unique<Image,ImgFunc,ImgCmp>(4,&mk_3x3,less_intensity);

  std::printf("\n");
  return __failed;
}
// clang-format on
