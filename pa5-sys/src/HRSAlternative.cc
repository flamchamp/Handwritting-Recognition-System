//========================================================================
// HRSAlternative.cc
//========================================================================
// Alternative HRS implementation.

#include "HRSAlternative.h"
#include "IHandwritingRecSys.h"
#include "Image.h"
#include "Vector.h"
#include <cstddef>
#include <iostream>

//------------------------------------------------------------------------
// HRSAlternative
//------------------------------------------------------------------------
// The default constructor for the HRSAlternative class
HRSAlternative::HRSAlternative()
{
  m_vimage = Vector<Image>();
}

//------------------------------------------------------------------------
// train
//------------------------------------------------------------------------
// A function that sets the array of the HRSAlternative equal to the
// given vector

void HRSAlternative::train( const Vector<Image>& vec )
{
  m_vimage = vec;
}

// Distance Function for Images
int distance_euclidean( const Image& a, const Image& b )
{
  return a.distance( b );
}

//------------------------------------------------------------------------
// linear_search
//------------------------------------------------------------------------
// A function that returns the closest value in the Vector's array to the
// given value using a linear search
void linear_search( const Vector<Image>& vec, Image* store_data,
                    const Image& value, int begin, int end )
{
  int smallestdiff = distance_euclidean( value, vec[0] );
  int sdidx        = begin;
  for ( int i = begin + 1; i < end; i++ ) {
    int absv = distance_euclidean( value, vec[i] );
    if ( smallestdiff > absv ) {
      smallestdiff = absv;
      sdidx        = i;
    }
  }
  *store_data = vec[sdidx];
}

Image parallel_linear_search( const Vector<Image>& vec, const Image& value )
{
  if ( vec.size() == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }
  int mid1 = vec.size() / 4;
  int mid2 = vec.size() / 2;
  int mid3 = 3 * ( vec.size() / 4 );

  Image       store_data[4];
  std::thread thread0( &linear_search, vec, &store_data[0], value, 0, mid1 );
  std::thread thread1( &linear_search, vec, &store_data[1], value, mid1, mid2 );
  std::thread thread2( &linear_search, vec, &store_data[2], value, mid2, mid3 );
  linear_search( vec, &store_data[3], value, mid3, vec.size() );

  thread0.join();
  thread1.join();
  thread2.join();

  int   smallest_dist = distance_euclidean( store_data[3], value );
  Image smallest      = store_data[3];
  for ( int i = 0; i < 3; i++ ) {
    int distance = distance_euclidean( store_data[i], value );
    if ( distance < smallest_dist ) {
      smallest      = store_data[i];
      smallest_dist = distance;
    }
  }

  return smallest;
}

//------------------------------------------------------------------------
// classify
//------------------------------------------------------------------------
// A function that finds the closest Image to the given Image using linear
// search method

Image HRSAlternative::classify( const Image& img )
{
  return parallel_linear_search( m_vimage, img );
}
