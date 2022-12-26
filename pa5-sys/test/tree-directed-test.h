//========================================================================
// tree-directed-tests.h
//========================================================================
// This file contains generic directed tests for trees. All of the
// generic test functions are templated by an "object creation" function
// which should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Tree.h"
#include "Vector.h"
#include <vector>
#include <cstdio>

//------------------------------------------------------------------------
// test_case_simple_add
//------------------------------------------------------------------------
// A simple test case that tests default constructor, add, and at.

template < typename T, typename Func, typename CmpFunc >
void test_case_simple_add( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Tree<T,CmpFunc> tree( 42, cmp );

  // Check size of empty tree
  ECE2400_CHECK_INT_EQ( tree.size(), 0 );

  // Push back some values
  T data[] = { f(10), f(11), f(12) };
  for ( T v : data )
    tree.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( tree.size(), 3 );

  // Check values
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_TRUE( tree.contains( data[i] ) );
}

//------------------------------------------------------------------------
// test_case_duplicate_add
//------------------------------------------------------------------------
// A simple test case that tests adding duplicates

template < typename T, typename Func, typename CmpFunc >
void test_case_duplicate_add( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Tree<T,CmpFunc> tree( 42, cmp );

  // Check size of empty tree
  ECE2400_CHECK_INT_EQ( tree.size(), 0 );

  // Push back some values
  T data[] = { f(1), f(1), f(2), f(2), f(1), f(1), f(2), f(2) };
  for ( T v : data )
    tree.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( tree.size(), 2 );

  // Check values
  ECE2400_CHECK_TRUE( tree.contains( f(1) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(2) ) );
}

//------------------------------------------------------------------------
// test_case_construct_empty
//------------------------------------------------------------------------
// A simple test case that tests empty tree

template < typename T, typename Func, typename CmpFunc >
void test_case_construct_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 42, cmp );

  ECE2400_CHECK_INT_EQ( tree.size(), 0 );
}

//------------------------------------------------------------------------
// test_case_contains_simple
//------------------------------------------------------------------------
// A simple test case that tests contains.

template < typename T, typename Func, typename CmpFunc >
void test_case_contains_simple( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a tree from array

  Tree<T,CmpFunc> tree( 42, cmp );

  T data[] = { f(1), f(9), f(9), f(5), f(0), f(4), f(2), f(3) };
  for ( T v : data )
    tree.add( v );

  // Search for value, expecting success

  ECE2400_CHECK_TRUE( tree.contains( f(1) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(9) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(5) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(0) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(4) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(2) ) );
  ECE2400_CHECK_TRUE( tree.contains( f(3) ) );

  // Search for value, expecting failure

  ECE2400_CHECK_FALSE( tree.contains( f(6) ) );
  ECE2400_CHECK_FALSE( tree.contains( f(7) ) );
  ECE2400_CHECK_FALSE( tree.contains( f(8) ) );
}

//------------------------------------------------------------------------
// test_case_contains_empty
//------------------------------------------------------------------------
// A simple test case that tests contains for an empty tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_contains_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct an empty tree

  Tree<T,CmpFunc> tree( 42, cmp );

  // Search for value, expecting failure

  for ( int i = 0; i < 10; i++ )
    ECE2400_CHECK_FALSE( tree.contains( f(i) ) );
}

//------------------------------------------------------------------------
// test_case_find_closest_balanced_largeK
//------------------------------------------------------------------------
// This will create a balanced tree with a total of 15 nodes and three
// levels.
//
//       150
//     140
//       130
//   120
//       110
//     100
//       90
// 80
//       70
//     60
//       50
//   40
//       30
//     20
//       10
//
// We choose a large K which means we are essentially doing an exhaustive
// search.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_find_closest_balanced_largeK( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 1024, cmp );

  T data[] = { f(80), f(40), f(120), f(20), f(60), f(100), f(140),
               f(10), f(30), f(50),  f(70), f(90), f(110), f(130), f(150) };
  for ( T v : data )
    tree.add( v );

  // First find exact matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(10), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(20), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(30), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(40), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(50), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(60), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(70), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(80), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(90), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(100), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(110), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(120), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(130), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(140), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(150), dist) == f(150) );

  // Find near matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(9), dist)   == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(11), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(19), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(21), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(29), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(31), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(39), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(41), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(49), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(51), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(59), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(61), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(69), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(71), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(79), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(81), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(89), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(91), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(99), dist)  == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(101), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(109), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(111), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(119), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(121), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(129), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(131), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(139), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(141), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(149), dist) == f(150) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(151), dist) == f(150) );
}

