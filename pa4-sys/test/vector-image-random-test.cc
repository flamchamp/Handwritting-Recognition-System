//========================================================================
// vector-image-random-test.cc
//========================================================================
// This file contains random tests for VectorImage.

#include "Image.h"
#include "VectorImage.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include <iostream>

//------------------------------------------------------------------------
// rand_img
//------------------------------------------------------------------------
// Randomly generates an image.

Image rand_img( int ncols, int nrows )
{
  int  size = ncols * nrows;
  int* data = new int[size];

  // Randomly generates the data
  for ( int i = 0; i < size; i++ )
    data[i] = rand() % 256;

  Image img = Image( VectorInt( data, size ), ncols, nrows );
  delete[] data;
  return img;
}

// Overload rand_img

Image rand_img( int ncols, int nrows, int min_value, int max_value )
{
  int  size = ncols * nrows;
  int* data = new int[size];

  // Randomly generates the data
  for ( int i = 0; i < size; i++ )
    data[i] = min_value + rand() % ( max_value - min_value );

  Image img = Image( VectorInt( data, size ), ncols, nrows );
  delete[] data;
  return img;
}

//------------------------------------------------------------------------
// test_case_1_push_back_random
//------------------------------------------------------------------------
// A random test case that tests push back.

void test_case_1_push_back_random()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xfaceb00c );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size = rand() % 1000;
    Image*    data = new Image[size];

    for ( int j = 0; j < size; j++ ) {
      // Randomly picks ncols and nrows
      const int ncols = rand() % 28 + 1;
      const int nrows = rand() % 28 + 1;

      // Generate a random image
      Image img = rand_img( ncols, nrows );

      // Push back the image and also store it in the array
      vec.push_back( img );
      data[j] = img;
    }

    ECE2400_CHECK_INT_EQ( vec.size(), size );

    // Check each image
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.at( j ) == data[j] );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_2_find_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_2_find_random()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadc0de );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size = rand() % 1000 + 1;

    Image* data = new Image[size];

    // Push back some images
    for ( int j = 0; j < size; j++ ) {
      // Randomly picks ncols and nrows
      const int ncols = rand() % 28 + 1;
      const int nrows = rand() % 28 + 1;

      // Push back to vector and the array
      Image img = rand_img( ncols, nrows, 0, 10 );
      data[j]   = img;
      vec.push_back( img );
    }

    // Search for images - expecting success
    for ( int j = 0; j < size; j++ )
      ECE2400_CHECK_TRUE( vec.contains( data[j] ) );

    // Search for images - expecting failure
    for ( int j = 0; j < size; j++ ) {
      const int ncols = rand() % 28 + 1;
      const int nrows = rand() % 28 + 1;
      ECE2400_CHECK_FALSE( vec.contains( rand_img( ncols, nrows, 11, 20 ) ) );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_3_find_closest_linear_small
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_3_find_closest_linear_small()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadc0de );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size   = rand() % 1000 + 1;
    const int ncols  = rand() % 28 + 1;
    const int nrows  = rand() % 28 + 1;
    const int nfinds = rand() % 100 + 1;

    // Randomly pick an index to insert a small imgae
    const int idx = rand() % size;

    // Insert images with large image
    for ( int j = 0; j < idx; j++ )
      vec.push_back( rand_img( ncols, nrows, 200, 255 ) );

    Image small_img = rand_img( ncols, nrows, 0, 10 );
    vec.push_back( small_img );

    // Keep pushing back images with large image
    for ( int j = idx; j < size; j++ )
      vec.push_back( rand_img( ncols, nrows, 200, 255 ) );

    // Try find_closest with small images
    for ( int j = 0; j < nfinds; j++ ) {
      Image random_img = rand_img( ncols, nrows, 0, 10 );
      ECE2400_CHECK_TRUE( vec.find_closest_linear( random_img ) == small_img );
    }
  }
}

