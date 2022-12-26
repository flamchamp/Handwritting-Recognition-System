//========================================================================
// ece2400-stdlib.inl
//========================================================================
// Inline and/or template definitions for ECE 2400 standard library.

#include "ece2400-stdlib.h"

namespace ece2400 {

//------------------------------------------------------------------------
// less
//------------------------------------------------------------------------
// Return true if a is strictly less than b; false otherwise.

inline bool less( int a, int b )
{
  return a < b;
}

//------------------------------------------------------------------------
// distance
//------------------------------------------------------------------------
// Return the distance between the two given objects.

inline int distance( int a, int b )
{
  if ( a > b )
    return a - b;
  else
    return b - a;
}

//------------------------------------------------------------------------
// hash
//------------------------------------------------------------------------
// Return hash value of the given integer

inline int hash( int a )
{
  return a;
}

}  // namespace ece2400
