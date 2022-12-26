//========================================================================
// HRSLinearSearch.cc
//========================================================================
// Handwritten recognition system that uses linear search.

#include "HRSLinearSearch.h"
#include "Image.h"
#include "VectorImage.h"

//------------------------------------------------------------------------
// HRSLinearSearch
//------------------------------------------------------------------------
// The default constructor for the HRSLinearSearch class

HRSLinearSearch::HRSLinearSearch()
{
  m_vimage = VectorImage();
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSLinearSearch equal to the
// given vector

void HRSLinearSearch::train( const VectorImage& vec )
{
  m_vimage = vec;
}

//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using linear
// search method

Image HRSLinearSearch::classify( const Image& img )
{
  return m_vimage.find_closest_linear( img );
}