//------------------------------------------------------------------------
// test_case_find_closest_balanced_smallK
//------------------------------------------------------------------------
// This will create a balanced tree with a total of 15 nodes and three
// levels. It looks like this:
//
//       150
//     140
//       130
//   120
//       110
//     100
//       90
// 80
//       70
//     60
//       50
//   40
//       30
//     20
//       10
//
// We choose a K of 4 which means we should be doing an exhaustive search
// through the bottom two levels (i.e., three nodes). We don't check for
// values which are in the first two levels since an implementation might
// not be looking for exact matches during the binary search part.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_find_closest_balanced_smallK( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 4, cmp );

  T data[] = { f(80), f(40), f(120), f(20), f(60), f(100), f(140),
               f(10), f(30), f(50),  f(70), f(90), f(110), f(130), f(150) };
  for ( T v : data )
    tree.add( v );

  // First find exact matches at the leaves

  ECE2400_CHECK_TRUE( tree.find_closest(f(10), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(20), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(30), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(50), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(60), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(70), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(90), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(100), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(110), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(130), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(140), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(150), dist) == f(150) );

  // Find near matches at the leaves

  ECE2400_CHECK_TRUE( tree.find_closest(f(9), dist)   == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(11), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(19), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(21), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(29), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(31), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(49), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(51), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(59), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(61), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(69), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(71), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(89), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(91), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(99), dist)  == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(101), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(109), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(111), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(129), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(131), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(139), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(141), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(149), dist) == f(150) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(151), dist) == f(150) );
}

//------------------------------------------------------------------------
// test_case_find_closest_unbalanced_largeK
//------------------------------------------------------------------------
// This will create a unbalanced tree with a total of 15 nodes and 8
// levels. It looks like this:
//
//               150
//             140
//           130
//         120
//       110
//     100
//   90
// 80
//   70
//     60
//       50
//         40
//           30
//             20
//               10
//
// We choose a large K which means we are essentially doing an
// exhaustive search.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_find_closest_unbalanced_largeK( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 1024, cmp );

  T data[] = { f(80), f(90), f(100), f(110), f(120), f(130), f(140), f(150),
               f(70), f(60), f(50),  f(40), f(30), f(20), f(10) };
  for ( T v : data )
    tree.add( v );

  // First find exact matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(10), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(20), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(30), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(40), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(50), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(60), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(70), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(80), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(90), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(100), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(110), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(120), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(130), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(140), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(150), dist) == f(150) );

  // Find near matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(9), dist)   == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(11), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(19), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(21), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(29), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(31), dist)  == f(30)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(39), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(41), dist)  == f(40)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(49), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(51), dist)  == f(50)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(59), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(61), dist)  == f(60)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(69), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(71), dist)  == f(70)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(79), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(81), dist)  == f(80)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(89), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(91), dist)  == f(90)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(99), dist)  == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(101), dist) == f(100) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(109), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(111), dist) == f(110) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(119), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(121), dist) == f(120) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(129), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(131), dist) == f(130) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(139), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(141), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(149), dist) == f(150) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(151), dist) == f(150) );
}

//------------------------------------------------------------------------
// test_case_find_closest_unbalanced_smallK
//------------------------------------------------------------------------
// This will create a balanced tree with a total of 15 nodes and three
// levels.
//
//               150
//             140
//           130
//         120
//       110
//     100
//   90
// 80
//   70
//     60
//       50
//         40
//           30
//             20
//               10
//
// We choose a K of 4 which means we should be doing an exhaustive search
// through the bottom two levels (i.e., two nodes). We don't check for
// values which are in the upper levels since an implementation might not
// be looking for exact matches during the binary search part.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_find_closest_unbalanced_smallK( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 4, cmp );

  T data[] = { f(80), f(90), f(100), f(110), f(120), f(130), f(140), f(150),
               f(70), f(60), f(50),  f(40), f(30), f(20), f(10) };
  for ( T v : data )
    tree.add( v );

  // First find exact matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(10), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(20), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(140), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(150), dist) == f(150) );

  // Find near matches

  ECE2400_CHECK_TRUE( tree.find_closest(f(9), dist)   == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(11), dist)  == f(10)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(19), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(21), dist)  == f(20)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(139), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(141), dist) == f(140) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(149), dist) == f(150) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(151), dist) == f(150) );
}

