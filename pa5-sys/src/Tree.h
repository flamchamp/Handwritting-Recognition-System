//========================================================================
// Tree.h
//========================================================================
// Declarations for generic tree.

#ifndef TREE_H
#define TREE_H

#include <cstddef>

template <typename T>
class Vector;

template <typename T>
struct Node {
  Node( T val );
  T     value;
  Node* left_p;
  Node* right_p;
};

template <typename T, typename CmpFunc>
class Tree {
 public:
  Tree( int K, CmpFunc cmp );
  ~Tree();

  // Copy constructor
  Tree( const Tree<T, CmpFunc>& tree );

  // Methods
  int  size() const;
  void add( const T& value );
  bool contains( const T& value ) const;

  template <typename DistFunc>
  T find_closest( const T& value, DistFunc dist );

  Vector<T> to_vector() const;

  void print() const;

  // Operator overloading
  Tree<T, CmpFunc>& operator=( const Tree<T, CmpFunc>& tree );

 private:
  // template <typename T, typename CmpFunc>
  // T m_value;
  CmpFunc  m_cmp;
  int      m_size;
  Node<T>* m_root_p;
  // Tree* m_left;
  // Tree* m_right;
  int m_k;
  // bool add_helper(const T& value, CmpFunc cmp, Tree<T, CmpFunc>* subtree );
  // void destruct_h();
};

// Include inline definitions
#include "Tree.inl"

#endif /* TREE_H */
