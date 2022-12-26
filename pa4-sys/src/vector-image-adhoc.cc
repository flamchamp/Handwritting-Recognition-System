//========================================================================
// vector-image-adhoc.c
//========================================================================
// This file contains an ad-hoc test for VectorImage.

#include "Image.h"
#include "VectorImage.h"
#include "VectorInt.h"
#include "digits.dat"
#include <stdio.h>

int main()
{
  VectorImage vec;

  vec.push_back( Image( VectorInt( digit12_image, 28 * 28 ), 28, 28 ) );
  vec.push_back( Image( VectorInt( digit2_image, 28 * 28 ), 28, 28 ) );
  vec.push_back( Image( VectorInt( digit1_image, 28 * 28 ), 28, 28 ) );

  printf( "Image at index 0 is:\n" );
  vec.at( 0 ).print();

  printf( "Image at index 1 is:\n" );
  vec.at( 1 ).print();

  printf( "Image at index 2 is:\n" );
  vec.at( 2 ).print();

  return 0;
}