//------------------------------------------------------------------------
// test_case_to_vector_balanced
//------------------------------------------------------------------------
// Testing to_vector on a balanced tree:
//         150
//      140
//         130
//   120
//         110
//      100
//          90
// 80
//          70
//       60
//          50
//    40
//          30
//       20
//          10
template < typename T, typename Func, typename CmpFunc >
void test_case_to_vector_balanced( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 1, cmp );

  T data[] = { f(80), f(40), f(120), f(20), f(60), f(100), f(140),
               f(10), f(30), f(50),  f(70), f(90), f(110), f(130), f(150) };
  for ( T v : data )
    tree.add( v );

  Vector<T> vec = tree.to_vector();

  ECE2400_CHECK_TRUE( vec[0]  == f(10) );
  ECE2400_CHECK_TRUE( vec[1]  == f(20) );
  ECE2400_CHECK_TRUE( vec[2]  == f(30) );
  ECE2400_CHECK_TRUE( vec[3]  == f(40) );
  ECE2400_CHECK_TRUE( vec[4]  == f(50) );
  ECE2400_CHECK_TRUE( vec[5]  == f(60) );
  ECE2400_CHECK_TRUE( vec[6]  == f(70) );
  ECE2400_CHECK_TRUE( vec[7]  == f(80) );
  ECE2400_CHECK_TRUE( vec[8]  == f(90) );
  ECE2400_CHECK_TRUE( vec[9]  == f(100) );
  ECE2400_CHECK_TRUE( vec[10] == f(110) );
  ECE2400_CHECK_TRUE( vec[11] == f(120) );
  ECE2400_CHECK_TRUE( vec[12] == f(130) );
  ECE2400_CHECK_TRUE( vec[13] == f(140) );
  ECE2400_CHECK_TRUE( vec[14] == f(150) );
}

//------------------------------------------------------------------------
// test_case_to_vector_unbalanced
//------------------------------------------------------------------------
// Testing to_vector on an unbalanced tree:
//                    150
//                 140
//              130
//           120
//        110
//     100
//   90
// 80
//   70
//      60
//         50
//            40
//               30
//                  20
//                     10
template < typename T, typename Func, typename CmpFunc >
void test_case_to_vector_unbalanced( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 1, cmp );

  T data[] = { f(80), f(70),  f(90), f(60),  f(100), f(50),  f(110),
               f(40), f(120), f(30), f(130), f(20),  f(140), f(10), f(150) };
  for ( T v : data )
    tree.add( v );

  Vector<T> vec = tree.to_vector();

  ECE2400_CHECK_TRUE( vec[0]  == f(10) );
  ECE2400_CHECK_TRUE( vec[1]  == f(20) );
  ECE2400_CHECK_TRUE( vec[2]  == f(30) );
  ECE2400_CHECK_TRUE( vec[3]  == f(40) );
  ECE2400_CHECK_TRUE( vec[4]  == f(50) );
  ECE2400_CHECK_TRUE( vec[5]  == f(60) );
  ECE2400_CHECK_TRUE( vec[6]  == f(70) );
  ECE2400_CHECK_TRUE( vec[7]  == f(80) );
  ECE2400_CHECK_TRUE( vec[8]  == f(90) );
  ECE2400_CHECK_TRUE( vec[9]  == f(100) );
  ECE2400_CHECK_TRUE( vec[10] == f(110) );
  ECE2400_CHECK_TRUE( vec[11] == f(120) );
  ECE2400_CHECK_TRUE( vec[12] == f(130) );
  ECE2400_CHECK_TRUE( vec[13] == f(140) );
  ECE2400_CHECK_TRUE( vec[14] == f(150) );
}

