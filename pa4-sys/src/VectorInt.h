//========================================================================
// VectorInt.h
//========================================================================
// Declarations for VectorInt.

#ifndef VECTOR_INT_H
#define VECTOR_INT_H

#include <cstddef>

class VectorInt {
 public:
  VectorInt();
  ~VectorInt();

  // Copy constructor
  VectorInt( const VectorInt& vec );

  // Construct from an array
  VectorInt( int* array, int size );

  // Methods
  int  size() const;
  void push_back( int value );
  int  at( int idx ) const;
  bool contains( int value ) const;
  int  find_closest_linear( int value ) const;
  int  find_closest_binary( int value, int k ) const;
  void sort();
  void print() const;

  // Operator overloading
  int        operator[]( int idx ) const;
  VectorInt& operator=( const VectorInt& vec );

 private:
  int* m_data;
  int  m_maxsize;
  int  m_size;
};

#include "VectorInt.inl"

#endif  // VECTOR_INT_H
