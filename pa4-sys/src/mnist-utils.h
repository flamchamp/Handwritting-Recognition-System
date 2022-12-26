//========================================================================
// mnist-utils.h
//========================================================================
// Utility functions for MNSIT dataset.
//
// Author: Yanghui Ou
//   Date: Nov 6, 2019

#ifndef MNIST_UTILS_H
#define MNIST_UTILS_H

#include "VectorImage.h"
#include <cstddef>
#include <string>

class IHandwritingRecSys;

//------------------------------------------------------------------------
// read_labeled_images
//------------------------------------------------------------------------
// Reads the images and labels file and fills a VectorImage with the
// corresponding labeled images.

void read_labeled_images( const std::string& images_path,
                          const std::string& labels_path, VectorImage& vec,
                          int size );

//------------------------------------------------------------------------
// train_and_classify
//------------------------------------------------------------------------
// Takes a handwriting recognition system, trains it with all of the
// labeled images in the training set, classifies all of the images in the
// inference set, and then checks how many classifications are correct,
// returning the accuracy as a double.

double train_and_classify( IHandwritingRecSys& hrs, const VectorImage& v_train,
                           const VectorImage& v_test );

//------------------------------------------------------------------------
// classify_with_progress_bar
//------------------------------------------------------------------------
// Takes a handwriting recognition system, runs classfication on the given
// testing set and prints a progress bar.

double classify_with_progress_bar( IHandwritingRecSys& hrs,
                                   const VectorImage&  v_test );

#endif  // MNIST_UTILS_H
