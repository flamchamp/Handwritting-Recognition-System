//========================================================================
// VectorImage.cc
//========================================================================
// Implementation of VectorImage.

#include "VectorImage.h"

#include "Image.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"

//------------------------------------------------------------------------
// VectorImage
//------------------------------------------------------------------------
// The default constructor for the VectorImage class

VectorImage::VectorImage()
{
  m_maxsize  = 10;
  m_size     = 0;
  m_data     = new Image[m_maxsize];
  m_issorted = false;
}

//------------------------------------------------------------------------
// ~VectorImage
//------------------------------------------------------------------------
// The default deconstructor for the VectorImage class

VectorImage::~VectorImage()
{
  delete[] m_data;
}

//------------------------------------------------------------------------
// VectorImage( const VectorImage& vec )
//------------------------------------------------------------------------
// The copy constructor for the VectorImage class copies the vec into the
// new VectorImage

VectorImage::VectorImage( const VectorImage& vec )
{
  m_maxsize  = vec.m_maxsize;
  m_data     = new Image[m_maxsize];
  m_size     = vec.m_size;
  m_issorted = vec.m_issorted;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = vec.m_data[i];
  }
}

//------------------------------------------------------------------------
// VectorImage( const VectorImage& vec )
//------------------------------------------------------------------------
// The non default constructor for the VectorImage class that takes in an
// array and the size for the array

VectorImage::VectorImage( Image* array, int size )
{
  m_maxsize  = size * 2;
  m_data     = new Image[m_maxsize];
  m_size     = size;
  m_issorted = false;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = array[i];
  }
}

//------------------------------------------------------------------------
// size
//------------------------------------------------------------------------
// A function that returns the size of a VectorImage

int VectorImage::size() const
{
  return m_size;
}

//------------------------------------------------------------------------
// push_back
//------------------------------------------------------------------------
// A function that adds the given Image to the back of the VectorImage's
// array and increases the size of the array if necessary

void VectorImage::push_back( const Image& img )
{
  Image* temp = m_data;
  if ( m_size + 1 > m_maxsize ) {
    m_maxsize *= 2;
    m_size++;
    m_data = new Image[m_maxsize];
    for ( int i = 0; i < m_size - 1; i++ ) {
      m_data[i] = temp[i];
    }
    m_data[m_size - 1] = img;
    delete[] temp;
  }
  else {
    m_size++;
    m_data[m_size - 1] = img;
  }
  m_issorted = false;
}

//------------------------------------------------------------------------
// contains
//------------------------------------------------------------------------
// A function that returns 1 if the VectorImage contains the given Image

bool VectorImage::contains( const Image& img ) const
{
  for ( int i = 0; i < m_size; i++ ) {
    if ( m_data[i] == img ) {
      return 1;
    }
  }
  return 0;
}

//------------------------------------------------------------------------
// absvalueimage
//------------------------------------------------------------------------
// A function that returns the absolute value of the given value

int absvalueimage( int value )
{
  if ( value < 0 ) {
    return value * -1;
  }
  return value;
}

//------------------------------------------------------------------------
// find_closest_linear
//------------------------------------------------------------------------
// A function that returns the closest image (using distance) in the
// VectorImage's array to the given Image using a linear search

Image VectorImage::find_closest_linear( const Image& img ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e;
    throw e;
  }
  int smallestdiff = absvalueimage( m_data[0].distance( img ) );
  int sdidx        = 0;
  for ( int i = 1; i < m_size; i++ ) {
    int absv = absvalueimage( m_data[i].distance( img ) );
    if ( smallestdiff > absv ) {
      smallestdiff = absv;
      sdidx        = i;
    }
  }
  return m_data[sdidx];
}

//------------------------------------------------------------------------
// binary_search
//------------------------------------------------------------------------
// A function that returns the index of the closest Image to the given
// Image in a given range using binary search algorithm. Returns -1 if not
// found

