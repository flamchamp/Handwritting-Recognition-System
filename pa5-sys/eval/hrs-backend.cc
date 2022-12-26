//========================================================================
// backend.cc
//========================================================================
// Backend for the python GUI program.
//
// Author : Kaishuo Cheng, Yanghui Ou
//   Date : Summer 2019

#include <iostream>
#include <fstream>
#include <assert.h>
#include "ece2400-stdlib.h"
#include "mnist-utils.h"
#include "Vector.h"
#include "Image.h"
#include "HRSLinearSearch.h"
#include "HRSBinarySearch.h"
#include "HRSTreeSearch.h"
#include "HRSTableSearch.h"
#include "HRSAlternative.h"

using namespace std;

//------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------

const std::string  mnsit_dir     = "/classes/ece2400/mnist/";
const int training_size = 60000;
const int ncols         = 28;
const int nrows         = 28;

//------------------------------------------------------------------------
// read_image
//------------------------------------------------------------------------

void read_image( const char* file_name, Vector<int>& vec )
{
  ifstream img_file( file_name );

  // Abort if file does not exists
  if ( !img_file ) {
    std::cout << file_name << " does not exists!" << std::endl;
    assert( false );
  }

  std::string line;

  // Parse data line by line
  while( getline( img_file, line ) ) {
    long unsigned int pos;
    std::string token;
    while( ( pos = line.find( ' ' ) ) != std::string::npos ) {
      token = line.substr( 0, pos );
      vec.push_back( std::stoi( token ) );
      line.erase( 0, pos + 1 );
    }

    // If there is a remaining token
    if ( line.length() > 0 )
      vec.push_back( std::stoi( line ) );
  }
}

//------------------------------------------------------------------------
// main
//------------------------------------------------------------------------

int main( int argc, char** argv ) {

  // Read the image to classify from the txt file
  Vector<int> v_img;
  read_image( argv[1], v_img );

  assert( v_img.size() == ncols * nrows );

  Image img = Image( v_img, ncols, nrows );

  Vector<Image> v_training;

  // Reads images into training vector

  std::string image_path = mnsit_dir + "training-images.bin";
  std::string label_path = mnsit_dir + "training-labels.bin";

  read_labeled_images( image_path, label_path, v_training, training_size );

  std::string method = argv[2];

  double training_time;
  double infering_time;

  Image result;

  // Train and classify
  if ( method == "LinearSearch" ) {
    HRSLinearSearch hrs;

    // Training
    ece2400::timer_reset();
    hrs.train( v_training );
    training_time = ece2400::timer_get_elapsed();

    // Inference
    ece2400::timer_reset();
    result = hrs.classify( img );
    infering_time = ece2400::timer_get_elapsed();
  }

  else if ( method == "BinarySearch" ) {
    HRSBinarySearch hrs;

    // Training
    ece2400::timer_reset();
    hrs.train( v_training );
    training_time = ece2400::timer_get_elapsed();

    // Inference
    ece2400::timer_reset();
    result = hrs.classify( img );
    infering_time = ece2400::timer_get_elapsed();
  }

  else if ( method == "TreeSearch" ) {
    HRSTreeSearch hrs;

    // Training
    ece2400::timer_reset();
    hrs.train( v_training );
    training_time = ece2400::timer_get_elapsed();

    // Inference
    ece2400::timer_reset();
    result = hrs.classify( img );
    infering_time = ece2400::timer_get_elapsed();
  }

  else if ( method == "TableSearch" ) {
    HRSTableSearch hrs;

    // Training
    ece2400::timer_reset();
    hrs.train( v_training );
    training_time = ece2400::timer_get_elapsed();

    // Inference
    ece2400::timer_reset();
    result = hrs.classify( img );
    infering_time = ece2400::timer_get_elapsed();
  }

  else if ( method == "Alternative" ) {
    HRSAlternative hrs;

    // Training
    ece2400::timer_reset();
    hrs.train( v_training );
    training_time = ece2400::timer_get_elapsed();

    // Inference
    ece2400::timer_reset();
    result = hrs.classify( img );
    infering_time = ece2400::timer_get_elapsed();
  }

  std::cout << "Training Time: "    << training_time << std::endl;
  std::cout << "Inferene Time: "    << infering_time << std::endl;
  std::cout << "Prediction Label: " << result.get_label() << std::endl;
  std::cout << "Prediction Match: " << std::endl;

  // Print out the closest image

  if ( argc == 4 && std::string( argv[3] ) == "--pretty") {
    result.print();
  }
  else{
    // Print out numerical value
    for ( int i = 0; i < nrows; i++ ) {
      for ( int j = 0; j < ncols; j++ ) {
        std::cout << result.at( j, i ) << " ";
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
