//========================================================================
// hrs-alternative-eval.cc
//========================================================================
// Evalutaion program for HRSAlternative.

#include <cstddef>
#include <iostream>
#include <iomanip> // for std::setw
#include "ece2400-stdlib.h"
#include "mnist-utils.h"
#include "Vector.h"
#include "HRSAlternative.h"

//------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------

void print_help()
{
  std::cout << "usage: ./hrs-alternative-eval [<train_size>] [<test_size>]"
            << std::endl << std::endl
            << "Evaluation program for HRSAlternative. You must use "
            << "full training set to get the accuracy! "
            << "Full training set size and full testing set size"
            << "will be used if no arguments are specified."
            << std::endl << std::endl
            << "positional arguments:" << std::endl
            << "  train_size  Size of the training set. " << std::endl
            << "It has to be within (0, 60000]." << std::endl
            << "  test_size   Size of the testing set. " << std::endl
            << "It has to be within (0, 10000]." << std::endl;
}

//------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------

const std::string mnsit_dir          = "/classes/ece2400/mnist/";
const int         full_training_size = 60000;
const int         full_testing_size  = 10000;
const int         width              = 22;

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv )
{
  // Parse command line argument
  int testing_size;
  int training_size;

  if ( argc != 3 && argc != 1 ) {
    std::cout << "Invalid command line arguments!"
              << std::endl << std::endl;
    print_help();
    return 1;
  }

  if ( argc == 1 ) {
    training_size = full_training_size;
    testing_size  = full_testing_size;
  }

  else {
    training_size = atoi( argv[1] );
    testing_size  = atoi( argv[2] );

    // Check range
    if ( testing_size < 1 || testing_size > full_testing_size ) {
      std::cout << "Invalid testing size: " << testing_size
                << std::endl << std::endl;
      return 1;
    }

    // Check range
    if ( training_size < 1 || training_size > full_training_size ) {
      std::cout << "Invalid training size: " << training_size
                << std::endl << std::endl;
      return 1;
    }
  }

  Vector<Image> v_train;
  Vector<Image> v_test;

  std::cout << "Evaluating HRSAlternative..." << std::endl;
  std::cout << std::setw(width) << std::left
            << " - training size" << " = " << training_size << std::endl;
  std::cout << std::setw(width) << std::left
            << " - testing  size" << " = " << testing_size  << std::endl;

  // Reads images into training vector

  std::string image_path = mnsit_dir + "training-images.bin";
  std::string label_path = mnsit_dir + "training-labels.bin";

  read_labeled_images( image_path, label_path, v_train, training_size );

  // Reads images into testing vector

  image_path = mnsit_dir + "testing-images.bin";
  label_path = mnsit_dir + "testing-labels.bin";

  read_labeled_images( image_path, label_path, v_test, testing_size );

  // Instantiate a classifier

  HRSAlternative clf;

  // Time the training phase

  ece2400::timer_reset();

  clf.train( v_train );

  double training_time = ece2400::timer_get_elapsed();

  // Time the classification phase

  ece2400::timer_reset();

  double accuracy = classify_with_progress_bar( clf, v_test );
  double classification_time = ece2400::timer_get_elapsed();

  std::cout << std::setw(width) << std::left
            << " - training time" << " : " << training_time
            << " seconds" << std::endl;
  std::cout << std::setw(width) << std::left
            << " - classification time" << " : " << classification_time
            << " seconds" << std::endl;

  // Report accuracy only if using the full traininig dataset

  if ( training_size == full_training_size && testing_size == full_testing_size )
    std::cout << std::setw(width) << std::left
              << " - accuracy" << " : " << accuracy << std::endl;

  return 0;
}
