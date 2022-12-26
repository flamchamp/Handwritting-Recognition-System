//========================================================================
// Table.h
//========================================================================
// Declarations for generic table.

#ifndef TABLE_H
#define TABLE_H

#include <cstddef>

template <typename T>
class Vector;

template <typename T, typename HashFunc>
class Table {
 public:
  Table( int k, HashFunc hash );

  // Methods
  int  size() const;
  void add( const T& value );
  bool contains( const T& value ) const;

  template <typename DistFunc>
  T find_closest( const T& value, DistFunc dist ) const;

  Vector<T> to_vector() const;

  void print() const;

 private:
  //'''' ASSIGNMENT TASK '''''''''''''''''''''''''''''''''''''''''''''''''
  // Declare private data members and member functions. Note that
  // according to our naming convention, data member's name should starts
  // with a `m_` prefix.
  //''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
};

// Include inline definitions
#include "Table.inl"

#endif /* TABLE_H */
