//========================================================================
// table-image-random-test.cc
//========================================================================
// This file contains random tests for Table<Image>

#include "Image.h"
#include "Table.h"
#include "table-random-test.h"

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
// Image hash intensity
//------------------------------------------------------------------------

int hash_intensity( const Image& a )
{
  return a.get_intensity();
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  typedef Image (ImgFunc)(int);
  typedef int (*ImgHash)( const Image& );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  std::printf("\n Testing with 1x1 images \n");

  if ( !__n || ( __n ==  1 ) ) test_case_add_random<Image,ImgFunc,ImgHash>(1,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  2 ) ) test_case_copy_random<Image,ImgFunc,ImgHash>(2,&mk_1x1,hash_intensity);

  std::printf("\n Testing with 3x3 images \n");

  if ( !__n || ( __n ==  3 ) ) test_case_add_random<Image,ImgFunc,ImgHash>(3,&mk_3x3,hash_intensity);
  if ( !__n || ( __n ==  4 ) ) test_case_copy_random<Image,ImgFunc,ImgHash>(4,&mk_3x3,hash_intensity);

  std::printf("\n");
  return __failed;
}
// clang-format on
