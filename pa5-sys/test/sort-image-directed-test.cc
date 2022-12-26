//========================================================================
// sort-image-directed-tests.c
//========================================================================
// This file contains the tests for the sort function with images

#include "Image.h"
#include "ece2400-stdlib.h"
#include "sort-directed-test.h"
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
// Image intensity functor
//------------------------------------------------------------------------
class LessIntensity {
 public:
  bool operator()( const Image& a, const Image& b )
  {
    return a.get_intensity() < b.get_intensity();
  }
};

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

  if ( !__n || ( __n ==  1 ) ) test_case_helper<Image,ImgFunc,ImgCmp>(1,&mk_1x1,less_intensity);
  // three different ways to pass in a compare function: function pointer, functor, and lambda
  if ( !__n || ( __n ==  2 ) ) test_case_five_element<Image,ImgFunc,ImgCmp>(2,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  3 ) ) test_case_five_element<Image,ImgFunc,LessIntensity>(2,&mk_1x1,LessIntensity());
  if ( !__n || ( __n ==  4 ) ) test_case_five_element<Image,ImgFunc,ImgCmp>(2,&mk_1x1,
                                 []( const Image& a, const Image& b ){ return a.get_intensity() < b.get_intensity(); } );
  if ( !__n || ( __n ==  5 ) ) test_case_empty<Image,ImgFunc,ImgCmp>(3,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  6 ) ) test_case_one_element<Image,ImgFunc,ImgCmp>(4,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  7 ) ) test_case_two_elements<Image,ImgFunc,ImgCmp>(5,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  8 ) ) test_case_three_elements<Image,ImgFunc,ImgCmp>(6,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  9 ) ) test_case_even_size_array<Image,ImgFunc,ImgCmp>(7,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 10 ) ) test_case_odd_size_array<Image,ImgFunc,ImgCmp>(8,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 11 ) ) test_case_almost_sorted<Image,ImgFunc,ImgCmp>(9,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 12 ) ) test_case_sorted_ascending<Image,ImgFunc,ImgCmp>(10,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 13 ) ) test_case_sorted_descending<Image,ImgFunc,ImgCmp>(11,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 14 ) ) test_case_few_unique<Image,ImgFunc,ImgCmp>(12,&mk_1x1,less_intensity);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n == 15 ) ) test_case_helper<Image,ImgFunc,ImgCmp>(13,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 16 ) ) test_case_five_element<Image,ImgFunc,ImgCmp>(14,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 17 ) ) test_case_empty<Image,ImgFunc,ImgCmp>(15,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 18 ) ) test_case_one_element<Image,ImgFunc,ImgCmp>(16,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 19 ) ) test_case_two_elements<Image,ImgFunc,ImgCmp>(17,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 20 ) ) test_case_three_elements<Image,ImgFunc,ImgCmp>(18,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 21 ) ) test_case_even_size_array<Image,ImgFunc,ImgCmp>(19,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 22 ) ) test_case_odd_size_array<Image,ImgFunc,ImgCmp>(20,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 23 ) ) test_case_almost_sorted<Image,ImgFunc,ImgCmp>(21,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 24 ) ) test_case_sorted_ascending<Image,ImgFunc,ImgCmp>(22,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 25 ) ) test_case_sorted_descending<Image,ImgFunc,ImgCmp>(23,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 26 ) ) test_case_few_unique<Image,ImgFunc,ImgCmp>(24,&mk_3x3,less_intensity);

  std::printf("\n");

  return __failed;
}
// clang-format on
