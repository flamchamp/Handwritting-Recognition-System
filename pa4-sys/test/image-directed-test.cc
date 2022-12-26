//========================================================================
// image-directed-test.cc
//========================================================================
// Test program that includes directed tests for Image.

#include "Image.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// test_case_1_basic
//------------------------------------------------------------------------
// A simple test case that tests Image basics.

void test_case_1_basic()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector
  int       data[] = {19, 95, 0, 4, 2, 3};
  VectorInt vec    = VectorInt( data, 6 );

  // Construct a image using non default construct
  Image img( vec, 3, 2 );

  // Mutate vec to test deepcopy
  vec = VectorInt();
  vec.push_back( 0xFaceDead );
  vec.push_back( 0xBadBed );

  // Check data
  ECE2400_CHECK_INT_EQ( img.at( 0, 0 ), 19 );
  ECE2400_CHECK_INT_EQ( img.at( 1, 0 ), 95 );
  ECE2400_CHECK_INT_EQ( img.at( 2, 0 ), 0 );
  ECE2400_CHECK_INT_EQ( img.at( 0, 1 ), 4 );
  ECE2400_CHECK_INT_EQ( img.at( 1, 1 ), 2 );
  ECE2400_CHECK_INT_EQ( img.at( 2, 1 ), 3 );

  // Check ncols and nrows
  ECE2400_CHECK_INT_EQ( img.get_ncols(), 3 );
  ECE2400_CHECK_INT_EQ( img.get_nrows(), 2 );
}

//------------------------------------------------------------------------
// test_case_2_default_constructor
//------------------------------------------------------------------------
// Test if an empty image is initialized properly.

void test_case_2_default_constructor()
{
  std::printf( "\n%s\n", __func__ );

  // Default constructor
  Image img;

  // Check size, get_ncols and get_nrows
  ECE2400_CHECK_INT_EQ( img.get_ncols(), 0 );
  ECE2400_CHECK_INT_EQ( img.get_nrows(), 0 );
}

//------------------------------------------------------------------------
// test_case_3_construct_size_mismatch
//------------------------------------------------------------------------

