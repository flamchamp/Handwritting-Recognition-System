//========================================================================
// table-image-directed-test.cc
//========================================================================
// This file contains directed tests for Table<Image>

#include "Image.h"
#include "Table.h"
#include "table-directed-test.h"

#include <climits>
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
// Image distance functor
//------------------------------------------------------------------------
class DistanceEuclidean {
 public:
  int operator()( const Image& a, const Image& b )
  {
    return a.distance( b );
  }
};

//------------------------------------------------------------------------
// Image hash intensity free function
//------------------------------------------------------------------------

int hash_intensity( const Image& img )
{
  return img.get_intensity() *
         ( INT_MAX / ( 255 * img.get_nrows() * img.get_ncols() ) );
}

//------------------------------------------------------------------------
// Image hash intensity functor
//------------------------------------------------------------------------

class HashIntensity {
 public:
  int operator()( const Image& img ) const
  {
    return img.get_intensity() *
           ( INT_MAX / ( 255 * img.get_nrows() * img.get_ncols() ) );
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
  typedef int (*ImgDist)( const Image&, const Image& );
  typedef int (*ImgHash)( const Image& );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  std::printf("\n Testing with 1x1 images \n");

  if ( !__n || ( __n ==  1 ) ) test_case_simple_add<Image,ImgFunc,ImgHash>(1,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  2 ) ) test_case_2bin_add<Image,ImgFunc,ImgHash>(2,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  3 ) ) test_case_duplicate_add<Image,ImgFunc,ImgHash>(3,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  4 ) ) test_case_empty_bin<Image,ImgFunc,ImgHash>(4,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  5 ) ) test_case_construct_empty<Image,ImgFunc,ImgHash>(5,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  6 ) ) test_case_contains_simple<Image,ImgFunc,ImgHash>(6,&mk_1x1,hash_intensity);
  if ( !__n || ( __n ==  7 ) ) test_case_contains_empty<Image,ImgFunc,ImgHash>(7,&mk_1x1,hash_intensity);
  // three different ways to pass in the callables
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest<Image,ImgFunc,ImgDist,ImgHash>(8,&mk_1x1,distance_euclidean,hash_intensity);
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest<Image,ImgFunc,DistanceEuclidean,HashIntensity>(9,&mk_1x1,DistanceEuclidean(),
                                                                                                               HashIntensity());
  if ( !__n || ( __n ==  10 ) ) test_case_find_closest<Image,ImgFunc,ImgDist,ImgHash>(10,&mk_1x1,
                                                     []( const Image& a, const Image & b ){ return a.distance(b); },
                                                     []( const Image& img ){ return img.get_intensity(); } );
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_empty<Image,ImgFunc,ImgDist,ImgHash>(8,&mk_1x1,distance_euclidean,hash_intensity);
  if ( !__n || ( __n == 11 ) ) test_case_to_vector<Image,ImgFunc,ImgHash>(11,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 12 ) ) test_case_to_vector_rehash<Image,ImgFunc,ImgHash>(12,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 13 ) ) test_case_to_vector_2rehash<Image,ImgFunc,ImgHash>(13,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 14 ) ) test_case_copy_v1<Image,ImgFunc,ImgHash>(14,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 15 ) ) test_case_copy_v2<Image,ImgFunc,ImgHash>(15,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 16 ) ) test_case_copy_empty<Image,ImgFunc,ImgHash>(16,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 17 ) ) test_case_assignment<Image,ImgFunc,ImgHash>(17,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 18 ) ) test_case_assignment_diff_nbins<Image,ImgFunc,ImgHash>(18,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 19 ) ) test_case_assignment_to_empty<Image,ImgFunc,ImgHash>(19,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 20 ) ) test_case_assignment_from_empty<Image,ImgFunc,ImgHash>(20,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 21 ) ) test_case_assignment_empty<Image,ImgFunc,ImgHash>(21,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 22 ) ) test_case_assignment_self<Image,ImgFunc,ImgHash>(22,&mk_1x1,hash_intensity);
  if ( !__n || ( __n == 23 ) ) test_case_general<Image,ImgFunc,ImgHash>(23,&mk_1x1,hash_intensity);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n == 24 ) ) test_case_simple_add<Image,ImgFunc,ImgHash>(24,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 25 ) ) test_case_2bin_add<Image,ImgFunc,ImgHash>(25,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 26 ) ) test_case_duplicate_add<Image,ImgFunc,ImgHash>(26,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 27 ) ) test_case_empty_bin<Image,ImgFunc,ImgHash>(27,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 28 ) ) test_case_construct_empty<Image,ImgFunc,ImgHash>(28,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 29 ) ) test_case_contains_simple<Image,ImgFunc,ImgHash>(29,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 30 ) ) test_case_contains_empty<Image,ImgFunc,ImgHash>(30,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 31 ) ) test_case_find_closest<Image,ImgFunc,ImgDist,ImgHash>(31,&mk_3x3,distance_euclidean,hash_intensity);
  if ( !__n || ( __n == 31 ) ) test_case_find_closest_empty<Image,ImgFunc,ImgDist,ImgHash>(31,&mk_3x3,distance_euclidean,hash_intensity);
  if ( !__n || ( __n == 32 ) ) test_case_to_vector<Image,ImgFunc,ImgHash>(32,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 33 ) ) test_case_to_vector_rehash<Image,ImgFunc,ImgHash>(33,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 34 ) ) test_case_to_vector_2rehash<Image,ImgFunc,ImgHash>(34,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 35 ) ) test_case_copy_v1<Image,ImgFunc,ImgHash>(35,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 36 ) ) test_case_copy_v2<Image,ImgFunc,ImgHash>(36,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 37 ) ) test_case_copy_empty<Image,ImgFunc,ImgHash>(37,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 38 ) ) test_case_assignment<Image,ImgFunc,ImgHash>(38,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 39 ) ) test_case_assignment_diff_nbins<Image,ImgFunc,ImgHash>(39,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 40 ) ) test_case_assignment_to_empty<Image,ImgFunc,ImgHash>(40,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 41 ) ) test_case_assignment_from_empty<Image,ImgFunc,ImgHash>(41,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 42 ) ) test_case_assignment_empty<Image,ImgFunc,ImgHash>(42,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 43 ) ) test_case_assignment_self<Image,ImgFunc,ImgHash>(43,&mk_3x3,hash_intensity);
  if ( !__n || ( __n == 44 ) ) test_case_general<Image,ImgFunc,ImgHash>(44,&mk_3x3,hash_intensity);

  std::printf("\n");
  return __failed;
}
// clang-format on
