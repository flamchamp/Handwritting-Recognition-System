//========================================================================
// Image.h
//========================================================================
// Declarations for Image.

#ifndef IMAGE_H
#define IMAGE_H

#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include <cstddef>

class Image {
 public:
  // Constructors
  Image();
  Image( const VectorInt& vec, int ncols, int nrows );

  // Methods
  int  get_ncols() const;
  int  get_nrows() const;
  int  at( int x, int y ) const;
  void set_label( char l );
  char get_label() const;
  int  get_intensity() const;
  void print() const;
  void display() const;
  int  distance( const Image& other ) const;

  // Operator overloading
  bool operator==( const Image& rhs ) const;
  bool operator!=( const Image& rhs ) const;

 private:
  VectorInt m_vector;
  int       m_cols;
  int       m_rows;
  int       m_intensity;
  char      m_label;
};

#include "Image.inl"

#endif  // IMAGE_H
