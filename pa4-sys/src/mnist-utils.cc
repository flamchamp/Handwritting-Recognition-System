//========================================================================
// mnist-utils.cc
//========================================================================
// Utility functions for MNSIT dataset.
//
// Author: Yanghui Ou
//   Date: Nov 6, 2019

#include "mnist-utils.h"
#include "IHandwritingRecSys.h"
#include "Image.h"
#include "VectorInt.h"
#include <cassert>
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------

const int mnist_ncols = 28;
const int mnist_nrows = 28;
const int mnist_size  = mnist_nrows * mnist_ncols;

const char* cursor_u = "\033[A";  // Move cursor up one line
const char* cursor_d = "\033[B";  // Move cursor up one line
const char* cursor_e = "\033[K";  // Erase to end of the line

//------------------------------------------------------------------------
// read_labeled_images
//------------------------------------------------------------------------
// Reads the images and labels file and fills a VectorImage with the
// corresponding labeled images.

void read_labeled_images( const std::string& images_path,
                          const std::string& labels_path, VectorImage& vec,
                          int size )
{
  std::ifstream myifs;

  // MNIST has 4 misc values in image bin and 2 in label bin
  const int n_misc_in_image_file = 4;
  const int n_misc_in_label_file = 2;

  //----------------------------------------------------------------------
  // Read images
  //----------------------------------------------------------------------

  Image* labeled_imgaes = new Image[size];
  int*   data           = new int[mnist_size];

  // Open binary file

  myifs.open( images_path, std::ios::in | std::ios::binary );

  assert( myifs.is_open() );

  // Skip the miscellaneous metadata (4B each)

  int misc = 0;
  for ( int i = 0; i < n_misc_in_image_file; i++ )
    myifs.read( (char*) &misc, 4 );

  // Read each image (28 x 28 bytes) and add to the Image

  for ( int idx = 0; idx < size; idx++ ) {
    for ( int i = 0; i < mnist_size; i++ ) {
      int tmp = 0;
      myifs.read( (char*) &tmp, 1 );
      data[i] = tmp;
    }

    // Add this image to the array

    labeled_imgaes[idx] =
        Image( VectorInt( data, mnist_size ), mnist_ncols, mnist_nrows );
  }

  // Close file

  myifs.close();

  //----------------------------------------------------------------------
  // Read images
  //----------------------------------------------------------------------

  // Open binary file

  myifs.open( labels_path, std::ios::in | std::ios::binary );

  assert( myifs.is_open() );

  // Skip the miscellaneous metadata (4B each)

  for ( int i = 0; i < n_misc_in_label_file; i++ )
    myifs.read( (char*) &misc, 4 );

  // Read each label and label the corresponding image

  for ( int idx = 0; idx < size; idx++ ) {
    // Read the label
    int tmp = 0;
    myifs.read( (char*) &tmp, 1 );
    char label_char = (char) ( '0' + tmp );

    // Set label for the corresponding image
    labeled_imgaes[idx].set_label( label_char );
  }

  //----------------------------------------------------------------------
  // Copy to the image vector
  //----------------------------------------------------------------------

  vec = VectorImage();  // Clear the data
  for ( int i = 0; i < size; i++ )
    vec.push_back( labeled_imgaes[i] );

  // Clear dynamic memory

  delete[] data;
  delete[] labeled_imgaes;
}

//------------------------------------------------------------------------
// train_and_classify
//------------------------------------------------------------------------
// Takes a handwriting recognition system, trains it with all of the
// labeled images in the training set, classifies all of the images in the
// inference set, and then checks how many classifications are correct,
// returning the accuracy as a double.

double train_and_classify( IHandwritingRecSys& hrs, const VectorImage& v_train,
                           const VectorImage& v_test )
{
  // Return 0 if testing set is empty

  if ( v_test.size() == 0 )
    return 0;

  // Train the classifier

  hrs.train( v_train );

  // Classify the images in the testing set

  int correct = 0;
  int total   = v_test.size();

  for ( int i = 0; i < total; i++ ) {
    // Check predicted results
    // Scrub label from input image
    Image test_image = v_test[i];
    test_image.set_label( '?' );

    Image prediction = hrs.classify( test_image );

    char predicted_label = prediction.get_label();
    char correct_label   = v_test[i].get_label();
    if ( predicted_label == correct_label )
      correct++;

    // Prints out the number of correct predictions per 1000 images

    if ( ( i + 1 ) % 1000 == 0 ) {
      std::cout << "#images tested         : " << i + 1 << std::endl;
      std::cout << " - correctly predicted : " << i + 1 << std::endl;
    }
  }

  // Calculate accuracy

  return (double) correct / (double) total;
}

//------------------------------------------------------------------------
// classify_with_progress_bar
//------------------------------------------------------------------------
// Takes a handwriting recognition system, runs classfication on the given
// testing set and prints a progress bar, and returns the accuracy.

double classify_with_progress_bar( IHandwritingRecSys& hrs,
                                   const VectorImage&  v_test )
{
  // Return 0 if testing set is empty to avoid devide by 0

  const int test_size = v_test.size();
  if ( test_size == 0 )
    return 0;

  // Set up progress bar for inference

  int n_frac       = 70;
  int frac_size    = ( test_size > n_frac ) ? test_size / n_frac : 1;
  int len_prog_bar = test_size / frac_size;

  // Run inference

  int num_correct = 0;

  for ( int i = 0; i < test_size; i++ ) {
    // Get classification result
    // Scrub label from input image
    Image test_image = v_test[i];
    test_image.set_label( '?' );

    Image clf_result = hrs.classify( test_image );

    char predicted_label = clf_result.get_label();
    char correct_label   = v_test[i].get_label();
    if ( predicted_label == correct_label )
      num_correct++;

    // Progress bar
    if ( i % frac_size == 0 ) {
      int n_markers = i / frac_size;

      std::cout << "[ ";

      for ( int j = 1; j < n_markers; j++ )
        std::cout << "=";

      std::cout << ">";

      for ( int j = 0; j < len_prog_bar - n_markers; j++ )
        std::cout << ".";

      std::cout << " ]";
      std::cout << cursor_e;
      std::cout << std::endl;

      std::cout << " - classifying image " << i + 1 << " of " << test_size;
      std::cout << cursor_e;
      std::cout << std::endl;

      std::cout << " - #correct classifications : " << num_correct;
      std::cout << cursor_e;
      std::cout << std::endl;

      std::cout << cursor_u << cursor_u << cursor_u;
    }
  }

  // Delete output and reset cursor
  std::cout << cursor_e << cursor_d << cursor_e << cursor_d << cursor_e
            << cursor_u << cursor_u;

  return (double) num_correct / (double) test_size;
}