//------------------------------------------------------------------------
// test_case_to_vector_funky
//------------------------------------------------------------------------
// Testing to_vector on a funky tree:
//     150   140   130
//   90   100   110   120
// 80   70
//   60    50
//      40    30
//         20
//            10
template < typename T, typename Func, typename CmpFunc >
void test_case_to_vector_funky( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Tree<T,CmpFunc> tree( 1, cmp );

  T data[] = { f(80), f(60), f(40),  f(20),  f(10),  f(30),  f(50),
               f(70), f(90), f(150), f(100), f(140), f(110), f(130), f(120) };
  for ( T v : data )
    tree.add( v );

  Vector<T> vec = tree.to_vector();

  ECE2400_CHECK_TRUE( vec[0]  == f(10) );
  ECE2400_CHECK_TRUE( vec[1]  == f(20) );
  ECE2400_CHECK_TRUE( vec[2]  == f(30) );
  ECE2400_CHECK_TRUE( vec[3]  == f(40) );
  ECE2400_CHECK_TRUE( vec[4]  == f(50) );
  ECE2400_CHECK_TRUE( vec[5]  == f(60) );
  ECE2400_CHECK_TRUE( vec[6]  == f(70) );
  ECE2400_CHECK_TRUE( vec[7]  == f(80) );
  ECE2400_CHECK_TRUE( vec[8]  == f(90) );
  ECE2400_CHECK_TRUE( vec[9]  == f(100) );
  ECE2400_CHECK_TRUE( vec[10] == f(110) );
  ECE2400_CHECK_TRUE( vec[11] == f(120) );
  ECE2400_CHECK_TRUE( vec[12] == f(130) );
  ECE2400_CHECK_TRUE( vec[13] == f(140) );
  ECE2400_CHECK_TRUE( vec[14] == f(150) );
}

//------------------------------------------------------------------------
// test_case_copy_v1
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with first syntax.

template < typename T, typename Func, typename CmpFunc >
void test_case_copy_v1( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0
  
  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Copy constructor

  Tree<T,CmpFunc> tree1( tree0 );

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 ) {
    tree0.add( v );
  }

  T data2[] = { f(20), f(21), f(22), f(23) };

  for ( T v : data2 ) {
    tree1.add( v );
  }

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 8 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_copy_v2
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with second syntax.

template < typename T, typename Func, typename CmpFunc >
void test_case_copy_v2( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0

  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Copy constructor with second syntax

  Tree<T,CmpFunc> tree1 = tree0;

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 8 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_copy_empty
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with empty tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_copy_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Copy constructor

  Tree<T,CmpFunc> tree0( 42, cmp );
  Tree<T,CmpFunc> tree1 = tree0;

  // Check both trees are empty

  ECE2400_CHECK_INT_EQ( tree0.size(), 0 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 0 );

  // Push different values to tree0 and tree1

  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 4 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 4 );

  // Check the elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data1[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a non-empty
// tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_assignment( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0

  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Push back some values to tree1

  Tree<T,CmpFunc> tree1( 42, cmp );
  for ( int i = 0; i < 10; i++ )
    tree1.add( f(i) );

  // Assignment operator

  tree1 = tree0;

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 8 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_to_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator to empty tree from
// non-empty tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_assignment_to_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0

  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Assignment operator

  Tree<T,CmpFunc> tree1( 42, cmp );
  tree1 = tree0;

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 8 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_from_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty tree to
// non-empty tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_assignment_from_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0

  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Assignment operator

  Tree<T,CmpFunc> tree1( 42, cmp );
  tree0 = tree1;

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 0 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 0 );

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 4 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty tree to
// empty tree.