int binary_search( Image* vimg, int bot, int top, int val, int k )
{
  // intialize middle index and value at middle index
  int middle_idx = ( ( top - bot ) / 2 ) + bot;
  int middle_val = vimg[middle_idx].get_intensity();

  if ( bot <= top ) {
    // base case: middle value is in range of value +- k
    if ( ( val - k < middle_val && middle_val < val + k ) ||
         val == middle_val ) {
      return middle_idx;
    }
    // recursive cases:
    // case 1: value is greater than the value at the middle index
    if ( val > middle_val ) {
      // search top half
      return binary_search( vimg, middle_idx + 1, top, val, k );
    }
    // case 2: value is less than the value at the middle index
    if ( val < middle_val ) {
      // search bottom half
      return binary_search( vimg, bot, middle_idx - 1, val, k );
    }
  }
  // function cannot find a value in range
  return -1;
}

//------------------------------------------------------------------------
// find_closest_binary
//------------------------------------------------------------------------
// A function that finds the index of the closest Image to the given Image
// in a given range using binary search. Then uses a linear search to find
// the closest Image based on distance in a certain range of said index

Image VectorImage::find_closest_binary( const Image& img, int k ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }
  // check if its not sorted
  if ( !m_issorted ) {
    ece2400::InvalidArgument e =
        ece2400::InvalidArgument( "Vector is not sorted" );
    throw e;
  }
  // find index of closest value in range using binary search
  int idx = -1;
  int kt  = 0;
  while ( idx == -1 ) {
    idx = binary_search( m_data, 0, size() - 1, img.get_intensity(), kt );
    kt  = kt + 5;
  }
  // CHECK IF IDX - K/2 IS LESS THAN 0 OR GREATER THAN SIZE
  int loidx = idx - k / 2;
  int hiidx = idx + k / 2;
  if ( loidx < 0 ) {
    loidx = 0;
  }
  if ( hiidx > size() - 1 ) {
    hiidx = size() - 1;
  }
  // initialize smallest difference value and smallest difference index
  int sdidx        = idx;
  int smallestdiff = abs( m_data[idx].distance( img ) );
  // loop through idk - k/2 to idx + k/2
  for ( int i = loidx; i <= hiidx; i++ ) {
    int absv = absvalueimage( m_data[i].distance( img ) );
    if ( smallestdiff > absv ) {
      smallestdiff = absv;
      // record smallest idx found
      sdidx = i;
    }
  }
  // return that smallest idx
  return m_data[sdidx];
}

//------------------------------------------------------------------------
// at
//------------------------------------------------------------------------
// A function that returns the Image at the given index in the
// VectorImages array

Image VectorImage::at( int idx ) const
{
  if ( m_size == 0 || idx > m_size - 1 ) {
    ece2400::OutOfRange e;
    throw e;
  }
  return m_data[idx];
}

void VectorImage::print() const
{
  // DID NOT FINISH THE PRINT FUNCTION
  // printf( "[ " );
  // for ( int i = 0; i < m_size - 1; i++ ) {
  //  printf( "%d, ", m_data[i] );
  //}
  // printf( "%d ]\n", m_data[m_size - 1] );
}

//------------------------------------------------------------------------
// sort
//------------------------------------------------------------------------
// A function that sorts the array of the VectorImages using sort_image().
// Also sets the sorted tag of the VectorImage to true.

void VectorImage::sort()
{
  sort_image( m_data, m_size );
  m_issorted = true;
}

//------------------------------------------------------------------------
// operator[]
//------------------------------------------------------------------------
// An override function for the [] operator that returns the Image at the
// given index in the VectorImage's array

Image VectorImage::operator[]( int idx ) const
{
  return m_data[idx];
}

//------------------------------------------------------------------------
// operator=
//------------------------------------------------------------------------
// An override function for the = operator that assigns the VectorImage to
// the given VectorImage

VectorImage& VectorImage::operator=( const VectorImage& img )
{
  if ( this != &img ) {
    m_maxsize = img.m_maxsize;
    delete[] m_data;
    m_data = new Image[m_maxsize];
    m_size = img.m_size;
    for ( int i = 0; i < m_size; i++ ) {
      m_data[i] = img.m_data[i];
    }
  }
  return *this;
}