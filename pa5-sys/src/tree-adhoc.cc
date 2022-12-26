//========================================================================
// tree-adhoc.cc
//========================================================================
// This file contains an ad-hoc test for tree.

#include "Tree.h"
#include "ece2400-stdlib.h"
#include <cstdio>
#include <functional>

int int_less( int a, int b )
{
  return a < b;
}

int main()
{
  // Tree<int, std::function<int( int, int )> > tree( 10, std::less );
  Tree<int, std::function<int( int, int )> > tree( 10, int_less );

  for ( int v : {10, 55, 20, 74, 5, 43, 59, 99, 12, 32} ) {
    printf( "Adding %d XXXXXXXXXXXXXX\n", v );
    tree.add( v );
  }

  printf( "printing: \n" );
  tree.print();

  std::printf( "\n" );

  printf( "size is %d\n", tree.size() );
}
