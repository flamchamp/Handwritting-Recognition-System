//========================================================================
// hrs-linear-search-directed-test.cc
//========================================================================
// Directed test cases for HRSLinearSearch.

#include "HRSLinearSearch.h"
#include "Image.h"
#include "Vector.h"
#include "ece2400-stdlib.h"
#include "mnist-utils.h"
#include <cstdlib>
#include <iostream>

//------------------------------------------------------------------------
// Inputs
//------------------------------------------------------------------------

#include "digits.dat"

// The data included is as follows:
//
//     Digit    | Label
//     ---------+-------
//     digit0   | 5
//     digit1   | 3
//     digit2   | 2
//     digit3   | 1
//     digit4   | 1
//     digit5   | 6
//     digit6   | 5
//     digit7   | 8
//     digit8   | 9
//     digit9   | 7
//     digit10  | 0
//     digit11  | 7
//     digit12  | 4
//     digit13  | 0
//

//------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------

const std::string mnsit_dir = "/classes/ece2400/mnist/";
const int         ncols     = 28;
const int         nrows     = 28;
const int         img_size  = nrows * ncols;

//------------------------------------------------------------------------
// test_case_1_classify_zero
//------------------------------------------------------------------------

void test_case_1_classify_zero()
{
  std::printf( "\n%s\n", __func__ );

  Image test_img( Vector<int>( digit10_image, img_size ), ncols, nrows );

  // Train with the first 5 MNIST training images

  Vector<Image> img_vec;

  std::string image_path = mnsit_dir + "training-images-tiny.bin";
  std::string label_path = mnsit_dir + "training-labels-tiny.bin";

  read_labeled_images( image_path, label_path, img_vec, 5 );

  // You may uncommment these prints to see the images

  // std::cout << "training images" << std::endl;
  // for ( int i = 0; i < 5; i++ ){
  //   img_vec[i].print();
  //   std::cout << "label:" << img_vec[i].get_label() << std::endl;
  // }
  // std::cout << "\ntesting image" << std::endl;
  // test_img.print();

  // Train the classifier
  HRSLinearSearch clf;
  clf.train( img_vec );

  // Check the predicted result
  ECE2400_CHECK_CHAR_EQ( clf.classify( test_img ).get_label(), digit10_label );
}

//------------------------------------------------------------------------
// test_case_2_classify_seven
//------------------------------------------------------------------------

void test_case_2_classify_seven()
{
  std::printf( "\n%s\n", __func__ );

  Image test_img = Image( Vector<int>( digit9_image, img_size ), ncols, nrows );

  // Train with the first 20 MNIST training images

  Vector<Image> img_vec;

  std::string image_path = mnsit_dir + "training-images-small.bin";
  std::string label_path = mnsit_dir + "training-labels-small.bin";

  read_labeled_images( image_path, label_path, img_vec, 20 );

  // You may uncommment these prints to see the images

  // std::cout << "training images" << std::endl;
  // for ( int i = 0; i < 20; i++ ){
  //   img_vec[i].print();
  //   std::cout << "label:" << img_vec[i].get_label() << std::endl;
  // }
  // std::cout << "\ntesting image" << std::endl;
  // test_img.print();

  // Train the classifier

  HRSLinearSearch clf;
  clf.train( img_vec );

  // Check the predicted result
  ECE2400_CHECK_CHAR_EQ( clf.classify( test_img ).get_label(), digit9_label );
}

//------------------------------------------------------------------------
// test_case_3_multiple_digits
//------------------------------------------------------------------------

