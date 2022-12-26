//========================================================================
// HRSBinarySearch.h
//========================================================================
// Handwritten recognition system that uses linear search.

#ifndef HRS_BINARY_SEARCH_H
#define HRS_BINARY_SEARCH_H

#include "IHandwritingRecSys.h"
#include "Vector.h"

// Here we use forward declaration instead of #include. Forward
// declaration is a declaration of an identifier (type, variable, or
// class) before giving a complete definition.
//
// We should use forward declaration whenever possible. Using forward
// declaration is almost always better than using #include because
// #include may have some side effects such as:
// - including other headers you don't need
// - polluting the namespcae
// - longer compilation time

class Image;

//------------------------------------------------------------------------
// HRSBinarySearch
//------------------------------------------------------------------------

class HRSBinarySearch : public IHandwritingRecSys {
 public:
  HRSBinarySearch( int K = 1000 );

  void  train( const Vector<Image>& vec );
  Image classify( const Image& img );

 private:
  Vector<Image> m_vimage;
  int           m_k;
};

#endif
