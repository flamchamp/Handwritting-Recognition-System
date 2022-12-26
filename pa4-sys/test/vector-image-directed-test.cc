//========================================================================
// vector-image-directed-test.cc
//========================================================================
// This file contains directed tests for VectorImage-related functions.

#include "Image.h"
#include "VectorImage.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// test_case_1_simple_push_back
//------------------------------------------------------------------------
// A simple test case that tests default constructor, push_back, and at.

void test_case_1_simple_push_back()
{
  std::printf( "\n%s\n", __func__ );

  int data[][4] = {{1, 9, 9, 5}, {0, 4, 2, 3}, {1, 1, 0, 3}};

  // Use default constructor to construct empty vecotr
  VectorImage vec;

  // Check size for empty vector
  ECE2400_CHECK_INT_EQ( vec.size(), 0 );

  // Push back some images
  for ( auto a : data )
    vec.push_back( Image( VectorInt( a, 4 ), 2, 2 ) );

  // Check value and size
  ECE2400_CHECK_TRUE( vec[0].at( 0, 0 ) == 1 );
  ECE2400_CHECK_TRUE( vec[0].at( 1, 0 ) == 9 );
  ECE2400_CHECK_TRUE( vec[0].at( 0, 1 ) == 9 );
  ECE2400_CHECK_TRUE( vec[0].at( 1, 1 ) == 5 );
  ECE2400_CHECK_TRUE( vec[0] == Image( VectorInt( data[0], 4 ), 2, 2 ) );
  ECE2400_CHECK_TRUE( vec[1] == Image( VectorInt( data[1], 4 ), 2, 2 ) );
  ECE2400_CHECK_TRUE( vec[2] == Image( VectorInt( data[2], 4 ), 2, 2 ) );

  ECE2400_CHECK_INT_EQ( vec.size(), 3 );
}

//------------------------------------------------------------------------
// test_case_2_at_out_of_bound
//------------------------------------------------------------------------
// Test that exception is properly thrown when at is out of bound.

void test_case_2_at_out_of_bound()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec;

  // empty vector

  bool flag = false;
  try {
    vec.at( 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // push back some images

  int data[][4] = {{1, 9, 9, 5}, {0, 4, 2, 3}};

  vec.push_back( Image( VectorInt( data[0], 4 ), 1, 4 ) );
  vec.push_back( Image( VectorInt( data[1], 4 ), 2, 2 ) );

  // right at the boundary

  flag = false;
  try {
    vec.at( 2 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  // beyond the boundary

  flag = false;
  try {
    vec.at( 5 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_3_construct
//------------------------------------------------------------------------
// A simple test case that tests non-default constructor.

void test_case_3_construct()
{
  std::printf( "\n%s\n", __func__ );

  int data[]  = {1, 9, 9, 5, 0, 4, 2, 3};
  int dummy[] = {1, 1, 1, 1, 7, 7, 7, 7};

  // An array of images
  Image images[] = {
      Image( VectorInt( data, 8 ), 2, 4 ),
      Image( VectorInt( data, 4 ), 1, 4 ),
      Image( VectorInt( data, 8 ), 4, 2 ),
      Image( VectorInt( data, 6 ), 2, 3 ),
  };

  VectorImage vec = VectorImage( images, 4 );

  // Modify the array to test deepcopy
  for ( Image& img : images )
    img = Image( VectorInt( dummy, 8 ), 8, 1 );

  // Check that the value inside the vector is not modified
  ECE2400_CHECK_TRUE( vec.at( 0 ) == Image( VectorInt( data, 8 ), 2, 4 ) );
  ECE2400_CHECK_TRUE( vec.at( 1 ) == Image( VectorInt( data, 4 ), 1, 4 ) );
  ECE2400_CHECK_TRUE( vec.at( 2 ) == Image( VectorInt( data, 8 ), 4, 2 ) );
  ECE2400_CHECK_TRUE( vec.at( 3 ) == Image( VectorInt( data, 6 ), 2, 3 ) );

  // Check size
  ECE2400_CHECK_INT_EQ( vec.size(), 4 );
}

//------------------------------------------------------------------------
// test_case_4_find_simple
//------------------------------------------------------------------------
// A simple test case that tests contains.

void test_case_4_find_simple()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3},
                   {0, 4, 2, 3, 1, 9, 9, 5},
                   {1, 9, 9, 4, 0, 9, 1, 7},
                   {0, 8, 2, 0, 1, 9, 9, 6}};

  // Construct an array of images - this will call the default constructor
  Image images[5];

  // Construct images from int array
  for ( int i = 0; i < 4; i++ )
    images[i] = Image( VectorInt( data[i], 8 ), 2, 4 );

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 5 );

  // Search for value, expecting success
  ECE2400_CHECK_TRUE( vec.contains( images[0] ) );
  ECE2400_CHECK_TRUE( vec.contains( images[1] ) );
  ECE2400_CHECK_TRUE( vec.contains( images[2] ) );
  ECE2400_CHECK_TRUE( vec.contains( images[3] ) );
  ECE2400_CHECK_TRUE( vec.contains( Image() ) );  // Find empty image

  // Search for value, expecting failure
  int arr[] = {8, 7, 6, 4, 5, 3, 2, 1};
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data[0], 8 ), 4, 2 ) ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data[1], 6 ), 2, 3 ) ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data[3], 6 ), 1, 6 ) ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( arr, 8 ), 2, 4 ) ) );
}

