//========================================================================
// Tree.inl
//========================================================================
// Implementation of Tree.

#include "Vector.h"
#include "ece2400-stdlib.h"
#include <cassert>
#include <iostream>

template <typename T>
Node<T>::Node( T val )
{
  value   = val;
  left_p  = nullptr;
  right_p = nullptr;
}

template <typename T, typename CmpFunc>
Tree<T, CmpFunc>::Tree( int k, CmpFunc cmp )
{
  m_root_p = nullptr;
  m_cmp    = cmp;
  m_size   = 0;
  m_k      = k;
}

template <typename T>
void destruct_h( Node<T>* node )
{
  if ( node == nullptr ) {
    return;
  }
  destruct_h( node->left_p );
  destruct_h( node->right_p );
  delete node;
}

template <typename T, typename CmpFunc>
Tree<T, CmpFunc>::~Tree()
{
  destruct_h( m_root_p );
}

template <typename T, typename CmpFunc>
int Tree<T, CmpFunc>::size() const
{
  return m_size;
}

// Helper function to add value to correct spot
template <typename T, typename CmpFunc>
bool add_h( const T& value, CmpFunc cmp, Node<T>* node )
{
  if ( !cmp( node->value, value ) && !cmp( value, node->value ) ) {
    return false;
  }
  if ( cmp( node->value, value ) && node->right_p == nullptr ) {
    Node<T>* newnode = new Node<T>( value );
    node->right_p    = newnode;
    return true;
  }
  else if ( cmp( value, node->value ) && node->left_p == nullptr ) {
    Node<T>* newnode = new Node<T>( value );
    node->left_p     = newnode;
    return true;
  }

  if ( cmp( value, node->value ) ) {
    return add_h( value, cmp, node->left_p );
  }
  else if ( cmp( node->value, value ) ) {
    return add_h( value, cmp, node->right_p );
  }

  return false;
}

template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::add( const T& value )
{
  bool increase_size = false;
  if ( m_root_p == nullptr ) {
    Node<T>* root = new Node<T>( value );
    m_root_p      = root;
    increase_size = true;
  }
  else {
    increase_size = add_h( value, m_cmp, m_root_p );
  }

  if ( increase_size ) {
    m_size += 1;
  }
}

// Recursive helper function for contains member function
template <typename T, typename CmpFunc>
bool find_val( const T& value, CmpFunc cmp, Node<T>* node )
{
  if ( node == nullptr ) {
    return false;
  }
  if ( !cmp( node->value, value ) && !cmp( value, node->value ) ) {
    return true;
  }
  if ( cmp( value, node->value ) ) {
    return find_val( value, cmp, node->left_p );
  }

  if ( cmp( node->value, value ) ) {
    return find_val( value, cmp, node->right_p );
  }
  return false;
}

template <typename T, typename CmpFunc>
bool Tree<T, CmpFunc>::contains( const T& value ) const
{
  return find_val( value, m_cmp, m_root_p );
}

// Recursive helper traverse tree in-order and populate values in a vector
template <typename T>
Vector<T> make_vec( Vector<T> newvec, const Node<T>* node )
{
  if ( node == nullptr ) {
    return newvec;
  }
  if ( node->left_p == nullptr && node->right_p == nullptr ) {
    newvec.push_back( node->value );
    return newvec;
  }
  newvec = make_vec( newvec, node->left_p );
  newvec.push_back( node->value );
  newvec = make_vec( newvec, node->right_p );
  return newvec;
}

template <typename T, typename CmpFunc>
Vector<T> Tree<T, CmpFunc>::to_vector() const
{
  Vector<T> newvec = Vector<T>();
  return make_vec( newvec, m_root_p );
}

// Recursice Function for find_closest
template <typename T, typename CmpFunc>
Vector<T> binary_tree_search( Node<T>* node, int levels, const T& value,
                              CmpFunc cmp, int k )
{
  if ( levels == 0 ) {
    Vector<T> newvec = Vector<T>();
    return make_vec( newvec, node );
  }
  if ( !cmp( node->value, value ) && !cmp( value, node->value ) ) {
    Vector<T> newvec = Vector<T>();
    newvec.push_back( node->value );
    return newvec;
  }
  if ( cmp( value, node->value ) ) {
    if ( node->left_p == nullptr || cmp( node->left_p->value, value ) ) {
      Vector<T> newvec = Vector<T>();
      return make_vec( newvec, node );
    }
    else {
      return binary_tree_search( node->left_p, levels - 1, value, cmp, k );
    }
  }
  if ( cmp( node->value, value ) ) {
    if ( node->right_p == nullptr || cmp( value, node->right_p->value ) ) {
      Vector<T> newvec = Vector<T>();
      return make_vec( newvec, node );
    }
    else {
      return binary_tree_search( node->right_p, levels - 1, value, cmp, k );
    }
  }
  Vector<T> newvec = Vector<T>();
  return make_vec( newvec, node );
}

template <typename T, typename CmpFunc>
template <typename DistFunc>
T Tree<T, CmpFunc>::find_closest( const T& value, DistFunc dist )
{
  if ( m_root_p == nullptr ) {
    ece2400::OutOfRange e = ece2400::OutOfRange( "Tree is empty" );
    throw e;
  }
  Vector<T> vec = binary_tree_search(
      m_root_p, (int) ( log2( m_size ) - log2( m_k ) ), value, m_cmp, m_k );
  return vec.find_closest_linear( value, dist );
}

template <typename T, typename CmpFunc>
Tree<T, CmpFunc>& Tree<T, CmpFunc>::operator=( const Tree<T, CmpFunc>& tree )
{
  if ( this != &tree ) {
    m_cmp  = tree.m_cmp;
    m_size = 0;
    m_k    = tree.m_k;
    destruct_h( m_root_p );
    m_root_p      = nullptr;
    Vector<T> vec = tree.to_vector();
    for ( int i = 0; i < vec.size(); i++ ) {
      add( vec[i] );
    }
  }
  return *this;
}

template <typename T, typename CmpFunc>
Tree<T, CmpFunc>::Tree( const Tree<T, CmpFunc>& tree )
{
  if ( this == &tree ) {
    return;
  }
  m_cmp         = tree.m_cmp;
  m_size        = 0;
  m_k           = tree.m_k;
  m_root_p      = nullptr;
  Vector<T> vec = tree.to_vector();
  for ( int i = 0; i < vec.size(); i++ ) {
    add( vec[i] );
  }
}

//------------------------------------------------------------------------
// Tree<T,CmpFunc>::print
//------------------------------------------------------------------------

template <typename T, typename CmpFunc>
void print_h( Node<T>* node_p, int level )
{
  if ( node_p == nullptr )  // base case, current node is nullptr
    return;

  print_h<T, CmpFunc>( node_p->right_p,
                       level + 1 );  // call helper on right child

  for ( int i = 0; i < level; i++ ) {  // print this node at the right level
    std::cout << "  ";
  }
  std::cout << node_p->value << std::endl;

  print_h<T, CmpFunc>( node_p->left_p,
                       level + 1 );  // call helper on left child
}

template <typename T, typename CmpFunc>
void Tree<T, CmpFunc>::print() const
{
  print_h<T, CmpFunc>( m_root_p,
                       0 );  // call the recursive helper on the root node
}
