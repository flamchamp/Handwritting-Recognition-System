//========================================================================
// sort-int-adhoc.cc
//========================================================================

#include "ece2400-stdlib.h"
#include "sort-int.h"
#include <cstddef>
#include <cstdio>

int main()
{
  int size = 4;
  int a[]  = {19, 95, 4, 23};

  // Print out array before

  std::printf( "Before sorting: " );

  ece2400::print_array( a, size );

  // Call sort_int

  sort_int( a, size );

  // Print out array after

  std::printf( "After sorting:  " );

  ece2400::print_array( a, size );

  return 0;
}