void test_case_3_construct_size_mismatch()
{
  std::printf( "\n%s\n", __func__ );

  // Construct a vector of size 8
  int       data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  VectorInt vec( data, 8 );

  // Try constructing an image that has a size of 9
  bool flag = false;
  try {
    Image img( vec, 3, 3 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_4_at_out_of_bound
//------------------------------------------------------------------------
// Test if exception is properly thrown when at is out of bound.

void test_case_4_at_out_of_bound()
{
  std::printf( "\n%s\n", __func__ );

  int data[] = {1, 9, 9, 5, 0, 4, 2, 3};

  // Try access an empty image

  bool flag = false;
  try {
    Image img;
    img.at( 0, 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // Try out of bound access - right at the boundary

  flag = false;
  try {
    Image img( VectorInt( data, 8 ), 2, 4 );
    img.at( 2, 4 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // Try out of bound access - beyond the boundary

  flag = false;
  try {
    Image img( VectorInt( data, 8 ), 2, 4 );
    img.at( 3, 1 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_5_label
//------------------------------------------------------------------------
// Test if label related functions.

void test_case_5_label()
{
  std::printf( "\n%s\n", __func__ );

  // Check if the label for empty image is initialized properly
  Image empty_img;
  ECE2400_CHECK_TRUE( empty_img.get_label() == '?' );

  // Construct an image
  int   data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  Image img    = Image( VectorInt( data, 8 ), 4, 2 );

  // Check if label is initialized properly
  ECE2400_CHECK_TRUE( img.get_label() == '?' );

  // Set label and check
  img.set_label( 'o' );

  ECE2400_CHECK_TRUE( img.get_label() == 'o' );

  img.set_label( 'y' );
  img.set_label( 'h' );

  ECE2400_CHECK_TRUE( img.get_label() == 'h' );
}

//------------------------------------------------------------------------
// test_case_6_intensity
//------------------------------------------------------------------------
// Test get_intensity.

void test_case_6_intensity()
{
  std::printf( "\n%s\n", __func__ );

  int data0[] = {1, 9, 9, 5, 0, 4, 2, 3};  // sum 33
  int data1[] = {1, 9, 9, 4, 0, 9, 1, 7};  // sum 40
  int data2[] = {1, 9, 9, 3, 0, 8, 2, 0};  // sum 32

  // Construct vectors
  VectorInt vec0( data0, 8 );
  VectorInt vec1( data1, 8 );
  VectorInt vec2( data2, 8 );

  // Construct images
  Image img0( vec0, 2, 4 );
  Image img1( vec1, 2, 4 );
  Image img2( vec2, 2, 4 );

  // Check intensity
  ECE2400_CHECK_INT_EQ( img0.get_intensity(), 33 );
  ECE2400_CHECK_INT_EQ( img1.get_intensity(), 40 );
  ECE2400_CHECK_INT_EQ( img2.get_intensity(), 32 );

  // Check the intensity of empty image
  ECE2400_CHECK_INT_EQ( Image().get_intensity(), 0 );
}

//------------------------------------------------------------------------
// test_case_7_distance
//------------------------------------------------------------------------
// Test distance.

void test_case_7_distance()
{
  std::printf( "\n%s\n", __func__ );

  int data0[] = {1, 9, 9, 5, 0, 4, 2, 3};  // sum 33
  int data1[] = {1, 9, 9, 4, 0, 9, 1, 7};  // sum 40

  // Calculate the distance
  int dist = 0;
  for ( int i = 0; i < 8; i++ )
    dist += ( data0[i] - data1[i] ) * ( data0[i] - data1[i] );

  // Construct images
  Image img0 = Image( VectorInt( data0, 8 ), 2, 4 );
  Image img1 = Image( VectorInt( data1, 8 ), 2, 4 );

  // Check distance
  ECE2400_CHECK_INT_EQ( img0.distance( img1 ), dist );

  // Check empty images
  ECE2400_CHECK_INT_EQ( Image().distance( Image() ), 0 );
}

//------------------------------------------------------------------------
// test_case_8_distance_mismatch
//------------------------------------------------------------------------
// Test if exception is properly thrown when the size of two images does
// not match.

void test_case_8_distance_mismatch()
{
  std::printf( "\n%s\n", __func__ );

  int data0[] = {1, 9, 9, 5, 0, 4, 2, 3};  // sum 33
  int data1[] = {1, 9, 9, 4, 0, 9, 1, 7};  // sum 40

  // Both dimension does not match

  bool flag = false;
  try {
    Image img0 = Image( VectorInt( data0, 8 ), 2, 4 );
    Image img1 = Image( VectorInt( data1, 8 ), 4, 2 );
    img0.distance( img1 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // Only ncols does not match

  flag = false;
  try {
    Image img0 = Image( VectorInt( data0, 8 ), 2, 4 );
    Image img1 = Image( VectorInt( data1, 4 ), 1, 4 );
    img0.distance( img1 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // Only nrows does not match

  flag = false;
  try {
    Image img0 = Image( VectorInt( data0, 8 ), 2, 4 );
    Image img1 = Image( VectorInt( data1, 6 ), 2, 3 );
    img0.distance( img1 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_9_equality_same_dim
//------------------------------------------------------------------------
// Test== and != operator on images whose dimension match.

void test_case_9_equality_same_dim()
{
  std::printf( "\n%s\n", __func__ );

  int data0[] = {1, 9, 9, 5, 0, 4, 2, 3};  // sum 33
  int data1[] = {1, 9, 9, 3, 0, 8, 2, 0};  // sum 32
  int data2[] = {1, 9, 9, 6, 0, 4, 2, 1};  // sum 32

  // Construct vectors
  VectorInt vec0( data0, 8 );
  VectorInt vec1( data1, 8 );
  VectorInt vec2( data2, 8 );

  // Construct images
  Image img0( vec0, 2, 4 );
  Image img1( vec1, 2, 4 );
  Image img2( vec2, 2, 4 );

  // Check inequality and equality
  ECE2400_CHECK_TRUE( img0 != img2 );
  ECE2400_CHECK_TRUE( img1 != img2 );
  ECE2400_CHECK_TRUE( img0 != img1 );

  ECE2400_CHECK_TRUE( img0 == Image( VectorInt( data0, 8 ), 2, 4 ) );
  ECE2400_CHECK_TRUE( img1 == Image( VectorInt( data1, 8 ), 2, 4 ) );
  ECE2400_CHECK_TRUE( img2 == Image( VectorInt( data2, 8 ), 2, 4 ) );
}

//------------------------------------------------------------------------
// test_case_10_equality_diff_dim
//------------------------------------------------------------------------
// Test== and != operator on images whose dimension match.

void test_case_10_equality_diff_dim()
{
  std::printf( "\n%s\n", __func__ );

  int data[] = {1, 9, 9, 5, 0, 4, 2, 3};  // sum 33

  // Construct image
  Image img = Image( VectorInt( data, 8 ), 2, 4 );

  // Check inequality
  ECE2400_CHECK_TRUE( img != Image( VectorInt( data, 6 ), 2, 3 ) );
  ECE2400_CHECK_TRUE( img != Image( VectorInt( data, 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( img != Image( VectorInt( data, 4 ), 1, 4 ) );
}

//------------------------------------------------------------------------
// test_case_11_copy
//------------------------------------------------------------------------
// Test the default copy construcotr

void test_case_11_copy()
{
  std::printf( "\n%s\n", __func__ );

  int data[] = {1, 9, 9, 5};

  // Construct vector from array
  VectorInt vec( data, 4 );

  // Construct image from vector
  Image img0( vec, 2, 2 );

  // Mutate the data array
  for ( int& v : data )
    v = 0xfaceb00c;

  // Mutate the vector
  vec = VectorInt();

  // Set a label to img0
  img0.set_label( '1' );

  // Use default copy constructor
  Image img1 = Image( img0 );

  // Check if the data in both images
  ECE2400_CHECK_INT_EQ( img0.at( 0, 0 ), 1 );
  ECE2400_CHECK_INT_EQ( img0.at( 1, 0 ), 9 );
  ECE2400_CHECK_INT_EQ( img0.at( 0, 1 ), 9 );
  ECE2400_CHECK_INT_EQ( img0.at( 1, 1 ), 5 );

  ECE2400_CHECK_INT_EQ( img1.at( 0, 0 ), 1 );
  ECE2400_CHECK_INT_EQ( img1.at( 1, 0 ), 9 );
  ECE2400_CHECK_INT_EQ( img1.at( 0, 1 ), 9 );
  ECE2400_CHECK_INT_EQ( img1.at( 1, 1 ), 5 );

  ECE2400_CHECK_TRUE( img0.get_label() == '1' );
  ECE2400_CHECK_TRUE( img1.get_label() == '1' );
}

//------------------------------------------------------------------------
// test_case_12_assignment
//------------------------------------------------------------------------

void test_case_12_assignment()
{
  std::printf( "\n%s\n", __func__ );

  int data[] = {1, 9, 9, 5};

  // Construct vector from array
  VectorInt vec( data, 4 );

  // Construct image from vector
  Image img0( vec, 2, 2 );

  // Mutate the data array
  for ( int& v : data )
    v = 0xfaceb00c;

  // Mutate the vector
  vec = VectorInt();

  // Set a label to img0
  img0.set_label( '1' );

  // Use default assignment constructor
  Image img1;
  img1 = Image( img0 );

  // Check if the data in both images
  ECE2400_CHECK_INT_EQ( img0.at( 0, 0 ), 1 );
  ECE2400_CHECK_INT_EQ( img0.at( 1, 0 ), 9 );
  ECE2400_CHECK_INT_EQ( img0.at( 0, 1 ), 9 );
  ECE2400_CHECK_INT_EQ( img0.at( 1, 1 ), 5 );

  ECE2400_CHECK_INT_EQ( img1.at( 0, 0 ), 1 );
  ECE2400_CHECK_INT_EQ( img1.at( 1, 0 ), 9 );
  ECE2400_CHECK_INT_EQ( img1.at( 0, 1 ), 9 );
  ECE2400_CHECK_INT_EQ( img1.at( 1, 1 ), 5 );

  ECE2400_CHECK_TRUE( img0.get_label() == '1' );
  ECE2400_CHECK_TRUE( img1.get_label() == '1' );
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

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_basic();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_default_constructor();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_construct_size_mismatch();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_at_out_of_bound();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_label();
  if ( ( __n == 0 ) || ( __n == 6  ) ) test_case_6_intensity();
  if ( ( __n == 0 ) || ( __n == 7  ) ) test_case_7_distance();
  if ( ( __n == 0 ) || ( __n == 8  ) ) test_case_8_distance_mismatch();
  if ( ( __n == 0 ) || ( __n == 9  ) ) test_case_9_equality_same_dim();
  if ( ( __n == 0 ) || ( __n == 10 ) ) test_case_10_equality_diff_dim();
  if ( ( __n == 0 ) || ( __n == 11 ) ) test_case_11_copy();
  if ( ( __n == 0 ) || ( __n == 12 ) ) test_case_12_assignment();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

  return __failed;
}
// clang-format on