//------------------------------------------------------------------------
// test_case_5_find_empty
//------------------------------------------------------------------------
// A simple test case that tests contains for an empty vector.

void test_case_5_find_empty()
{
  std::printf( "\n%s\n", __func__ );

  // Construct an empty vector
  VectorImage vec;

  // Search for value, expecting failure
  int data[] = {1, 9, 9, 5, 0, 4, 2, 3};
  ECE2400_CHECK_FALSE( vec.contains( Image() ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data, 8 ), 4, 2 ) ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data, 4 ), 4, 1 ) ) );
  ECE2400_CHECK_FALSE( vec.contains( Image( VectorInt( data, 6 ), 2, 3 ) ) );
}

//------------------------------------------------------------------------
// test_case_6_find_closest_linear
//------------------------------------------------------------------------
// A simple test case that tests copy constructor and assignment operator.

void test_case_6_find_closest_linear()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3},
                   {1, 9, 9, 5, 0, 7, 3, 1},
                   {1, 9, 9, 5, 0, 1, 2, 3},
                   {2, 0, 0, 0, 1, 1, 0, 3}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 ),
                    Image( VectorInt( data[2], 8 ), 2, 4 ),
                    Image( VectorInt( data[3], 8 ), 2, 4 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 4 );

  // Find exact match
  ECE2400_CHECK_TRUE( vec.find_closest_linear( images[0] ) == images[0] );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( images[1] ) == images[1] );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( images[2] ) == images[2] );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( images[3] ) == images[3] );

  // Find images that are not in the vector
  int   arr0[] = {1, 9, 9, 5, 0, 5, 2, 4};
  int   arr1[] = {1, 9, 9, 4, 0, 8, 3, 0};
  Image img    = Image( VectorInt( arr0, 8 ), 2, 4 );

  ECE2400_CHECK_TRUE( vec.find_closest_linear( img ) == images[0] );

  img = Image( VectorInt( arr1, 8 ), 2, 4 );
  ECE2400_CHECK_TRUE( vec.find_closest_linear( img ) == images[1] );
}

