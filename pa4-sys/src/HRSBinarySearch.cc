//========================================================================
// HRSBinarySearch.cc
//========================================================================
// Handwritten recognition system that uses linear search.

#include "HRSBinarySearch.h"
#include "IHandwritingRecSys.h"
#include "Image.h"
#include "VectorImage.h"
#include <cstddef>

//------------------------------------------------------------------------
// HRSBinarySearch
//------------------------------------------------------------------------
// The default constructor for the HRSBinarySearch class

HRSBinarySearch::HRSBinarySearch( int k )
{
  m_vimage = VectorImage();
  m_k      = k;
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSBinarySearch equal to the
// given vector

void HRSBinarySearch::train( const VectorImage& vec )
{
  m_vimage = vec;
  m_vimage.sort();
}

//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using binary
// search method

Image HRSBinarySearch::classify( const Image& img )
{
  return m_vimage.find_closest_binary( img, m_k );
}
