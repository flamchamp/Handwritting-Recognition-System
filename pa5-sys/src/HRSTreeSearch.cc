//========================================================================
// HRSTreeSearch.cc
//========================================================================
// Definitions for HRSTreeSearch

#include "HRSTreeSearch.h"

#include "Image.h"
#include "Tree.h"
#include "Vector.h"

bool HRSTreeSearch::LessIntensity::operator()( const Image& a, const Image& b )
{
  return a.get_intensity() < b.get_intensity();
}

//------------------------------------------------------------------------
// HRSTreeSearch
//------------------------------------------------------------------------
// The default constructor for the HRSTreeSearch class
HRSTreeSearch::HRSTreeSearch( int k ) : m_training_set( k, LessIntensity() )
{
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSLinearSearch equal to the
// given vector

void HRSTreeSearch::train( const Vector<Image>& vec )
{
  for ( int i = 0; i < vec.size(); i++ ) {
    m_training_set.add( vec[i] );
  }
}

int HRSTreeSearch::Distance::operator()( const Image& a, const Image& b )
{
  return a.distance( b );
}
//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using binary
// search method
Image HRSTreeSearch::classify( const Image& img )
{
  return m_training_set.find_closest( img, Distance() );
}