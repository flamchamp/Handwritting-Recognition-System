//========================================================================
// sort.h
//========================================================================
// Declarations for generic sort algorithm.

#ifndef SORT_H
#define SORT_H

#include <cstddef>

// Cmp is a function object type. cmp should return true when arg1 is
// strictly less than arg2, and false otherwise.
template <typename T, typename CmpFunc>
void sort( T* a, int size, CmpFunc cmp );

// Include inline definitions
#include "sort.inl"

#endif  // SORT_H
