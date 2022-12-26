//========================================================================
// sort-image-random-test.cc
//========================================================================

#include "Image.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>

//------------------------------------------------------------------------
// test_case_1_simple
//------------------------------------------------------------------------

void test_case_1_simple()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0x8BadBeef );

  const int size  = 100;
  const int ncols = 4;
  const int nrows = 4;
  Image*    a     = new Image[size];

  for ( int i = 0; i < size; i++ ) {
    VectorInt vec;
    for ( int x = 0; x < ncols; x++ )
      for ( int y = 0; y < nrows; y++ ) {
        int random_value = rand() % 250;
        vec.push_back( random_value );
      }
    a[i] = Image( vec, ncols, nrows );
  }

  sort_image( a, size );

  for ( int i = 0; i < size - 1; i++ ) {
    int intensity1 = a[i].get_intensity();
    int intensity2 = a[i + 1].get_intensity();
    ECE2400_CHECK_TRUE( intensity1 <= intensity2 );
  }

  delete[] a;
}

//------------------------------------------------------------------------
// test_case_2_large
//------------------------------------------------------------------------

void test_case_2_large()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0xbadc0de );

  const int size  = 1000;
  const int ncols = 4;
  const int nrows = 4;
  Image*    a     = new Image[size];

  for ( int i = 0; i < size; i++ ) {
    VectorInt vec;
    for ( int x = 0; x < ncols; x++ )
      for ( int y = 0; y < nrows; y++ ) {
        int random_value = rand() % 250;
        vec.push_back( random_value );
      }
    a[i] = Image( vec, ncols, nrows );
  }

  sort_image( a, size );

  for ( int i = 0; i < size - 1; i++ ) {
    int intensity1 = a[i].get_intensity();
    int intensity2 = a[i + 1].get_intensity();
    ECE2400_CHECK_TRUE( intensity1 <= intensity2 );
  }

  delete[] a;
}

//------------------------------------------------------------------------
// test_case_3_few_unique
//------------------------------------------------------------------------

void test_case_3_few_unique()
{
  std::printf( "\n%s\n", __func__ );
  srand( 0xfaceb00c );

  const int size  = 1000;
  const int ncols = 4;
  const int nrows = 4;
  Image*    a     = new Image[size];

  for ( int i = 0; i < size; i++ ) {
    VectorInt vec;
    for ( int x = 0; x < ncols; x++ )
      for ( int y = 0; y < nrows; y++ ) {
        int random_value = rand() % 10;
        vec.push_back( random_value );
      }
    a[i] = Image( vec, ncols, nrows );
  }

  sort_image( a, size );

  for ( int i = 0; i < size - 1; i++ ) {
    int intensity1 = a[i].get_intensity();
    int intensity2 = a[i + 1].get_intensity();
    ECE2400_CHECK_TRUE( intensity1 <= intensity2 );
  }

  delete[] a;
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
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_large();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_few_unique();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  return __failed;
}
// clang-format on
