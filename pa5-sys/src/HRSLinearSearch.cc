//========================================================================
// HRSLinearSearch.cc
//========================================================================
// Handwritten recognition system that uses linear search.

#include "HRSLinearSearch.h"
#include "Image.h"
#include <cstddef>
#include <iostream>

//------------------------------------------------------------------------
// HRSLinearSearch
//------------------------------------------------------------------------
// The default constructor for the HRSLinearSearch class

HRSLinearSearch::HRSLinearSearch()
{
  m_vimage = Vector<Image>();
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSLinearSearch equal to the
// given vector

void HRSLinearSearch::train( const Vector<Image>& vec )
{
  m_vimage = vec;
}

// Distance Function for Images
int distance_euclidean( const Image& a, const Image& b )
{
  return a.distance( b );
}

//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using linear
// search method

Image HRSLinearSearch::classify( const Image& img )
{
  return m_vimage.find_closest_linear( img, distance_euclidean );
}