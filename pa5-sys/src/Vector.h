//========================================================================
// Vector.h
//========================================================================
// Declarations for Vector.

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename T>
class Vector {
 public:
  Vector();
  ~Vector();

  // Copy constructor
  Vector( const Vector<T>& vec );

  // Construct from an array
  Vector( T* array, int size );

  // Methods
  int      size() const;
  void     push_back( const T& value );
  const T& at( int idx ) const;
  T&       at( int idx );
  bool     contains( const T& value ) const;

  // clang-format off
  template <typename DistFunc>
  T find_closest_linear( const T& value, DistFunc dist ) const;

  template <typename DistFunc, typename CmpFunc>
  T find_closest_binary( const T& value, int k,
                         DistFunc dist, CmpFunc cmp ) const;

  template <typename CmpFunc>
  void sort( CmpFunc cmp );

  template <typename DistFunc>
  T parallel_linear_search( const T& value, DistFunc dist ) const;

  // clang-format on

  void print() const;

  // Operator overloading
  const T&   operator[]( int idx ) const;
  T&         operator[]( int idx );
  Vector<T>& operator=( const Vector<T>& vec );

 private:
  T*  m_data;
  int m_maxsize;
  int m_size;
};

// Include inline definitions
#include "Vector.inl"

#endif  // VECTOR_H
