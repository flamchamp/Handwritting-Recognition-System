//========================================================================
// sort-image.cc
//========================================================================
// Implementation of the sort-image function

#include "sort-image.h"

// This was an attempt to optimize the sort function but it was not finished
// but I am leavving it in as a comment in case I want to come back to it
// potentially

// int median(int x, int y, int z) {
//   if ((x > y && x < z) || (x < y && x > z)) {
//     return x;
//   }
//   else if ((x < y && y < z) || (x > y && y > z)) {
//     return y;
//   }
//   return z;
// }

// int find_pivot(Image* a, int begin, int end) {
//   if (end <= begin + 1) {
//     return a[end - 1].get_intensity();
//   }
//   int first = a[begin].get_intensity();
//   printf("first = %d\n", first);
//   int second = a[((end - 1) + begin) / 2].get_intensity();
//   printf("second = %d\n", second);
//   int third = a[end - 1].get_intensity();
//   printf("third = %d\n", third);
//   int middle = median(first, second, third);
//   printf("middle = %d\n", middle);
//   return middle;
// }

//------------------------------------------------------------------------
// partition
//------------------------------------------------------------------------
// A function that finds a pivot point and swaps values around the pivot point
// by pushing them back if less than pivot and up if greater than pivot by
// swapping the two values

int partition( Image* a, int begin, int end )
{
  int pivot = a[end - 1].get_intensity();
  int idx   = begin;
  for ( int i = begin; i < end; i++ ) {
    if ( a[i].get_intensity() <= pivot ) {
      Image temp = a[i];
      a[i]       = a[idx];
      a[idx]     = temp;
      idx++;
    }
  }
  return idx - 1;
}

//------------------------------------------------------------------------
// quick_sort_h
//------------------------------------------------------------------------
// A function that sorts an array using the quicksort algorithm

void quick_sort_h( Image* a, int begin, int end )
{
  int size = end - begin;
  if ( size == 0 || size == 1 ) {
    return;
  }
  int part = partition( a, begin, end );
  quick_sort_h( a, begin, part );
  quick_sort_h( a, part, end );
}

//------------------------------------------------------------------------
// sort_image
//------------------------------------------------------------------------
// A function that sorts an array a using the quicksort algorithm

void sort_image( Image* a, int size )
{
  quick_sort_h( a, 0, size );
  return;
}
