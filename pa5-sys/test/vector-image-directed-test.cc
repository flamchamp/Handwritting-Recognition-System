//========================================================================
// vector-image-directed-test.cc
//========================================================================
// This file contains directed tests for Vector<Image>

#include "Image.h"
#include "Vector.h"
#include "vector-directed-test.h"

#include <cstdio>
#include <cstdlib>
#include <functional>

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
// Image distance functor
//------------------------------------------------------------------------
class DistanceEuclidean {
 public:
  int operator()( const Image& a, const Image& b ) const
  {
    return a.distance( b );
  }
};

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
// test_case_21_find_closest_different
//------------------------------------------------------------------------
// a case where sorting by intensity causes find_closest_binary to
// produce a different result from find_closest_linear

void test_case_50_find_closest_different()
{
  std::printf( "\n%s\n", __func__ );

  int data[][9] = {
      {2, 2, 2, 0, 0, 0, 0, 0, 0},    {0, 0, 4, 0, 0, 4, 0, 0, 4},
      {0, 0, 0, 0, 0, 0, 6, 6, 6},    {8, 0, 0, 8, 0, 0, 8, 0, 0},
      {10, 0, 0, 0, 10, 0, 0, 0, 10}, {0, 0, 12, 0, 12, 0, 12, 0, 0},
      {0, 0, 0, 0, 0, 0, 14, 14, 14}, {16, 0, 0, 16, 0, 0, 16, 0, 0}};

  // An array of images
  Image images[] = {Image( Vector<int>( data[0], 9 ), 3, 3 ),
                    Image( Vector<int>( data[1], 9 ), 3, 3 ),
                    Image( Vector<int>( data[2], 9 ), 3, 3 ),
                    Image( Vector<int>( data[3], 9 ), 3, 3 ),
                    Image( Vector<int>( data[4], 9 ), 3, 3 ),
                    Image( Vector<int>( data[5], 9 ), 3, 3 ),
                    Image( Vector<int>( data[6], 9 ), 3, 3 ),
                    Image( Vector<int>( data[7], 9 ), 3, 3 )};

  // Construct a vector of images
  Vector<Image> vec( images, 8 );

  int   test_img[9] = {13, 13, 13, 0, 0, 0, 0, 0, 0};
  Image test        = Image( Vector<int>( test_img, 9 ), 3, 3 );

  ECE2400_CHECK_TRUE( vec.find_closest_linear( test, distance_euclidean ) ==
                      images[0] );

  vec.sort( less_intensity );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( test, 4, distance_euclidean,
                                               less_intensity ) == images[3] );
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

  if ( !__n || ( __n ==  1 ) ) test_case_simple_push_back<Image>(1,&mk_1x1);
  if ( !__n || ( __n ==  2 ) ) test_case_at_out_of_bound<Image>(2,&mk_1x1);
  if ( !__n || ( __n ==  3 ) ) test_case_construct<Image>(3,&mk_1x1);
  if ( !__n || ( __n ==  4 ) ) test_case_construct_empty<Image>(4,&mk_1x1);
  if ( !__n || ( __n ==  5 ) ) test_case_contains_simple<Image>(5,&mk_1x1);
  if ( !__n || ( __n ==  6 ) ) test_case_contains_empty<Image>(6,&mk_1x1);
  // four different ways to pass in a distance function: function pointer, functor, lambda, and member function wrapper
  if ( !__n || ( __n ==  7 ) ) test_case_find_closest_linear<Image,ImgFunc,ImgDist>(7,&mk_1x1,distance_euclidean);
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_linear<Image,ImgFunc,DistanceEuclidean>(8,&mk_1x1,DistanceEuclidean());
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest_linear<Image,ImgFunc,ImgDist>(9,&mk_1x1,
                                                     []( const Image& a, const Image& b ){ return a.distance( b ); });
  if ( !__n || ( __n == 10 ) ) test_case_find_closest_linear<Image,ImgFunc,std::function<int( const Image&, const Image& )>>(10,&mk_1x1,
                                                                                                    std::mem_fn(&Image::distance));
  if ( !__n || ( __n == 11 ) ) test_case_find_closest_linear_empty<Image,ImgFunc,ImgDist>(11,&mk_1x1,distance_euclidean);
  // three different ways to pass in a compare function: function pointer, functor, and lambda
  if ( !__n || ( __n == 12 ) ) test_case_sort_simple<Image,ImgFunc,ImgCmp>(12,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 13 ) ) test_case_sort_simple<Image,ImgFunc,LessIntensity>(13,&mk_1x1,LessIntensity());
  if ( !__n || ( __n == 14 ) ) test_case_sort_simple<Image,ImgFunc,ImgCmp>(14,&mk_1x1,
                               []( const Image& a, const Image& b ){ return a.get_intensity() < b.get_intensity(); } );
  if ( !__n || ( __n == 15 ) ) test_case_find_closest_binary<Image,ImgFunc,ImgDist,ImgCmp>(15,&mk_1x1,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 16 ) ) test_case_find_closest_binary_empty<Image,ImgFunc,ImgDist,ImgCmp>(16,&mk_1x1,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 17 ) ) test_case_find_closest_binary_unsorted<Image,ImgFunc,ImgDist,ImgCmp>(17,&mk_1x1,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 18 ) ) test_case_subscript<Image>(18,&mk_1x1);
  if ( !__n || ( __n == 19 ) ) test_case_copy_v1<Image>(19,&mk_1x1);
  if ( !__n || ( __n == 20 ) ) test_case_copy_v2<Image>(20,&mk_1x1);
  if ( !__n || ( __n == 21 ) ) test_case_copy_empty<Image>(21,&mk_1x1);
  if ( !__n || ( __n == 22 ) ) test_case_assignment<Image>(22,&mk_1x1);
  if ( !__n || ( __n == 23 ) ) test_case_assignment_to_empty<Image>(23,&mk_1x1);
  if ( !__n || ( __n == 24 ) ) test_case_assignment_from_empty<Image>(24,&mk_1x1);
  if ( !__n || ( __n == 25 ) ) test_case_assignment_empty<Image>(25,&mk_1x1);
  if ( !__n || ( __n == 26 ) ) test_case_assignment_self<Image>(26,&mk_1x1);
  if ( !__n || ( __n == 27 ) ) test_case_general<Image,ImgFunc,ImgDist,ImgCmp>(27,&mk_1x1,4,distance_euclidean,less_intensity);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n == 28 ) ) test_case_simple_push_back<Image>(28,&mk_3x3);
  if ( !__n || ( __n == 29 ) ) test_case_at_out_of_bound<Image>(29,&mk_3x3);
  if ( !__n || ( __n == 30 ) ) test_case_construct<Image>(30,&mk_3x3);
  if ( !__n || ( __n == 31 ) ) test_case_construct_empty<Image>(31,&mk_3x3);
  if ( !__n || ( __n == 32 ) ) test_case_contains_simple<Image>(32,&mk_3x3);
  if ( !__n || ( __n == 33 ) ) test_case_contains_empty<Image>(33,&mk_3x3);
  if ( !__n || ( __n == 34 ) ) test_case_find_closest_linear<Image,ImgFunc,ImgDist>(34,&mk_3x3,distance_euclidean);
  if ( !__n || ( __n == 35 ) ) test_case_find_closest_linear_empty<Image,ImgFunc,ImgDist>(35,&mk_3x3,distance_euclidean);
  if ( !__n || ( __n == 36 ) ) test_case_sort_simple<Image,ImgFunc,ImgCmp>(36,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 37 ) ) test_case_find_closest_binary<Image,ImgFunc,ImgDist,ImgCmp>(37,&mk_3x3,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 38 ) ) test_case_find_closest_binary_empty<Image,ImgFunc,ImgDist,ImgCmp>(38,&mk_3x3,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 39 ) ) test_case_find_closest_binary_unsorted<Image,ImgFunc,ImgDist,ImgCmp>(39,&mk_3x3,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 40 ) ) test_case_subscript<Image>(40,&mk_3x3);
  if ( !__n || ( __n == 41 ) ) test_case_copy_v1<Image>(41,&mk_3x3);
  if ( !__n || ( __n == 42 ) ) test_case_copy_v2<Image>(42,&mk_3x3);
  if ( !__n || ( __n == 43 ) ) test_case_copy_empty<Image>(43,&mk_3x3);
  if ( !__n || ( __n == 44 ) ) test_case_assignment<Image>(44,&mk_3x3);
  if ( !__n || ( __n == 45 ) ) test_case_assignment_to_empty<Image>(45,&mk_3x3);
  if ( !__n || ( __n == 46 ) ) test_case_assignment_from_empty<Image>(46,&mk_3x3);
  if ( !__n || ( __n == 47 ) ) test_case_assignment_empty<Image>(47,&mk_3x3);
  if ( !__n || ( __n == 48 ) ) test_case_assignment_self<Image>(48,&mk_3x3);
  if ( !__n || ( __n == 49 ) ) test_case_general<Image,ImgFunc,ImgDist,ImgCmp>(49,&mk_3x3,4,distance_euclidean,less_intensity);
  if ( !__n || ( __n == 50 ) ) test_case_50_find_closest_different();

  std::printf("\n");
  return __failed;
}
// clang-format on
