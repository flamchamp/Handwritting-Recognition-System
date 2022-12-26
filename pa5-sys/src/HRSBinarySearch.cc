//========================================================================
// HRSBinarySearch.cc
//========================================================================
// Handwritten recognition system that uses binary search.

#include "HRSBinarySearch.h"
#include "IHandwritingRecSys.h"
#include "Image.h"
#include "Vector.h"
#include <cstddef>
#include <iostream>

//------------------------------------------------------------------------
// HRSBinarySearch
//------------------------------------------------------------------------
// The default constructor for the HRSBinarySearch class
HRSBinarySearch::HRSBinarySearch( int k )
{
  m_vimage = Vector<Image>();
  m_k      = k;
}

// Image compare function
bool less_intensity( const Image& a, const Image& b )
{
  return a.get_intensity() < b.get_intensity();
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSBinarySearch equal to the
// given vector

void HRSBinarySearch::train( const Vector<Image>& vec )
{
  m_vimage = vec;
  m_vimage.sort( less_intensity );
  printf( "finished sort\n" );
}

// Distance Function for Images
int distance_euclidean( const Image& a, const Image& b )
{
  return a.distance( b );
}

//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using binary
// search method
Image HRSBinarySearch::classify( const Image& img )
{
  return m_vimage.find_closest_binary( img, m_k, distance_euclidean,
                                       less_intensity );
}