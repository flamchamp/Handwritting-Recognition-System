//========================================================================
// sort-image-adhoc.cc
//========================================================================

#include "Image.h"
#include "VectorInt.h"
#include "ece2400-stdlib.h"
#include "sort-image.h"
#include <cstddef>
#include <cstdio>

int main()
{
  int size      = 4;
  int data[][4] = {
      {19, 95, 4, 23}, {41, 42, 43, 44}, {1, 21, 200, 199}, {12, 22, 36, 87}};

  Image images[4];

  for ( int i = 0; i < size; i++ )
    images[i] = Image( VectorInt( data[i], 4 ), 1, 4 );

  // Print out array before

  std::printf( "Intensity before sorting: \n" );
  for ( int i = 0; i < size; i++ )
    std::printf( "%d ", images[i].get_intensity() );
  std::printf( "\n" );

  // Call sort_image

  sort_image( images, size );

  // Print out array after

  std::printf( "Intensity after sorting: \n" );
  for ( int i = 0; i < size; i++ )
    std::printf( "%d ", images[i].get_intensity() );
  std::printf( "\n" );

  std::printf( "\n" );
  std::printf( "NEXT ADHOC TEST XXXXXXXXXXXXXXXXXXXXXX\n" );
  std::printf( "\n" );

  // int dat[][8] = {{1, 1, 1, 1, 1, 1, 1, 1}, {2, 2, 2, 2, 2, 2, 2, 2}};
  int dat[][8] = {{1, 1, 1, 1, 1, 1, 1, 1}};

  // An array of images
  // Image imagearr[] = {Image( VectorInt( dat[0], 8 ), 4, 2 ), Image(
  // VectorInt( dat[1], 8 ), 4, 2 )};
  Image imagearr[] = {Image( VectorInt( dat[0], 8 ), 4, 2 )};

  std::printf( "Intensity before sorting: \n" );
  for ( int i = 0; i < 1; i++ )
    std::printf( "%d ", imagearr[i].get_intensity() );
  std::printf( "\n" );

  sort_image( imagearr, 1 );

  std::printf( "Intensity after sorting: \n" );
  for ( int i = 0; i < 1; i++ )
    std::printf( "%d ", imagearr[i].get_intensity() );
  std::printf( "\n" );

  // 4 columns 2 rows failing at (0, 2)
  // 1 1 1 1
  // 1 1 1 1
  std::printf( "image[0] == Image( VectorInt( data[0], 8 ), 4, 2 ) is %d \n",
               imagearr[0] == Image( VectorInt( dat[0], 8 ), 4, 2 ) );
  // std::printf( "image[0] == Image( VectorInt( data[0], 8 ), 4, 2 ) is %d \n",
  // imagearr[0] == Image( VectorInt( dat[0], 8 ), 4, 2 ));

  return 0;
}