void test_case_3_multiple_digits()
{
  std::printf( "\n%s\n", __func__ );

  // Train with the first 1000 MNIST training images

  Vector<Image> img_vec;

  std::string image_path = mnsit_dir + "training-images-small.bin";
  std::string label_path = mnsit_dir + "training-labels-small.bin";

  read_labeled_images( image_path, label_path, img_vec, 1000 );

  // Get all digits from the .dat file

  Image img0( Vector<int>( digit0_image, img_size ), ncols, nrows );
  Image img1( Vector<int>( digit1_image, img_size ), ncols, nrows );
  Image img2( Vector<int>( digit2_image, img_size ), ncols, nrows );
  Image img3( Vector<int>( digit3_image, img_size ), ncols, nrows );
  Image img4( Vector<int>( digit4_image, img_size ), ncols, nrows );
  Image img5( Vector<int>( digit5_image, img_size ), ncols, nrows );
  Image img6( Vector<int>( digit6_image, img_size ), ncols, nrows );
  Image img7( Vector<int>( digit7_image, img_size ), ncols, nrows );

  // Train the classifier

  HRSLinearSearch clf;
  clf.train( img_vec );

  // Classify and check the predicted results

  ECE2400_CHECK_CHAR_EQ( clf.classify( img0 ).get_label(), digit0_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img1 ).get_label(), digit1_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img2 ).get_label(), digit2_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img3 ).get_label(), digit3_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img4 ).get_label(), digit4_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img5 ).get_label(), digit5_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img6 ).get_label(), digit6_label );
  ECE2400_CHECK_CHAR_EQ( clf.classify( img7 ).get_label(), digit7_label );
}

//------------------------------------------------------------------------
// test_case_4_tiny_accuracy
//------------------------------------------------------------------------

void test_case_4_tiny_accuracy()
{
  std::printf( "\n%s\n", __func__ );

  const int training_size = 10;
  const int testing_size  = 10;

  // Read the training images

  Vector<Image> v_train;

  std::string image_path = mnsit_dir + "training-images-tiny.bin";
  std::string label_path = mnsit_dir + "training-labels-tiny.bin";

  read_labeled_images( image_path, label_path, v_train, training_size );

  // Read the testing images

  Vector<Image> v_test;

  image_path = mnsit_dir + "testing-images-tiny.bin";
  label_path = mnsit_dir + "testing-labels-tiny.bin";

  read_labeled_images( image_path, label_path, v_test, testing_size );

  // Train and classify

  HRSLinearSearch clf;

  double accuracy = train_and_classify( clf, v_train, v_test );
  std::cout << "Accuracy: " << accuracy << std::endl;

  // Accuracy should be...

  double expected_accuracy = 0.6;
  double tolerance         = 0.015;

  ECE2400_CHECK_APPROX_EQ( accuracy / expected_accuracy, 1.0, tolerance );
}

//------------------------------------------------------------------------
// test_case_5_small_accuracy
//------------------------------------------------------------------------

void test_case_5_small_accuracy()
{
  std::printf( "\n%s\n", __func__ );

  const int training_size = 600;
  const int testing_size  = 100;

  // Read the training images

  Vector<Image> v_train;

  std::string image_path = mnsit_dir + "training-images-small.bin";
  std::string label_path = mnsit_dir + "training-labels-small.bin";

  read_labeled_images( image_path, label_path, v_train, training_size );

  // Read the testing images

  Vector<Image> v_test;

  image_path = mnsit_dir + "testing-images-small.bin";
  label_path = mnsit_dir + "testing-labels-small.bin";

  read_labeled_images( image_path, label_path, v_test, testing_size );

  // Train and classify

  HRSLinearSearch clf;

  double accuracy = train_and_classify( clf, v_train, v_test );
  std::cout << "Accuracy: " << accuracy << std::endl;

  // Accuracy should be...

  double expected_accuracy = 0.83;
  double tolerance         = 0.015;

  ECE2400_CHECK_APPROX_EQ( accuracy / expected_accuracy, 1.0, tolerance );
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

// clang-format off
int main( int argc, char** argv )
{
  using namespace ece2400;

  __n = ( argc == 1 ) ? 0 : std::atoi( argv[1] );

  if ( ( __n == 0 ) || ( __n == 1  ) ) test_case_1_classify_zero();
  if ( ( __n == 0 ) || ( __n == 2  ) ) test_case_2_classify_seven();
  if ( ( __n == 0 ) || ( __n == 3  ) ) test_case_3_multiple_digits();
  if ( ( __n == 0 ) || ( __n == 4  ) ) test_case_4_tiny_accuracy();
  if ( ( __n == 0 ) || ( __n == 5  ) ) test_case_5_small_accuracy();

  return __failed;
}
// clang-format on
