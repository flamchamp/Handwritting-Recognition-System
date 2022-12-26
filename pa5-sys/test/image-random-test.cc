//========================================================================
// image-random-test.cc
//========================================================================
// Test program that includes directed tests for Image.

#include "Image.h"
#include "ece2400-stdlib.h"

#include <cstdio>
#include <cstdlib>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------

void test_case_1_simple()
{
  std::printf( "\n%s\n", __func__ );

  const char labels[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  // Construct a vector
  int iterations = 10;
  srand( 0xdeadbeef );

  for ( int i = 0; i < iterations; i++ ) {
    // Choose image dimension from 2 to 41
    int  dim  = rand() % 40 + 2;
    int  size = dim * dim;
    int* data = new int[size];

    // For calculating intensity
    int intensity = 0;

    for ( int j = 0; j < size; j++ ) {
      data[j] = rand() % 100;
      intensity += data[j];
    }

    Vector<int> vec( data, size );
    Image       img( vec, dim, dim );

    // Make sure img deepcopies
    vec = Vector<int>();

    // Check vector initialization is correct
    int ind = 0;
    for ( int j = 0; j < dim; j++ ) {
      for ( int k = 0; k < dim; k++ ) {
        ECE2400_CHECK_INT_EQ( img.at( k, j ), data[ind] );
        ind++;
      }
    }

    ECE2400_CHECK_INT_EQ( img.get_intensity(), intensity );

    int label = rand() % 10;

    // Check get_label and set_label
    ECE2400_CHECK_TRUE( img.get_label() == '?' );
    img.set_label( labels[label] );
    ECE2400_CHECK_TRUE( img.get_label() == labels[label] );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_2_copy
//------------------------------------------------------------------------

void test_case_2_copy()
{
  std::printf( "\n%s\n", __func__ );

  const char labels[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  // Construct a vector
  int iterations = 10;

  srand( 0xc0ded00d );

  for ( int i = 0; i < iterations; i++ ) {
    int  dim       = rand() % 40 + 2;
    int  size      = dim * dim;
    int* data      = new int[size];
    int  intensity = 0;

    for ( int j = 0; j < size; j++ ) {
      data[j] = rand() % 100;
      intensity += data[j];
    }

    Vector<int> vec( data, size );
    Image       img0( vec, dim, dim );

    // Change the vector
    vec = Vector<int>();

    int label = rand() % 10;

    img0.set_label( labels[label] );

    // Use default assignment operator
    Image img1;
    img1 = img0;

    int ind = 0;
    for ( int j = 0; j < dim; j++ ) {
      for ( int k = 0; k < dim; k++ ) {
        ECE2400_CHECK_INT_EQ( img0.at( k, j ), data[ind] );
        ECE2400_CHECK_INT_EQ( img1.at( k, j ), data[ind] );
        ind++;
      }
    }

    ECE2400_CHECK_INT_EQ( img0.get_intensity(), intensity );
    ECE2400_CHECK_INT_EQ( img1.get_intensity(), intensity );

    ECE2400_CHECK_TRUE( img0.get_label() == labels[label] );
    ECE2400_CHECK_TRUE( img1.get_label() == labels[label] );

    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_3_intensity
//------------------------------------------------------------------------

void test_case_3_intensity()
{
  std::printf( "\n%s\n", __func__ );

  const int iterations = 10;

  srand( 0xcafe50da );

  for ( int i = 0; i < iterations; i++ ) {
    // Choose image dimensions from 2 to 41
    int dim1 = rand() % 40 + 2;
    int dim2 = rand() % 40 + 2;

    int    num_images = rand() % 10 + 1;
    int    size       = dim1 * dim2;
    int**  data       = new int*[num_images];
    int*   intensity  = new int[num_images];
    Image* images     = new Image[num_images];

    for ( int j = 0; j < num_images; j++ ) {
      data[j] = new int[size];

      // Set intensity for image j to 0
      intensity[j] = 0;

      for ( int k = 0; k < size; k++ ) {
        data[j][k] = rand() % 100;
        intensity[j] += data[j][k];
      }

      Vector<int> vec( data[j], size );
      images[j] = Image( vec, dim1, dim2 );

      delete[] data[j];
    }

    // Check vector_compare for random vectors
    for ( int j = 0; j < 20; j++ ) {
      int rand_i1 = rand() % num_images;
      int rand_i2 = rand() % num_images;

      // Check all boolean operators
      if ( intensity[rand_i1] == intensity[rand_i2] ) {
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() <
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() >
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() <=
                            images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() >=
                            images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() ==
                            images[rand_i2].get_intensity() );
      }
      else if ( intensity[rand_i1] > intensity[rand_i2] ) {
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() <
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() <=
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() ==
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() >
                            images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() >=
                            images[rand_i2].get_intensity() );
      }
      else {
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() >
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() >=
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_FALSE( images[rand_i1].get_intensity() ==
                             images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() <
                            images[rand_i2].get_intensity() );
        ECE2400_CHECK_TRUE( images[rand_i1].get_intensity() <=
                            images[rand_i2].get_intensity() );
      }
    }

    delete[] images;
    delete[] intensity;
    delete[] data;
  }
}

//------------------------------------------------------------------------
// test_case_4_exceptions
//------------------------------------------------------------------------

void test_case_4_exceptions()
{
  std::printf( "\n%s\n", __func__ );

  const int iterations = 100;

  srand( 0xf00dface );

  for ( int i = 0; i < iterations; i++ ) {
    // Choose image dimensions from 2 to 41
    int dim1 = rand() % 40 + 2;
    int dim2 = rand() % 40 + 2;
    int size = dim1 * dim2;

    // Initialize vec
    int* data = new int[size];

    for ( int j = 0; j < size; j++ )
      data[j] = 0;

    Vector<int> vec( data, size );

    // Try constructing an image that has a size greater than data size
    bool flag = false;
    try {
      Image img( vec, dim1 + 1, dim2 + 1 );
    } catch ( ece2400::InvalidArgument e ) {
      flag = true;
    }
    ECE2400_CHECK_TRUE( flag );

    // Choose random dimension that can go over dimension sizes, and
    // test if invalid at throws exception
    int rand_dim1 = rand() % ( dim1 * 2 );
    int rand_dim2 = rand() % ( dim2 * 2 );
    flag          = false;
    try {
      Image img( vec, dim1, dim2 );
      img.at( rand_dim1, rand_dim2 );
    } catch ( ece2400::OutOfRange e ) {
      flag = true;
    }

    if ( rand_dim1 >= dim1 || rand_dim2 >= dim2 ) {
      ECE2400_CHECK_TRUE( flag );
    }
    else {
      ECE2400_CHECK_FALSE( flag );
    }

    delete[] data;
  }
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1 ) ) test_case_1_simple();
  if ( ( __n == 0 ) || ( __n == 2 ) ) test_case_2_copy();
  if ( ( __n == 0 ) || ( __n == 3 ) ) test_case_3_intensity();
  if ( ( __n == 0 ) || ( __n == 4 ) ) test_case_4_exceptions();

  std::printf("\n");

  return __failed;
}
// clang-format on