//------------------------------------------------------------------------
// test_case_7_find_closest_linear_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_7_find_closest_linear_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec;

  // find_closest on empty vector
  bool flag = false;
  try {
    vec.find_closest_linear( Image() );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_8_find_closest_binary
//------------------------------------------------------------------------
// A simple test case that tests copy constructor and assignment operator.

void test_case_8_find_closest_binary()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3}, {1, 9, 9, 5, 0, 7, 3, 1},
                   {1, 9, 9, 5, 0, 1, 2, 3}, {2, 0, 0, 0, 1, 1, 0, 3},
                   {0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0},
                   {8, 9, 8, 9, 8, 9, 8, 9}, {9, 8, 9, 8, 9, 8, 9, 8}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 ),
                    Image( VectorInt( data[2], 8 ), 2, 4 ),
                    Image( VectorInt( data[3], 8 ), 2, 4 ),
                    Image( VectorInt( data[4], 8 ), 2, 4 ),
                    Image( VectorInt( data[5], 8 ), 2, 4 ),
                    Image( VectorInt( data[6], 8 ), 2, 4 ),
                    Image( VectorInt( data[7], 8 ), 2, 4 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 8 );
  vec.sort();

  // Find exact match
  ECE2400_CHECK_TRUE( vec.find_closest_binary( images[0], 4 ) == images[0] );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( images[1], 4 ) == images[1] );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( images[2], 4 ) == images[2] );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( images[3], 4 ) == images[3] );

  // Find images that are not in the vector
  int   arr0[] = {1, 9, 9, 5, 0, 5, 2, 4};
  int   arr1[] = {1, 9, 9, 4, 0, 8, 3, 0};
  Image img    = Image( VectorInt( arr0, 8 ), 2, 4 );

  ECE2400_CHECK_TRUE( vec.find_closest_binary( img, 4 ) == images[0] );

  img = Image( VectorInt( arr1, 8 ), 2, 4 );
  ECE2400_CHECK_TRUE( vec.find_closest_binary( img, 4 ) == images[1] );
}

//------------------------------------------------------------------------
// test_case_9_find_closest_binary_empty
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_9_find_closest_binary_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec;

  // find_closest on empty vector
  bool flag = false;
  try {
    vec.find_closest_binary( Image(), 0 );
  } catch ( ece2400::OutOfRange e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_10_find_closest_binary_unsorted
//------------------------------------------------------------------------
// Test that the exception is properly thrown when calling find_closet on
// an empty vector.

void test_case_10_find_closest_binary_unsorted()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3},
                   {1, 9, 9, 5, 0, 7, 3, 1},
                   {1, 9, 9, 5, 0, 1, 2, 3},
                   {2, 0, 0, 0, 1, 1, 0, 3}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 ),
                    Image( VectorInt( data[2], 8 ), 2, 4 ),
                    Image( VectorInt( data[3], 8 ), 2, 4 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 4 );

  // find_closest on unsorted vector
  bool flag = false;
  try {
    vec.find_closest_binary( Image( VectorInt( data[0], 8 ), 2, 4 ), 4 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );

  vec.sort();
  flag = false;
  try {
    vec.find_closest_binary( Image( VectorInt( data[0], 8 ), 2, 4 ), 4 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_FALSE( flag );

  int new_img[] = {1, 0, 1, 0, 1, 0, 1, 0};
  vec.push_back( Image( VectorInt( new_img, 8 ), 2, 4 ) );
  flag = false;
  try {
    vec.find_closest_binary( Image( VectorInt( data[0], 8 ), 2, 4 ), 4 );
  } catch ( ece2400::InvalidArgument e ) {
    flag = true;
  }
  ECE2400_CHECK_TRUE( flag );
}

//------------------------------------------------------------------------
// test_case_11_sort_simple
//------------------------------------------------------------------------
// A simple sort test.

void test_case_11_sort_simple()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3},
                   {1, 9, 9, 5, 0, 7, 3, 1},
                   {1, 9, 9, 5, 0, 1, 2, 3},
                   {2, 0, 0, 0, 1, 1, 0, 3}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 ),
                    Image( VectorInt( data[2], 8 ), 2, 4 ),
                    Image( VectorInt( data[3], 8 ), 2, 4 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 4 );

  vec.sort();

  ECE2400_CHECK_TRUE( vec.at( 0 ) == images[3] );
  ECE2400_CHECK_TRUE( vec.at( 1 ) == images[2] );
  ECE2400_CHECK_TRUE( vec.at( 2 ) == images[0] );
  ECE2400_CHECK_TRUE( vec.at( 3 ) == images[1] );
}

//------------------------------------------------------------------------
// test_case_12_subscript
//------------------------------------------------------------------------
// A simple test for the subscript operator.

void test_case_12_subscript()
{
  std::printf( "\n%s\n", __func__ );

  int data[][8] = {{1, 9, 9, 5, 0, 4, 2, 3},
                   {1, 9, 9, 5, 0, 7, 3, 1},
                   {1, 9, 9, 5, 0, 1, 2, 3},
                   {2, 0, 0, 0, 1, 1, 0, 3}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 8 ), 2, 4 ),
                    Image( VectorInt( data[1], 8 ), 2, 4 ),
                    Image( VectorInt( data[2], 8 ), 2, 4 ),
                    Image( VectorInt( data[3], 8 ), 2, 4 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 4 );

  // Check the value using subscript operator
  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( vec[i] == images[i] );
}

