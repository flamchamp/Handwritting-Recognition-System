//========================================================================
// sort-adhoc.c
//========================================================================

#include "ece2400-stdlib.h"
#include "sort.h"

#include <cstddef>
#include <cstdio>

bool less( int a, int b )
{
  return a < b;
}

int main()
{
  int size = 4;
  int a[]  = {19, 95, 4, 23};

  // Print out array before

  std::printf( "Before sorting: " );

  ece2400::print_array( a, size );

  // Call sort

  sort( a, size, less );

  // Print out array after

  std::printf( "After sorting:  " );

  ece2400::print_array( a, size );

  return 0;
}