template < typename T, typename Func, typename CmpFunc >
void test_case_assignment_empty( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Assignment operator

  Tree<T,CmpFunc> tree0( 42, cmp );
  Tree<T,CmpFunc> tree1( 42, cmp );
  tree0 = tree1;

  // Push different values to tree0 and tree1

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  T data2[] = { f(20), f(21), f(22), f(23) };
  for ( T v : data2 )
    tree1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 4 );
  ECE2400_CHECK_INT_EQ( tree1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( tree1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_self
//------------------------------------------------------------------------
// A simple test case that tests self assignment.

template < typename T, typename Func, typename CmpFunc >
void test_case_assignment_self( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to tree0

  Tree<T,CmpFunc> tree0( 42, cmp );
  T data0[] = { f(0),  f(1),  f(2),  f(3)  };
  for ( T v : data0 )
    tree0.add( v );

  // Assignment operator

  tree0 = tree0;

  // Push more values into tree0

  T data1[] = { f(10), f(11), f(12), f(13) };
  for ( T v : data1 )
    tree0.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( tree0.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( tree0.contains( data0[i] ) );

  // Check the second 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( tree0.contains( data1[i] ) );
}

//------------------------------------------------------------------------
// test_case_general
//------------------------------------------------------------------------
// A generic test case.

template < typename T, typename Func, typename CmpFunc >
void test_case_general( int test_case_num, Func f, CmpFunc cmp )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a new tree

  Tree<T,CmpFunc> tree( 42, cmp );

  // Push data into the data structure

  for ( int i = 0; i < 5; i++ )
    tree.add( f(50+i) );

  for ( int i = 5; i < 10; i++ )
    tree.add( f(100+i) );

  for ( int i = 10; i < 20; i++ )
    tree.add( f(150+i) );

  for ( int i = 20; i < 30; i++ )
    tree.add( f(200+i) );

  // Test size

  ECE2400_CHECK_INT_EQ( tree.size(), 30 );

  // Test data

  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_TRUE( tree.contains( f(50+i) ) );

  for ( int i = 5; i < 10; i++ )
    ECE2400_CHECK_TRUE( tree.contains( f(100+i) ) );

  for ( int i = 10; i < 20; i++ )
    ECE2400_CHECK_TRUE( tree.contains( f(150+i) ) );

  for ( int i = 20; i < 30; i++ )
    ECE2400_CHECK_TRUE( tree.contains( f(200+i) ) );

  // Test contains, expecting not successful

  for ( int i = 0; i < 50; i++ )
    ECE2400_CHECK_FALSE( tree.contains( f(i) ) );
}


//------------------------------------------------------------------------
// test_case_one_node
//------------------------------------------------------------------------
// A general test case for trees with a single node.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_one_node( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct tree & add single element
  Tree<T,CmpFunc> tree( 42, cmp );
  tree.add( f(5) );

  // Test size() and contains()
  ECE2400_CHECK_INT_EQ( tree.size(), 1);
  ECE2400_CHECK_TRUE( tree.contains( f(5) ) );

  // Test find closest
  ECE2400_CHECK_TRUE( tree.find_closest(f(5), dist) == f(5)  );
  ECE2400_CHECK_TRUE( tree.find_closest(f(0), dist) == f(5) );
  ECE2400_CHECK_TRUE( tree.find_closest(f(100), dist) == f(5)  );

  // Basic copy constructor test ----
  
  Tree<T,CmpFunc> tree1( tree );
  ECE2400_CHECK_TRUE( tree1.contains( f(5) ) );
  ECE2400_CHECK_INT_EQ( tree1.size(), 1);

  // Ensure deep copy:
  tree1.add( f(10) );
  ECE2400_CHECK_INT_EQ( tree1.size(), 2 );
  ECE2400_CHECK_INT_EQ( tree.size(), 1  );

  ECE2400_CHECK_TRUE( tree1.contains( f(10) ) );
  ECE2400_CHECK_FALSE( tree.contains( f(10) ) );
}


//------------------------------------------------------------------------
// test_case_two_nodes
//------------------------------------------------------------------------
// A general test case for all permutations of tree with two nodes.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_two_nodes( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct trees & add elements
  std::vector<Tree<T,CmpFunc>> trees(2, Tree<T,CmpFunc>( 42, cmp ));
  trees[0].add( f(5) ); // Perm 1
  trees[0].add( f(8) );
  trees[1].add( f(8) ); // Perm 2
  trees[1].add( f(5) );

  trees[0].print();

  // Test size() and contains()
  for ( int i = 0; i < 2; ++i ) {
    ECE2400_CHECK_INT_EQ( trees[i].size(), 2);
    ECE2400_CHECK_TRUE( trees[i].contains( f(5) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(8) ) );
  }
  
  // Test find closest
  for ( int i = 0; i < 2; ++i ) {
    printf("i is %d\n", i);
    ECE2400_CHECK_TRUE( trees[i].find_closest(f(1), dist) == f(5) );
    ECE2400_CHECK_TRUE( trees[i].find_closest(f(6), dist) == f(5) );
    ECE2400_CHECK_TRUE( trees[i].find_closest(f(8), dist) == f(8) );
    ECE2400_CHECK_TRUE( trees[i].find_closest(f(23), dist) == f(8) );
  }
}