//------------------------------------------------------------------------
// test_case_13_copy
//------------------------------------------------------------------------
// A simple test case that tests copy constructor.

void test_case_13_copy()
{
  std::printf( "\n%s\n", __func__ );

  int data[][4] = {
      {1, 9, 9, 5},
      {0, 4, 2, 3},
      {1, 9, 9, 5},
      {0, 7, 3, 1},
  };

  int data0[][4] = {{6, 5, 4, 3}, {7, 6, 5, 4}, {8, 7, 6, 5}, {9, 8, 7, 6}};

  int data1[][4] = {{3, 4, 5, 6}, {4, 5, 6, 7}, {5, 6, 7, 8}, {6, 7, 8, 9}};

  // Array of images - first 4 iamges are the same
  Image images[] = {
      Image( VectorInt( data[0], 4 ), 2, 2 ),
      Image( VectorInt( data[1], 4 ), 2, 2 ),
      Image( VectorInt( data[2], 4 ), 2, 2 ),
      Image( VectorInt( data[3], 4 ), 2, 2 ),
  };

  Image images0[] = {
      Image( VectorInt( data0[0], 4 ), 2, 2 ),
      Image( VectorInt( data0[1], 4 ), 2, 2 ),
      Image( VectorInt( data0[2], 4 ), 2, 2 ),
      Image( VectorInt( data0[3], 4 ), 2, 2 ),
  };

  Image images1[] = {
      Image( VectorInt( data1[0], 4 ), 2, 2 ),
      Image( VectorInt( data1[1], 4 ), 2, 2 ),
      Image( VectorInt( data1[2], 4 ), 2, 2 ),
      Image( VectorInt( data1[3], 4 ), 2, 2 ),
  };

  // Empty vector
  VectorImage vec0;

  // Push back to vec0
  for ( auto img : images )
    vec0.push_back( img );

  // Copy constructor
  VectorImage vec1( vec0 );

  // Push different values to vec0 and vec1
  for ( auto img : images0 )
    vec0.push_back( img );

  for ( auto img : images1 )
    vec1.push_back( img );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec0[i] == images[i] );
    ECE2400_CHECK_TRUE( vec1.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec1[i] == images[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i + 4 ) == images0[i] );
    ECE2400_CHECK_TRUE( vec0[i + 4] == images0[i] );
    ECE2400_CHECK_TRUE( vec1.at( i + 4 ) == images1[i] );
    ECE2400_CHECK_TRUE( vec1[i + 4] == images1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_14_assignment_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a empty vector.

void test_case_14_assignment_empty()
{
  std::printf( "\n%s\n", __func__ );

  int data[][4] = {
      {1, 9, 9, 5},
      {0, 4, 2, 3},
      {1, 9, 9, 5},
      {0, 7, 3, 1},
  };

  int data0[][4] = {{6, 5, 4, 3}, {7, 6, 5, 4}, {8, 7, 6, 5}, {9, 8, 7, 6}};

  int data1[][4] = {{3, 4, 5, 6}, {4, 5, 6, 7}, {5, 6, 7, 8}, {6, 7, 8, 9}};

  // Array of images - first 4 iamges are the same
  Image images[] = {
      Image( VectorInt( data[0], 4 ), 2, 2 ),
      Image( VectorInt( data[1], 4 ), 2, 2 ),
      Image( VectorInt( data[2], 4 ), 2, 2 ),
      Image( VectorInt( data[3], 4 ), 2, 2 ),
  };

  Image images0[] = {
      Image( VectorInt( data0[0], 4 ), 2, 2 ),
      Image( VectorInt( data0[1], 4 ), 2, 2 ),
      Image( VectorInt( data0[2], 4 ), 2, 2 ),
      Image( VectorInt( data0[3], 4 ), 2, 2 ),
  };

  Image images1[] = {
      Image( VectorInt( data1[0], 4 ), 2, 2 ),
      Image( VectorInt( data1[1], 4 ), 2, 2 ),
      Image( VectorInt( data1[2], 4 ), 2, 2 ),
      Image( VectorInt( data1[3], 4 ), 2, 2 ),
  };

  // Empty vector
  VectorImage vec0;

  // Push back to vec0
  for ( auto img : images )
    vec0.push_back( img );

  // Assignment operator
  VectorImage vec1;
  vec1 = vec0;

  // Push different values to vec0 and vec1
  for ( auto img : images0 )
    vec0.push_back( img );

  for ( auto img : images1 )
    vec1.push_back( img );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec0[i] == images[i] );
    ECE2400_CHECK_TRUE( vec1.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec1[i] == images[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i + 4 ) == images0[i] );
    ECE2400_CHECK_TRUE( vec0[i + 4] == images0[i] );
    ECE2400_CHECK_TRUE( vec1.at( i + 4 ) == images1[i] );
    ECE2400_CHECK_TRUE( vec1[i + 4] == images1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_15_assignment_non_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a empty vector.

void test_case_15_assignment_non_empty()
{
  std::printf( "\n%s\n", __func__ );

  int data[][4] = {
      {1, 9, 9, 5},
      {0, 4, 2, 3},
      {1, 9, 9, 5},
      {0, 7, 3, 1},
  };

  int data0[][4] = {{6, 5, 4, 3}, {7, 6, 5, 4}, {8, 7, 6, 5}, {9, 8, 7, 6}};

  int data1[][4] = {{3, 4, 5, 6}, {4, 5, 6, 7}, {5, 6, 7, 8}, {6, 7, 8, 9}};

  // Array of images - first 4 iamges are the same
  Image images[] = {
      Image( VectorInt( data[0], 4 ), 2, 2 ),
      Image( VectorInt( data[1], 4 ), 2, 2 ),
      Image( VectorInt( data[2], 4 ), 2, 2 ),
      Image( VectorInt( data[3], 4 ), 2, 2 ),
  };

  Image images0[] = {
      Image( VectorInt( data0[0], 4 ), 2, 2 ),
      Image( VectorInt( data0[1], 4 ), 2, 2 ),
      Image( VectorInt( data0[2], 4 ), 2, 2 ),
      Image( VectorInt( data0[3], 4 ), 2, 2 ),
  };

  Image images1[] = {
      Image( VectorInt( data1[0], 4 ), 2, 2 ),
      Image( VectorInt( data1[1], 4 ), 2, 2 ),
      Image( VectorInt( data1[2], 4 ), 2, 2 ),
      Image( VectorInt( data1[3], 4 ), 2, 2 ),
  };

  // Empty vector
  VectorImage vec0;
  VectorImage vec1;

  // Push back to vec0
  for ( auto img : images )
    vec0.push_back( img );

  // Push back to vec1
  for ( auto img : images1 )
    vec1.push_back( img );

  for ( auto img : images0 )
    vec1.push_back( img );

  // Assignment operator
  vec1 = vec0;

  // Push different values to vec0 and vec1
  for ( auto img : images0 )
    vec0.push_back( img );

  for ( auto img : images1 )
    vec1.push_back( img );

  // Check size
  ECE2400_CHECK_TRUE( vec0.size() == 8 );
  ECE2400_CHECK_TRUE( vec1.size() == 8 );

  // Check the first 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec0[i] == images[i] );
    ECE2400_CHECK_TRUE( vec1.at( i ) == images[i] );
    ECE2400_CHECK_TRUE( vec1[i] == images[i] );
  }

  // Check the last 4 elements
  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( vec0.at( i + 4 ) == images0[i] );
    ECE2400_CHECK_TRUE( vec0[i + 4] == images0[i] );
    ECE2400_CHECK_TRUE( vec1.at( i + 4 ) == images1[i] );
    ECE2400_CHECK_TRUE( vec1[i + 4] == images1[i] );
  }
}

