//========================================================================
// sort.inl
//========================================================================
// Definition of generic sort algorithm.

//------------------------------------------------------------------------
// partition
//------------------------------------------------------------------------
// A function that finds a pivot point and swaps values around the pivot point
// by pushing them back if less than pivot and up if greater than pivot by
// swapping the two values
template <typename T, typename CmpFunc>
int partition( T* a, int begin, int end, CmpFunc cmp )
{
  T   pivot = a[end - 1];
  int idx   = begin;
  for ( int i = begin; i < end; i++ ) {
    if ( cmp( a[i], pivot ) ||
         ( !cmp( a[i], pivot ) && !cmp( pivot, a[i] ) ) ) {
      T temp = a[i];
      a[i]   = a[idx];
      a[idx] = temp;
      idx++;
    }
  }
  return idx - 1;
}

//------------------------------------------------------------------------
// quick_sort_h
//------------------------------------------------------------------------
// A function that sorts an array using the quicksort algorithm
template <typename T, typename CmpFunc>
void quick_sort_h( T* a, int begin, int end, CmpFunc cmp )
{
  int size = end - begin;
  if ( size == 0 || size == 1 ) {
    return;
  }
  int part = partition( a, begin, end, cmp );
  quick_sort_h( a, begin, part, cmp );
  quick_sort_h( a, part, end, cmp );
}

//------------------------------------------------------------------------
// sort
//------------------------------------------------------------------------
// A function that sorts an array a using the quicksort algorithm
template <typename T, typename CmpFunc>
void sort( T* a, int size, CmpFunc cmp )
{
  quick_sort_h( a, 0, size, cmp );
}