//------------------------------------------------------------------------
// test_case_4_find_closest_linear_large
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_4_find_closest_linear_large()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadc0de );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size   = rand() % 1000 + 1;
    const int ncols  = rand() % 28 + 1;
    const int nrows  = rand() % 28 + 1;
    const int nfinds = rand() % 100 + 1;

    // Randomly pick an index to insert a small imgae
    const int idx = rand() % size;

    // Insert images with large image
    for ( int j = 0; j < idx; j++ )
      vec.push_back( rand_img( ncols, nrows, 0, 10 ) );

    Image large_img = rand_img( ncols, nrows, 128, 255 );
    vec.push_back( large_img );

    // Keep pushing back images with large image
    for ( int j = idx; j < size; j++ )
      vec.push_back( rand_img( ncols, nrows, 0, 10 ) );

    // Try find_closest with small images
    for ( int j = 0; j < nfinds; j++ ) {
      Image random_img = rand_img( ncols, nrows, 128, 255 );
      ECE2400_CHECK_TRUE( vec.find_closest_linear( random_img ) == large_img );
    }
  }
}

//------------------------------------------------------------------------
// test_case_5_find_closest_binary_small
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_5_find_closest_binary_small()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadc0de );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size   = rand() % 1000 + 1;
    const int ncols  = rand() % 28 + 1;
    const int nrows  = rand() % 28 + 1;
    const int nfinds = rand() % 100 + 1;

    // Randomly pick an index to insert a small imgae
    const int idx = rand() % size;

    // Insert images with large image
    for ( int j = 0; j < idx; j++ )
      vec.push_back( rand_img( ncols, nrows, 200, 255 ) );

    Image small_img = rand_img( ncols, nrows, 0, 10 );
    vec.push_back( small_img );

    // Keep pushing back images with large image
    for ( int j = idx; j < size; j++ )
      vec.push_back( rand_img( ncols, nrows, 200, 255 ) );

    vec.sort();

    // Try find_closest with small images
    for ( int j = 0; j < nfinds; j++ ) {
      Image random_img = rand_img( ncols, nrows, 0, 10 );
      ECE2400_CHECK_TRUE( vec.find_closest_binary( random_img, 6 ) ==
                          small_img );
    }
  }
}

//------------------------------------------------------------------------
// test_case_6_find_closest_binary_large
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_6_find_closest_binary_large()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadc0de );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec;

    const int size   = rand() % 1000 + 1;
    const int ncols  = rand() % 28 + 1;
    const int nrows  = rand() % 28 + 1;
    const int nfinds = rand() % 100 + 1;

    // Randomly pick an index to insert a small imgae
    const int idx = rand() % size;

    // Insert images with large image
    for ( int j = 0; j < idx; j++ )
      vec.push_back( rand_img( ncols, nrows, 0, 10 ) );

    Image large_img = rand_img( ncols, nrows, 128, 255 );
    vec.push_back( large_img );

    // Keep pushing back images with large image
    for ( int j = idx; j < size; j++ )
      vec.push_back( rand_img( ncols, nrows, 0, 10 ) );

    vec.sort();

    // Try find_closest with small images
    for ( int j = 0; j < nfinds; j++ ) {
      Image random_img = rand_img( ncols, nrows, 128, 255 );
      ECE2400_CHECK_TRUE( vec.find_closest_binary( random_img, 6 ) ==
                          large_img );
    }
  }
}

