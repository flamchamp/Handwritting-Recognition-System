//========================================================================
// Vector.inl
//========================================================================
// Implementation of Vector.

#include "ece2400-stdlib.h"
#include "sort.h"
#include <iostream>
#include <thread>

//------------------------------------------------------------------------
// Vector
//------------------------------------------------------------------------
// The default constructor for Vector class
template <typename T>
Vector<T>::Vector()
{
  m_maxsize = 10;
  m_data    = new T[m_maxsize];
  m_size    = 0;
}

//------------------------------------------------------------------------
// ~Vector
//------------------------------------------------------------------------
// The default deconstructor for Vector class
template <typename T>
Vector<T>::~Vector()
{
  delete[] m_data;
}

//------------------------------------------------------------------------
// Vector( const Vector<T>& vec )
//------------------------------------------------------------------------
// The copy constructor for VectorInt class that takes in a VectorInt
template <typename T>
Vector<T>::Vector( const Vector<T>& vec )
{
  m_maxsize = vec.m_maxsize;
  m_data    = new T[m_maxsize];
  m_size    = vec.m_size;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = vec.m_data[i];
  }
}

//------------------------------------------------------------------------
// Vector( T* array, int size )
//------------------------------------------------------------------------
// The non default constructor for Vector class that takes in an array
// and a size for the array
template <typename T>
Vector<T>::Vector( T* array, int size )
{
  m_maxsize = size * 2;
  m_data    = new T[m_maxsize];
  m_size    = size;
  for ( int i = 0; i < m_size; i++ ) {
    m_data[i] = array[i];
  }
}

//------------------------------------------------------------------------
// size
//------------------------------------------------------------------------
// A function that returns the size of the Vector
template <typename T>
int Vector<T>::size() const
{
  return m_size;
}

//------------------------------------------------------------------------
// push_back
//------------------------------------------------------------------------
// A function that adds the given value to the end of the Vector's m_data
// array using the value that it takes in
template <typename T>
void Vector<T>::push_back( const T& value )
{
  T* temp = m_data;
  if ( m_size + 1 > m_maxsize ) {
    m_maxsize *= 2;
    m_size++;
    m_data = new T[m_maxsize];
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
// A function that returns 1 if the given value is in the data of the Vector
template <typename T>
bool Vector<T>::contains( const T& value ) const
{
  for ( int i = 0; i < m_size; i++ ) {
    if ( m_data[i] == value ) {
      return 1;
    }
  }
  return 0;
}

//------------------------------------------------------------------------
// at
//------------------------------------------------------------------------
// A function that returns the value at the index idx in the Vector's array
// This is the read version
template <typename T>
const T& Vector<T>::at( int idx ) const
{
  if ( m_size == 0 || idx > m_size - 1 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "index is out of range" );
    throw e;
  }
  return m_data[idx];
}

//------------------------------------------------------------------------
// at
//------------------------------------------------------------------------
// A function that returns the value at the index idx in the Vector's array
// This is the write version
template <typename T>
T& Vector<T>::at( int idx )
{
  if ( m_size == 0 || idx > m_size - 1 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "index is out of range" );
    throw e;
  }
  return m_data[idx];
}