//------------------------------------------------------------------------
// test_case_three_nodes
//------------------------------------------------------------------------
// A general test case for all permutations of tree with three nodes.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_three_nodes( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct trees
  std::vector<Tree<T,CmpFunc>> trees(6, Tree<T,CmpFunc>( 42, cmp ));

  // All possible permutations of ints 1, 5, 9
  int perms[6][3] = {
    {1, 5, 9}, {5, 1, 9}, {5, 9, 1}, {1, 9, 5},
    {9, 1, 5}, {9, 5, 1}
  };

  // Generate a tree for each permutation
  for ( int i = 0; i < 6; ++i ) {
    for ( int j = 0; j < 3; ++j ) {
      trees[i].add( f( perms[i][j] ) );
    }
  }
  
  // Test size() and contains()
  for ( int i = 0; i < 6; ++i ) {
    ECE2400_CHECK_INT_EQ( trees[i].size(), 3);
    ECE2400_CHECK_TRUE( trees[i].contains( f(1) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(5) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(9) ) );
  }
  
  // Test find closest
  for ( int i = 0; i < 6; ++i ) {
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(0), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(1), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(2), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(4), dist) == f(5) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(5), dist) == f(5) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(6), dist) == f(5) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(8), dist) == f(9) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(9), dist) == f(9) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(15), dist) == f(9) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(200), dist) == f(9) );
  }
}

//------------------------------------------------------------------------
// test_case_four_nodes
//------------------------------------------------------------------------
// A general test case for all permutations of tree with four nodes.

template < typename T, typename Func, typename CmpFunc, typename DistFunc >
void test_case_four_nodes( int test_case_num, Func f, CmpFunc cmp, DistFunc dist )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct trees
  std::vector<Tree<T,CmpFunc>> trees(24, Tree<T,CmpFunc>( 42, cmp ));

  // All possible permutations of ints 1, 7, 15, 30
  int perms[24][4] = {
    {1,15,30,7}, {1,15,7,30}, {1,30,15,7}, {1,30,7,15}, {1,7,15,30}, {1,7,30,15},
    {15,1,30,7}, {15,1,7,30}, {15,30,1,7}, {15,30,7,1}, {15,7,30,1}, {15,7,1,30},
    {30,1,15,7}, {30,1,7,15}, {30,15,1,7}, {30,15,7,1}, {30,7,15,1}, {30,7,1,15},
    {7,1,15,30}, {7,1,30,15}, {7,15,1,30}, {7,15,30,1}, {7,30,15,1}, {7,30,1,15}
  };

  // Generate a tree for each permutation
  for ( int i = 0; i < 24; ++i ) {
    for ( int j = 0; j < 4; ++j ) {
      trees[i].add( f( perms[i][j] ) );
    }
  }
  
  // Test size() and contains()
  for ( int i = 0; i < 24; ++i ) {
    ECE2400_CHECK_INT_EQ( trees[i].size(), 4);
    ECE2400_CHECK_TRUE( trees[i].contains( f(1) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(7) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(15) ) );
    ECE2400_CHECK_TRUE( trees[i].contains( f(30) ) );
  }
  
  // Test find closest
  for ( int i = 0; i < 24; ++i ) {
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(0), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(1), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(3), dist) == f(1) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(5), dist) == f(7) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(7), dist) == f(7) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(9), dist) == f(7) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(13), dist) == f(15) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(15), dist) == f(15) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(17), dist) == f(15) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(25), dist) == f(30) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(30), dist) == f(30) );
    ECE2400_CHECK_TRUE( trees[i].find_closest( f(35), dist) == f(30) );
  }
}