//------------------------------------------------------------------------
// test_case_16_self_assignment
//------------------------------------------------------------------------
// Test self assignment

void test_case_16_self_assignment()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec;
  int         data[4] = {1, 9, 9, 5};

  vec.push_back( Image( VectorInt( data, 4 ), 1, 4 ) );

  vec = vec;
}

//------------------------------------------------------------------------
// test_case_17_assign_twice
//------------------------------------------------------------------------
// Assign vec0 to vec1, vec1 to vec2

void test_case_17_assign_twice()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec0;
  VectorImage vec1;
  VectorImage vec2;

  int data[][4] = {
      {1, 9, 9, 5}, {2, 0, 0, 0}, {3, 4, 2, 1}, {5, 6, 1, 3}, {5, 6, 1, 3}};

  vec0.push_back( Image( VectorInt( data[0], 4 ), 4, 1 ) );
  vec0.push_back( Image( VectorInt( data[1], 4 ), 4, 1 ) );
  vec0.push_back( Image( VectorInt( data[2], 4 ), 4, 1 ) );
  vec1.push_back( Image( VectorInt( data[1], 4 ), 4, 1 ) );
  vec1.push_back( Image( VectorInt( data[2], 4 ), 4, 1 ) );
  vec2.push_back( Image( VectorInt( data[3], 4 ), 4, 1 ) );
  vec2.push_back( Image( VectorInt( data[4], 4 ), 4, 1 ) );

  vec1 = vec0;                                               // vec1 has 0, 1, 2
  vec1.push_back( Image( VectorInt( data[3], 4 ), 4, 1 ) );  // append 3
  vec2 = vec1;  // vec2 has 0, 1, 2, 3
  vec2.push_back( Image( VectorInt( data[4], 4 ), 4, 1 ) );  // append 4

  ECE2400_CHECK_TRUE( vec0.size() == 3 );
  ECE2400_CHECK_TRUE( vec1.size() == 4 );
  ECE2400_CHECK_TRUE( vec2.size() == 5 );
  ECE2400_CHECK_TRUE( vec2.at( 0 ) == Image( VectorInt( data[0], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 1 ) == Image( VectorInt( data[1], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 2 ) == Image( VectorInt( data[2], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 3 ) == Image( VectorInt( data[3], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 4 ) == Image( VectorInt( data[4], 4 ), 4, 1 ) );
}

//------------------------------------------------------------------------
// test_case_18_copy_twice
//------------------------------------------------------------------------
// Copy vec0 to vec1, vec1 to vec2

void test_case_18_copy_twice()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec0;

  int data[][4] = {
      {1, 9, 9, 5}, {2, 0, 0, 0}, {3, 4, 2, 1}, {5, 6, 1, 3}, {5, 6, 1, 3}};

  vec0.push_back( Image( VectorInt( data[0], 4 ), 4, 1 ) );
  vec0.push_back( Image( VectorInt( data[1], 4 ), 4, 1 ) );
  vec0.push_back( Image( VectorInt( data[2], 4 ), 4, 1 ) );

  VectorImage vec1 = vec0;  // vec1 has 0, 1, 2

  vec1.push_back( Image( VectorInt( data[3], 4 ), 4, 1 ) );  // append 3

  VectorImage vec2 = vec1;  // vec2 has 0, 1, 2, 3

  vec2.push_back( Image( VectorInt( data[4], 4 ), 4, 1 ) );  // append 4

  ECE2400_CHECK_TRUE( vec0.size() == 3 );
  ECE2400_CHECK_TRUE( vec1.size() == 4 );
  ECE2400_CHECK_TRUE( vec2.size() == 5 );
  ECE2400_CHECK_TRUE( vec2.at( 0 ) == Image( VectorInt( data[0], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 1 ) == Image( VectorInt( data[1], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 2 ) == Image( VectorInt( data[2], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 3 ) == Image( VectorInt( data[3], 4 ), 4, 1 ) );
  ECE2400_CHECK_TRUE( vec2.at( 4 ) == Image( VectorInt( data[4], 4 ), 4, 1 ) );
}

//------------------------------------------------------------------------
// test_case_19_assign_empty
//------------------------------------------------------------------------
// Assign an empty vector

void test_case_19_assign_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec0;
  VectorImage vec1;

  vec0 = vec1;

  ECE2400_CHECK_TRUE( vec0.size() == 0 );
  ECE2400_CHECK_TRUE( vec1.size() == 0 );
}

//------------------------------------------------------------------------
// test_case_20_copy_empty
//------------------------------------------------------------------------
// Copy an empty vector

void test_case_20_copy_empty()
{
  std::printf( "\n%s\n", __func__ );

  VectorImage vec0;

  VectorImage vec1 = vec0;

  ECE2400_CHECK_TRUE( vec0.size() == 0 );
  ECE2400_CHECK_TRUE( vec1.size() == 0 );
}

//------------------------------------------------------------------------
// test_case_21_find_closest_different
//------------------------------------------------------------------------
// a case where sorting by intensity causes find_closest_binary to
// produce a different result from find_closest_linear

void test_case_21_find_closest_different()
{
  std::printf( "\n%s\n", __func__ );

  int data[][9] = {
      {2, 2, 2, 0, 0, 0, 0, 0, 0},    {0, 0, 4, 0, 0, 4, 0, 0, 4},
      {0, 0, 0, 0, 0, 0, 6, 6, 6},    {8, 0, 0, 8, 0, 0, 8, 0, 0},
      {10, 0, 0, 0, 10, 0, 0, 0, 10}, {0, 0, 12, 0, 12, 0, 12, 0, 0},
      {0, 0, 0, 0, 0, 0, 14, 14, 14}, {16, 0, 0, 16, 0, 0, 16, 0, 0}};

  // An array of images
  Image images[] = {Image( VectorInt( data[0], 9 ), 3, 3 ),
                    Image( VectorInt( data[1], 9 ), 3, 3 ),
                    Image( VectorInt( data[2], 9 ), 3, 3 ),
                    Image( VectorInt( data[3], 9 ), 3, 3 ),
                    Image( VectorInt( data[4], 9 ), 3, 3 ),
                    Image( VectorInt( data[5], 9 ), 3, 3 ),
                    Image( VectorInt( data[6], 9 ), 3, 3 ),
                    Image( VectorInt( data[7], 9 ), 3, 3 )};

  // Construct a vector of images
  VectorImage vec = VectorImage( images, 8 );

  int   test_img[9] = {13, 13, 13, 0, 0, 0, 0, 0, 0};
  Image test        = Image( VectorInt( test_img, 9 ), 3, 3 );

  ECE2400_CHECK_TRUE( vec.find_closest_linear( test ) == images[0] );

  vec.sort();
  ECE2400_CHECK_TRUE( vec.find_closest_binary( test, 4 ) == images[3] );
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

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_simple_push_back();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_at_out_of_bound();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_construct();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_find_simple();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_find_empty();
  if ( ( __n == 0 ) || ( __n == 6  ) ) test_case_6_find_closest_linear();
  if ( ( __n == 0 ) || ( __n == 7  ) ) test_case_7_find_closest_linear_empty();
  if ( ( __n == 0 ) || ( __n == 8  ) ) test_case_8_find_closest_binary();
  if ( ( __n == 0 ) || ( __n == 9  ) ) test_case_9_find_closest_binary_empty();
  if ( ( __n == 0 ) || ( __n == 10 ) ) test_case_10_find_closest_binary_unsorted();
  if ( ( __n == 0 ) || ( __n == 11 ) ) test_case_11_sort_simple();
  if ( ( __n == 0 ) || ( __n == 12 ) ) test_case_12_subscript();
  if ( ( __n == 0 ) || ( __n == 13 ) ) test_case_13_copy();
  if ( ( __n == 0 ) || ( __n == 14 ) ) test_case_14_assignment_empty();
  if ( ( __n == 0 ) || ( __n == 15 ) ) test_case_15_assignment_non_empty();
  if ( ( __n == 0 ) || ( __n == 16 ) ) test_case_16_self_assignment();
  if ( ( __n == 0 ) || ( __n == 17 ) ) test_case_17_assign_twice();
  if ( ( __n == 0 ) || ( __n == 18 ) ) test_case_18_copy_twice();
  if ( ( __n == 0 ) || ( __n == 19 ) ) test_case_19_assign_empty();
  if ( ( __n == 0 ) || ( __n == 20 ) ) test_case_20_copy_empty();
  if ( ( __n == 0 ) || ( __n == 21 ) ) test_case_21_find_closest_different();

  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Add your test cases here
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  return __failed;
}
// clang-format on