//------------------------------------------------------------------------
// test_case_7_copy_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_7_copy_random()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadcafe );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec0;

    const int base_size = rand() % 1000 + 1;
    const int add_size  = rand() % 1000 + 1;

    Image* data  = new Image[base_size];
    Image* data0 = new Image[add_size];
    Image* data1 = new Image[add_size];

    // Push back to vec0
    for ( int j = 0; j < base_size; j++ ) {
      Image img = rand_img( 28, 28 );
      data[j]   = img;
      vec0.push_back( img );
    }

    // Copy constructor
    VectorImage vec1 = VectorImage( vec0 );

    // Push back different images to vec0 and vec1
    for ( int j = 0; j < add_size; j++ ) {
      Image img0 = rand_img( 28, 28, 0, 127 );
      Image img1 = rand_img( 28, 28, 128, 255 );

      data0[j] = img0;
      data1[j] = img1;

      vec0.push_back( img0 );
      vec1.push_back( img1 );
    }

    // Check size
    ECE2400_CHECK_INT_EQ( vec0.size(), base_size + add_size );
    ECE2400_CHECK_INT_EQ( vec1.size(), base_size + add_size );

    // Check base
    for ( int j = 0; j < base_size; j++ ) {
      ECE2400_CHECK_TRUE( vec0.at( j ) == data[j] );
      ECE2400_CHECK_TRUE( vec0[j] == data[j] );
      ECE2400_CHECK_TRUE( vec1.at( j ) == data[j] );
      ECE2400_CHECK_TRUE( vec1[j] == data[j] );
    }

    // Check additional images
    for ( int j = 0; j < add_size; j++ ) {
      ECE2400_CHECK_TRUE( vec0.at( j + base_size ) == data0[j] );
      ECE2400_CHECK_TRUE( vec1.at( j + base_size ) == data1[j] );
      ECE2400_CHECK_TRUE( vec0[j + base_size] == data0[j] );
      ECE2400_CHECK_TRUE( vec1[j + base_size] == data1[j] );
    }

    delete[] data;
    delete[] data0;
    delete[] data1;
  }
}

//------------------------------------------------------------------------
// test_case_8_assignment_random
//------------------------------------------------------------------------
// A random test case that tests copy constructor and assignment operator.

void test_case_8_assignment_random()
{
  std::printf( "\n%s\n", __func__ );

  srand( 0xbadbed );

  const int ntrials = 10;

  for ( int i = 0; i < ntrials; i++ ) {
    VectorImage vec0;
    VectorImage vec1;

    const int base_size = rand() % 1000 + 1;
    const int add_size  = rand() % 1000 + 1;

    Image* data  = new Image[base_size];
    Image* data0 = new Image[add_size];
    Image* data1 = new Image[add_size];

    // Push back to vec0
    for ( int j = 0; j < base_size; j++ ) {
      Image img = rand_img( 28, 28 );
      data[j]   = img;
      vec0.push_back( img );
    }

    // Push back some garbage to vec1
    int rand_size = rand() % 30;
    for ( int j = 0; j < rand_size; j++ )
      vec1.push_back( rand_img( 28, 28 ) );

    // Assignment operator
    vec1 = vec0;

    // Push back different images to vec0 and vec1
    for ( int j = 0; j < add_size; j++ ) {
      Image img0 = rand_img( 28, 28, 0, 127 );
      Image img1 = rand_img( 28, 28, 128, 255 );

      data0[j] = img0;
      data1[j] = img1;

      vec0.push_back( img0 );
      vec1.push_back( img1 );
    }

    // Check size
    ECE2400_CHECK_INT_EQ( vec0.size(), base_size + add_size );
    ECE2400_CHECK_INT_EQ( vec1.size(), base_size + add_size );

    // Check base
    for ( int j = 0; j < base_size; j++ ) {
      ECE2400_CHECK_TRUE( vec0.at( j ) == data[j] );
      ECE2400_CHECK_TRUE( vec0[j] == data[j] );
      ECE2400_CHECK_TRUE( vec1.at( j ) == data[j] );
      ECE2400_CHECK_TRUE( vec1[j] == data[j] );
    }

    // Check additional images
    for ( int j = 0; j < add_size; j++ ) {
      ECE2400_CHECK_TRUE( vec0.at( j + base_size ) == data0[j] );
      ECE2400_CHECK_TRUE( vec1.at( j + base_size ) == data1[j] );
      ECE2400_CHECK_TRUE( vec0[j + base_size] == data0[j] );
      ECE2400_CHECK_TRUE( vec1[j + base_size] == data1[j] );
    }

    delete[] data;
    delete[] data0;
    delete[] data1;
  }
}

//'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''''
// Implement more test cases here.
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_push_back_random();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_find_random();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_find_closest_linear_small();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_find_closest_linear_large();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_find_closest_binary_small();
  if ( ( __n == 0 ) || ( __n == 6  ) ) test_case_6_find_closest_binary_large();
  if ( ( __n == 0 ) || ( __n == 7  ) ) test_case_7_copy_random();
  if ( ( __n == 0 ) || ( __n == 8  ) ) test_case_8_assignment_random();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return __failed;
}
// clang-format on
