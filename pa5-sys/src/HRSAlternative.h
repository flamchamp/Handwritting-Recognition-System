//========================================================================
// HRSAlternativeSearch.h
//========================================================================
// Handwritten recognition system that uses linear search.

#ifndef HRS_ALTERNATIVE_H
#define HRS_ALTERNATIVE_H

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
// HRSLinearSearch
//------------------------------------------------------------------------

class HRSAlternative : public IHandwritingRecSys {
 public:
  //'''' STAFF NOTE ''''''''''''''''''''''''''''''''''''''''''''''''''''''
  // You are free to change the signature of the constructor or add other
  // constructors. Note that you may need to change the evaluation program
  // if you do so.
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  HRSAlternative();

  void  train( const Vector<Image>& vec );
  Image classify( const Image& img );

 private:
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Declare private data members and member functions. Note that
  // according to our naming convention, data member's name should starts
  // with a `m_` prefix.
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
  Vector<Image> m_vimage;
};

#endif
