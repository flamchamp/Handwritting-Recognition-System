//========================================================================
// image-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for Image.

#include "Image.h"
#include "Vector.h"
#include "digits.dat"
#include <cstdio>

int main()
{
  Vector<int> vec( digit1_image, 28 * 28 );
  Image       img( vec, 28, 28 );
  img.set_label( digit1_label );

  std::printf( "Print the Image:\n" );
  img.print();
  img.display();

  return 0;
}
