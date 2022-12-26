//========================================================================
// VectorInt.cc
//========================================================================
// Implementation of VectorInt.

#include "VectorInt.h"

#include "ece2400-stdlib.h"
#include "sort-int.h"

//------------------------------------------------------------------------
// VectorInt
//------------------------------------------------------------------------
// The default constructor for VectorInt class

VectorInt::VectorInt()
{
  m_maxsize = 10;
  m_data    = new int[m_maxsize];
  m_size    = 0;
}

//------------------------------------------------------------------------
// ~VectorInt
//------------------------------------------------------------------------
// The default deconstructor for VectorInt class

VectorInt::~VectorInt()
{
  delete[] m_data;
}

//------------------------------------------------------------------------
// VectorInt( const VectorInt& vec )
//------------------------------------------------------------------------
// The copy constructor for VectorInt class that takes in a VectorInt

VectorInt::VectorInt( const VectorInt& vec )
{
  m_maxsize = vec.m_maxsize;
  m_data    = new int[m_maxsize];
  m_size    = vec.m_size;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = vec.m_data[i];
  }
}

//------------------------------------------------------------------------
// VectorInt( int* array, int size )
//------------------------------------------------------------------------
// The non default constructor for VectorInt class that takes in an array
// and a size for the array

VectorInt::VectorInt( int* array, int size )
{
  m_maxsize = size * 2;
  m_data    = new int[m_maxsize];
  m_size    = size;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = array[i];
  }
}

//------------------------------------------------------------------------
// size
//------------------------------------------------------------------------
// A function that returns the size of the VectorInt

int VectorInt::size() const
{
  return m_size;
}

//------------------------------------------------------------------------
// push_back
//------------------------------------------------------------------------
// A function that adds the given value to the end of the VectorInt's m_data
// array using the value that it takes in

void VectorInt::push_back( int value )
{
  int* temp = m_data;
  if ( m_size + 1 > m_maxsize ) {
    m_maxsize *= 2;
    m_size++;
    m_data = new int[m_maxsize];
    for ( int i = 0; i < m_size - 1; i++ ) {
      m_data[i] = temp[i];
    }
    m_data[m_size - 1] = value;
    delete[] temp;
  }
  else {
    m_size++;
    m_data[m_size - 1] = value;
  }
}

//------------------------------------------------------------------------
// contains
//------------------------------------------------------------------------
// A function that returns 1 if the given value is in the data of the VectorInt

bool VectorInt::contains( int value ) const
{
  for ( int i = 0; i < m_size; i++ ) {
    if ( m_data[i] == value ) {
      return 1;
    }
  }
  return 0;
}

//------------------------------------------------------------------------
// absvalue
//------------------------------------------------------------------------
// A helper function that returns the absolute value of the value it takes in

int absvalue( int value )
{
  if ( value < 0 ) {
    return value * -1;
  }
  return value;
}

//------------------------------------------------------------------------
// find_closest_linear
//------------------------------------------------------------------------
// A function that returns the closest value in the VectorInt's array to the
// given value using a linear search

int VectorInt::find_closest_linear( int value ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }
  int smallestdiff = absvalue( value - m_data[0] );
  int sdidx        = 0;
  for ( int i = 1; i < m_size; i++ ) {
    int absv = absvalue( value - m_data[i] );
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
// A function that returns the index of the closest value to val in range +- k.
// returns -1 if not found

int binary_search( VectorInt vec, int bot, int top, int val, int k )
{
  // intialize middle index and value at middle index
  int middle_idx = ( ( top - bot ) / 2 ) + bot;
  int middle_val = vec.at( middle_idx );

  if ( bot <= top ) {
    // base case: middle value is in range of value +- k
    if ( ( val - k < middle_val && middle_val < val + k ) ||
         val == middle_val ) {
      // return middle
      return middle_idx;
    }
    // recursive cases:
    // case 1: value is greater than the value at the middle index
    if ( val > middle_val ) {
      // search top half
      return binary_search( vec, middle_idx + 1, top, val, k );
    }
    // case 2: value is less than the value at the middle index
    if ( val < middle_val ) {
      // search bottom half
      return binary_search( vec, bot, middle_idx - 1, val, k );
    }
  }
  // the function can not find a value in range
  return -1;
}

//------------------------------------------------------------------------
// find_closest_binary
//------------------------------------------------------------------------
// A function that finds the closest value to value in range k using binary
// search

int VectorInt::find_closest_binary( int value, int k ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }

  for ( int i = 0; i < size() - 1; i++ ) {
    if ( m_data[i] > m_data[i + 1] ) {
      ece2400::InvalidArgument e =
          ece2400::InvalidArgument( "Vector is not sorted" );
      throw e;
    }
  }
  // find index of closest value in range using binary search
  int idx = binary_search( *this, 0, size() - 1, value, k - 1 );
  // return idx;
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
  int smallestdiff = abs( value - at( idx ) );
  // loop through idk - k/2 to idx + k/2
  for ( int i = loidx; i <= hiidx; i++ ) {
    int absv = absvalue( value - m_data[i] );
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
// sort
//------------------------------------------------------------------------
// A function that sorts the array of the VectorInt using sort_int()

void VectorInt::sort()
{
  sort_int( m_data, m_size );
}

//------------------------------------------------------------------------
// print
//------------------------------------------------------------------------
// A function that prints out the array of the VectorInt

void VectorInt::print() const
{
  printf( "[ " );
  for ( int i = 0; i < m_size - 1; i++ ) {
    printf( "%d, ", m_data[i] );
  }
  printf( "%d ]\n", m_data[m_size - 1] );
}

//------------------------------------------------------------------------
// at
//------------------------------------------------------------------------
// A function that returns the value at the index idx in the VectorInt's array

int VectorInt::at( int idx ) const
{
  if ( m_size == 0 || idx > m_size - 1 ) {
    ece2400::OutOfRange e;
    throw e;
  }
  return m_data[idx];
}

//------------------------------------------------------------------------
// operator[]
//------------------------------------------------------------------------
// An override function for the [] operator that returns the value at idx in
// the VectorInt's array

int VectorInt::operator[]( int idx ) const
{
  return m_data[idx];
}

//------------------------------------------------------------------------
// operator=
//------------------------------------------------------------------------
// An override function for the = operator that assigns the VectorInt to
// the given VectorInt vec

VectorInt& VectorInt::operator=( const VectorInt& vec )
{
  if ( this != &vec ) {
    m_maxsize = vec.m_maxsize;
    delete[] m_data;
    m_data = new int[m_maxsize];
    m_size = vec.m_size;
    for ( int i = 0; i < m_size; i++ ) {
      m_data[i] = vec.m_data[i];
    }
  }
  return *this;
}