//------------------------------------------------------------------------
// find_closest_linear
//------------------------------------------------------------------------
// A function that returns the closest value in the Vector's array to the
// given value using a linear search
template <typename T>
template <typename DistFunc>
T Vector<T>::find_closest_linear( const T& value, DistFunc dist ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }
  int smallestdiff = dist( value, m_data[0] );
  int sdidx        = 0;
  for ( int i = 1; i < m_size; i++ ) {
    int absv = dist( value, m_data[i] );
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
template <typename T, typename CmpFunc, typename DistFunc>
int closer( Vector<T> vec, T val, int first, int second, CmpFunc cmp,
            DistFunc dist )
{
  if ( dist( vec.at( second ), val ) <= dist( val, vec.at( first ) ) ) {
    return second;
  }
  else {
    return first;
  }
}

template <typename T, typename CmpFunc, typename DistFunc>
int binary_search( const Vector<T>& vec, int bot, int top, T val, CmpFunc cmp,
                   DistFunc dist )
{
  if ( top > bot ) {
    int middle_idx = ( ( top - bot ) / 2 ) + bot;
    T   middle_val = vec.at( middle_idx );

    bool middle_val_lessthan_val = cmp( middle_val, val );
    bool val_lessthan_middle_val = cmp( val, middle_val );

    // base case: middle value is in range of value +- k
    if ( !val_lessthan_middle_val && !middle_val_lessthan_val ) {
      return middle_idx;
    }

    // recursive cases:
    // case 1: value is greater than the value at the middle index
    if ( middle_val_lessthan_val ) {
      if ( cmp( val, vec.at( middle_idx + 1 ) ) ) {
        return closer( vec, val, middle_idx, middle_idx + 1, cmp, dist );
      }
      // search top half
      return binary_search( vec, middle_idx + 1, top, val, cmp, dist );
    }

    // case 2: value is less than the value at the middle index
    if ( val_lessthan_middle_val ) {
      if ( cmp( vec.at( middle_idx - 1 ), val ) ) {
        return closer( vec, val, middle_idx - 1, middle_idx, cmp, dist );
      }
      // search bottom half
      return binary_search( vec, bot, middle_idx, val, cmp, dist );
    }
  }
  return -1;
}

//------------------------------------------------------------------------
// find_closest_binary
//------------------------------------------------------------------------
// A function that finds the closest value to value in range k using binary
// search
template <typename T>
template <typename DistFunc, typename CmpFunc>
T Vector<T>::find_closest_binary( const T& value, int k, DistFunc dist,
                                  CmpFunc cmp ) const
{
  if ( m_size == 0 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "vectors size is 0" );
    throw e;
  }

  for ( int i = 0; i < size() - 1; i++ ) {
    if ( cmp( m_data[i + 1], m_data[i] ) ) {
      ece2400::InvalidArgument e =
          ece2400::InvalidArgument( "Vector is not sorted" );
      throw e;
    }
  }
  // find index of closest value in range using binary search
  int idx = -1;
  if ( cmp( value, m_data[0] ) ||
       ( !cmp( value, m_data[0] ) && !cmp( m_data[0], value ) ) ) {
    idx = 0;
  }
  else if ( cmp( m_data[m_size - 1], value ) ||
            ( !cmp( value, m_data[m_size - 1] ) &&
              !cmp( m_data[m_size - 1], value ) ) ) {
    idx = m_size - 1;
  }
  else {
    idx = binary_search( *this, 0, size() - 1, value, cmp, dist );
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
  int smallestdiff = dist( value, at( idx ) );
  // loop through idk - k/2 to idx + k/2
  for ( int i = loidx; i <= hiidx; i++ ) {
    int absv = dist( value, m_data[i] );
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
// A function that sorts the array of the Vector using sort()
template <typename T>
template <typename CmpFunc>
void Vector<T>::sort( CmpFunc cmp )
{
  ::sort( m_data, m_size, cmp );
}

//------------------------------------------------------------------------
// operator[]
//------------------------------------------------------------------------
// An override function for the [] operator that returns the value at idx in
// the Vector's array. This is the read version
template <typename T>
const T& Vector<T>::operator[]( int idx ) const
{
  return m_data[idx];
}

//------------------------------------------------------------------------
// operator[]
//------------------------------------------------------------------------
// An override function for the [] operator that returns the value at idx in
// the Vector's array. This is the write version
template <typename T>
T& Vector<T>::operator[]( int idx )
{
  return m_data[idx];
}

//------------------------------------------------------------------------
// operator=
//------------------------------------------------------------------------
// An override function for the = operator that assigns the Vector to
// the given Vector vec
template <typename T>
Vector<T>& Vector<T>::operator=( const Vector<T>& vec )
{
  if ( this != &vec ) {
    m_maxsize = vec.m_maxsize;
    delete[] m_data;
    m_data = new T[m_maxsize];
    m_size = vec.m_size;
    for ( int i = 0; i < m_size; i++ ) {
      m_data[i] = vec.m_data[i];
    }
  }
  return *this;
}

//------------------------------------------------------------------------
// print
//------------------------------------------------------------------------

template <typename T>
void Vector<T>::print() const
{
  printf( "[ " );
  int size = this->size();
  for ( int i = 0; i < size - 1; i++ )
    std::cout << ( *this )[i] << ", ";
  std::cout << ( *this )[size - 1] << " ";
  printf( "]" );
  std::cout << std::endl;
}