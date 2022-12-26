//========================================================================
// sort-image-directed-test.cc
//========================================================================

#include "Image.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"
#include <cstring>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------
// Simple test case for sort_image.

void test_case_1_simple()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 )};

  sort_image( images, 2 );

  ECE2400_CHECK_TRUE( images[0] == Image( VectorInt( data[1], 8 ), 2, 4 ) );
  ECE2400_CHECK_TRUE( images[1] == Image( VectorInt( data[0], 8 ), 2, 4 ) );
}

//------------------------------------------------------------------------
// test_case_2_empty
//------------------------------------------------------------------------
// A simple test case that tests sorting an empty array.

void test_case_2_empty()
{
  std::printf( "\n%s\n", __func__ );

  Image* images = nullptr;

  sort_image( images, 0 );
}

//------------------------------------------------------------------------
// test_case_3_one_element
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_3_one_element()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 2, 3, 4, 5, 6, 7, 8}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 )};

  sort_image( images, 1 );

  ECE2400_CHECK_TRUE( images[0] == Image( VectorInt( data[0], 8 ), 2, 4 ) );
}

//------------------------------------------------------------------------
// test_case_4_sorted
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_4_sorted()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 1, 1, 1, 1, 1, 1, 1},   // intensity = 8
                   {2, 2, 2, 2, 2, 2, 2, 2},   // intensity = 16
                   {3, 3, 3, 3, 3, 3, 3, 3},   // intensity = 24
                   {4, 4, 4, 4, 4, 4, 4, 4},   // intensity = 32
                   {5, 5, 5, 5, 5, 5, 5, 5}};  // intensity = 40

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 4, 2 ),
                    Image( VectorInt( data[1], 8 ), 4, 2 ),
                    Image( VectorInt( data[2], 8 ), 4, 2 ),
                    Image( VectorInt( data[3], 8 ), 4, 2 ),
                    Image( VectorInt( data[4], 8 ), 4, 2 )};

  sort_image( images, 5 );

  ECE2400_CHECK_TRUE( images[0] == Image( VectorInt( data[0], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[1] == Image( VectorInt( data[1], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[2] == Image( VectorInt( data[2], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[3] == Image( VectorInt( data[3], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[4] == Image( VectorInt( data[4], 8 ), 4, 2 ) );
}

//------------------------------------------------------------------------
// test_case_5_reversed
//------------------------------------------------------------------------
// A simple test case that tests sorting a one-element array.

void test_case_5_reversed()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{5, 5, 5, 5, 5, 5, 5, 5},
                   {4, 4, 4, 4, 4, 4, 4, 4},
                   {3, 3, 3, 3, 3, 3, 3, 3},
                   {2, 2, 2, 2, 2, 2, 2, 2},
                   {1, 1, 1, 1, 1, 1, 1, 1}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 4, 2 ),
                    Image( VectorInt( data[1], 8 ), 4, 2 ),
                    Image( VectorInt( data[2], 8 ), 4, 2 ),
                    Image( VectorInt( data[3], 8 ), 4, 2 ),
                    Image( VectorInt( data[4], 8 ), 4, 2 )};

  sort_image( images, 5 );

  ECE2400_CHECK_TRUE( images[0] == Image( VectorInt( data[4], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[1] == Image( VectorInt( data[3], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[2] == Image( VectorInt( data[2], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[3] == Image( VectorInt( data[1], 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( images[4] == Image( VectorInt( data[0], 8 ), 4, 2 ) );
}

//'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
// Add more test cases here
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_simple();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_empty();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_one_element();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_sorted();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_reversed();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  return __failed;
}
// clang-format on
