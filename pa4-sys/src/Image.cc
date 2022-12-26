//========================================================================
// Image.cc
//========================================================================
// Implementations for Image.

#include "Image.h"
#include "ece2400-stdlib.h"

//------------------------------------------------------------------------
// Image
//------------------------------------------------------------------------
// The default constructor for Image class

Image::Image()
{
  m_vector    = VectorInt( nullptr, 0 );
  m_cols      = 0;
  m_rows      = 0;
  m_intensity = 0;
  m_label     = '?';
}

//------------------------------------------------------------------------
// Image( const VectorInt& vec, int ncols, int nrows )
//------------------------------------------------------------------------
// The non default constructor for Image class that takes in an VectorInt
// and a number of columns and rows

Image::Image( const VectorInt& vec, int ncols, int nrows )
{
  if ( ncols > 128 || nrows > 128 ) {
    ece2400::InvalidArgument e =
        ece2400::InvalidArgument( "dimension is larger than 128" );
    throw e;
  }
  int size = ncols * nrows;
  if ( vec.size() != size ) {
    ece2400::InvalidArgument e = ece2400::InvalidArgument(
        "size does not match number of columns and rows" );
    throw e;
  }
  m_vector    = VectorInt( vec );
  m_cols      = ncols;
  m_rows      = nrows;
  m_intensity = 0;
  for ( int i = 0; i < size; i++ ) {
    m_intensity = m_intensity + vec[i];
  }
  m_label = '?';
}

//------------------------------------------------------------------------
// get_ncols
//------------------------------------------------------------------------
// A function that returns the number of columns of an Image

int Image::get_ncols() const
{
  return m_cols;
}

//------------------------------------------------------------------------
// get_nrows
//------------------------------------------------------------------------
// A function that returns the number of rows of an Image

int Image::get_nrows() const
{
  return m_rows;
}

//------------------------------------------------------------------------
// at
//------------------------------------------------------------------------
// A function that returns the value at the given index using 2d indices

int Image::at( int x, int y ) const
{
  if ( x > m_cols - 1 || y > m_rows - 1 ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "x or y is out of bounds" );
    throw e;
  }
  int idx = x + m_cols * y;
  return m_vector.at( idx );
}

//------------------------------------------------------------------------
// set_label
//------------------------------------------------------------------------
// A function that sets the label of an Image

void Image::set_label( char label )
{
  m_label = label;
}

//------------------------------------------------------------------------
// get_label
//------------------------------------------------------------------------
// A function that returns the label field of an Image

char Image::get_label() const
{
  return m_label;
}

//------------------------------------------------------------------------
// get_intensity
//------------------------------------------------------------------------
// A function that returns the intensity field of an Image

int Image::get_intensity() const
{
  return m_intensity;
}

//------------------------------------------------------------------------
// square
//------------------------------------------------------------------------
// A function that returns the square of a given value

int square( int x )
{
  return x * x;
}

//------------------------------------------------------------------------
// distance
//------------------------------------------------------------------------
// A function that returns the euclidean distance between one image and another

int Image::distance( const Image& other ) const
{
  int total_distance = 0;
  int size           = m_cols * m_rows;
  if ( size != other.get_nrows() * other.get_ncols() ||
       ( m_rows != other.get_nrows() && m_cols != other.get_ncols() ) ) {
    ece2400::InvalidArgument e =
        ece2400::InvalidArgument( "dimensions of images do not match" );
    throw e;
  }
  for ( int i = 0; i < size; i++ ) {
    int before_square = m_vector[i] - other.m_vector[i];
    total_distance    = total_distance + square( before_square );
  }
  return total_distance;
}

//------------------------------------------------------------------------
// print
//------------------------------------------------------------------------

void Image::print() const
{
  std::printf( "label: %c\n", this->get_label() );
  std::printf( "intensity: %d\n", this->get_intensity() );
}

//------------------------------------------------------------------------
// print_pixel
//------------------------------------------------------------------------
// A helper function that prints a grayscale pixel using unicode based on
// the integer value.

void print_pixel( int v )
{
  if ( v <= 0 )
    std::printf( "%s", "  " );
  else if ( 0 < v && v <= 64 )
    std::printf( "%s", "\u2591\u2591" );
  else if ( 64 < v && v <= 128 )
    std::printf( "%s", "\u2592\u2592" );
  else if ( 128 < v && v <= 192 )
    std::printf( "%s", "\u2593\u2593" );
  else
    std::printf( "%s", "\u2588\u2588" );
}

//------------------------------------------------------------------------
// display
//------------------------------------------------------------------------

void Image::display() const
{
  int nrows = this->get_nrows();
  int ncols = this->get_ncols();

  for ( int y = 0; y < nrows; y++ ) {
    for ( int x = 0; x < ncols; x++ ) {
      print_pixel( this->at( x, y ) );
    }
    std::printf( "\n" );
  }
}

//------------------------------------------------------------------------
// operator==
//------------------------------------------------------------------------
// A function that overrides the == operator for Images and allows the
// comparison of Images by checking each value of one imgae against the value
// of another image. Returns true if the images are equal.

bool Image::operator==( const Image& rhs ) const
{
  if ( this == &rhs ) {
    return true;
  }
  if ( m_rows != rhs.get_nrows() || m_cols != rhs.get_ncols() ) {
    return false;
  }
  int size = m_cols * m_rows;
  for ( int i = 0; i < size; i++ ) {
    int x = i % m_cols;
    int y = i / m_cols;
    if ( at( x, y ) != rhs.at( x, y ) ) {
      return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------
// operator!=
//------------------------------------------------------------------------
// A function that overrides the != operator for Images and allows the
// comparison of Images by checking each value of one imgae against the value
// of another image. Returns true if the images are not equal.

bool Image::operator!=( const Image& rhs ) const
{
  if ( this == &rhs ) {
    return false;
  }
  if ( m_rows != rhs.get_nrows() || m_cols != rhs.get_ncols() ) {
    return true;
  }
  int size = m_cols * m_rows;
  for ( int i = 0; i < size; i++ ) {
    int x = i % m_cols;
    int y = i / m_rows;
    if ( at( x, y ) != rhs.at( x, y ) ) {
      return true;
    }
  }
  return false;
}
