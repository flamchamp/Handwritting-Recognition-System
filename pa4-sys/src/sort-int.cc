//========================================================================
// sort-int.cc
//========================================================================
// Implementation of the sort-int function

#include "sort-int.h"

//------------------------------------------------------------------------
// partition
//------------------------------------------------------------------------
// A function that takes the last element of a given range of an array as a
// a pivot and swaps integers based on value around that pivot

int partition( int* a, int begin, int end )
{
  int pivot = a[end - 1];
  int idx   = begin;
  for ( int i = begin; i < end; i++ ) {
    if ( a[i] <= pivot ) {
      int temp = a[i];
      a[i]     = a[idx];
      a[idx]   = temp;
      idx++;
    }
  }
  return idx - 1;
}

//------------------------------------------------------------------------
// quick_sort_h
//------------------------------------------------------------------------
// A helper function that sorts an array of ints using the quicksort algorithm

void quick_sort_h( int* a, int begin, int end )
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
// sort_int
//------------------------------------------------------------------------
// A function that sorts an array of ints based on value

void sort_int( int* a, int size )
{
  quick_sort_h( a, 0, size );
}
