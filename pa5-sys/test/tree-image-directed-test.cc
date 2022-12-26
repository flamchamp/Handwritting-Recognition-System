//========================================================================
// tree-image-directed-test.cc
//========================================================================
// This file contains directed tests for Tree<Image>

#include "Image.h"
#include "Tree.h"
#include "tree-directed-test.h"

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
  // printf("intensity of a is %d\n", a.get_intensity());
  // printf("intensity of b is %d\n", b.get_intensity());
  // printf("dimensions of a are %d and %d\n", a.get_ncols(), a.get_nrows());
  // printf("dimensions of b are %d and %d\n", b.get_ncols(), b.get_nrows());
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
  bool operator()( const Image& a, const Image& b ) const
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
  typedef int (*ImgDist)( const Image&, const Image& );

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  std::printf("\n Testing with 1x1 images \n");

  if ( !__n || ( __n ==  1 ) ) test_case_simple_add<Image,ImgFunc,ImgCmp>(1,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  2 ) ) test_case_duplicate_add<Image,ImgFunc,ImgCmp>(2,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  3 ) ) test_case_construct_empty<Image,ImgFunc,ImgCmp>(3,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  4 ) ) test_case_contains_simple<Image,ImgFunc,ImgCmp>(4,&mk_1x1,less_intensity);
  if ( !__n || ( __n ==  5 ) ) test_case_contains_empty<Image,ImgFunc,ImgCmp>(5,&mk_1x1,less_intensity);
  // three different ways to pass in the callables: free funtion, functor, and lambda
  if ( !__n || ( __n ==  6 ) ) test_case_find_closest_balanced_largeK<Image,ImgFunc,ImgCmp,ImgDist>(6,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n ==  7 ) ) test_case_find_closest_balanced_largeK<Image,ImgFunc,LessIntensity,DistanceEuclidean>(7,&mk_1x1,LessIntensity(),DistanceEuclidean());
  if ( !__n || ( __n ==  8 ) ) test_case_find_closest_balanced_largeK<Image,ImgFunc,ImgCmp,ImgDist>(8,&mk_1x1,
                                                                     []( const Image& a, const Image& b ){ return a.get_intensity() < b.get_intensity(); },
                                                                     []( const Image& a, const Image& b ){ return a.distance(b); } );
  if ( !__n || ( __n ==  9 ) ) test_case_find_closest_balanced_smallK<Image,ImgFunc,ImgCmp,ImgDist>(9,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 10 ) ) test_case_find_closest_unbalanced_largeK<Image,ImgFunc,ImgCmp,ImgDist>(10,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 11 ) ) test_case_find_closest_unbalanced_smallK<Image,ImgFunc,ImgCmp,ImgDist>(11,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 12 ) ) test_case_to_vector_balanced<Image,ImgFunc,ImgCmp>(12,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 13 ) ) test_case_to_vector_unbalanced<Image,ImgFunc,ImgCmp>(13,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 14 ) ) test_case_to_vector_funky<Image,ImgFunc,ImgCmp>(14,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 15 ) ) test_case_copy_v1<Image,ImgFunc,ImgCmp>(15,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 16 ) ) test_case_copy_v2<Image,ImgFunc,ImgCmp>(16,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 17 ) ) test_case_copy_empty<Image,ImgFunc,ImgCmp>(17,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 18 ) ) test_case_assignment<Image,ImgFunc,ImgCmp>(18,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 19 ) ) test_case_assignment_to_empty<Image,ImgFunc,ImgCmp>(19,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 20 ) ) test_case_assignment_from_empty<Image,ImgFunc,ImgCmp>(20,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 21 ) ) test_case_assignment_empty<Image,ImgFunc,ImgCmp>(21,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 22 ) ) test_case_assignment_self<Image,ImgFunc,ImgCmp>(22,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 23 ) ) test_case_general<Image,ImgFunc,ImgCmp>(23,&mk_1x1,less_intensity);
  if ( !__n || ( __n == 24 ) ) test_case_one_node<Image,ImgFunc,ImgCmp,ImgDist>(24,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 25 ) ) test_case_two_nodes<Image,ImgFunc,ImgCmp,ImgDist>(25,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 26 ) ) test_case_three_nodes<Image,ImgFunc,ImgCmp,ImgDist>(26,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 27 ) ) test_case_four_nodes<Image,ImgFunc,ImgCmp,ImgDist>(27,&mk_1x1,less_intensity,distance_euclidean);

  std::printf("\n\n Testing with 3x3 images \n");

  if ( !__n || ( __n == 28 ) ) test_case_simple_add<Image,ImgFunc,ImgCmp>(28,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 29 ) ) test_case_duplicate_add<Image,ImgFunc,ImgCmp>(29,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 30 ) ) test_case_construct_empty<Image,ImgFunc,ImgCmp>(30,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 31 ) ) test_case_contains_simple<Image,ImgFunc,ImgCmp>(31,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 32 ) ) test_case_contains_empty<Image,ImgFunc,ImgCmp>(32,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 33 ) ) test_case_find_closest_balanced_largeK<Image,ImgFunc,ImgCmp,ImgDist>(33,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 34 ) ) test_case_find_closest_balanced_smallK<Image,ImgFunc,ImgCmp,ImgDist>(34,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 35 ) ) test_case_find_closest_unbalanced_largeK<Image,ImgFunc,ImgCmp,ImgDist>(35,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 36 ) ) test_case_find_closest_unbalanced_smallK<Image,ImgFunc,ImgCmp,ImgDist>(36,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 37 ) ) test_case_to_vector_balanced<Image,ImgFunc,ImgCmp>(37,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 38 ) ) test_case_to_vector_unbalanced<Image,ImgFunc,ImgCmp>(38,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 39 ) ) test_case_to_vector_funky<Image,ImgFunc,ImgCmp>(39,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 40 ) ) test_case_copy_v1<Image,ImgFunc,ImgCmp>(40,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 41 ) ) test_case_copy_v2<Image,ImgFunc,ImgCmp>(41,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 42 ) ) test_case_copy_empty<Image,ImgFunc,ImgCmp>(42,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 43 ) ) test_case_assignment<Image,ImgFunc,ImgCmp>(43,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 44 ) ) test_case_assignment_to_empty<Image,ImgFunc,ImgCmp>(44,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 45 ) ) test_case_assignment_from_empty<Image,ImgFunc,ImgCmp>(45,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 46 ) ) test_case_assignment_empty<Image,ImgFunc,ImgCmp>(46,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 47 ) ) test_case_assignment_self<Image,ImgFunc,ImgCmp>(47,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 48 ) ) test_case_general<Image,ImgFunc,ImgCmp>(48,&mk_3x3,less_intensity);
  if ( !__n || ( __n == 49 ) ) test_case_one_node<Image,ImgFunc,ImgCmp,ImgDist>(49,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 50 ) ) test_case_two_nodes<Image,ImgFunc,ImgCmp,ImgDist>(50,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 51 ) ) test_case_three_nodes<Image,ImgFunc,ImgCmp,ImgDist>(51,&mk_1x1,less_intensity,distance_euclidean);
  if ( !__n || ( __n == 52 ) ) test_case_four_nodes<Image,ImgFunc,ImgCmp,ImgDist>(52,&mk_1x1,less_intensity,distance_euclidean);

  std::printf("\n");
  return __failed;
}
// clang-format on
