//========================================================================
// VectorImage.h
//========================================================================
// Declarations for VectorImage.

#ifndef VECTOR_IMAGE_H
#define VECTOR_IMAGE_H

#include "Image.h"
#include <cstddef>

class VectorImage {
 public:
  VectorImage();
  ~VectorImage();

  // Copy constructor
  VectorImage( const VectorImage& vec );
  VectorImage( Image* data, int size );

  // Methods
  int   size() const;
  void  push_back( const Image& img );
  Image at( int idx ) const;
  bool  contains( const Image& img ) const;
  Image find_closest_linear( const Image& img ) const;
  Image find_closest_binary( const Image& img, int k ) const;
  void  sort();
  void  print() const;

  // Operator overloading
  Image        operator[]( int idx ) const;
  VectorImage& operator=( const VectorImage& vec );

 private:
  Image* m_data;
  int    m_maxsize;
  int    m_size;
  bool   m_issorted;
};

#include "VectorImage.inl"

#endif  // VECTOR_IMAGE_H
