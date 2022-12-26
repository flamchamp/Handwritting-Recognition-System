//========================================================================
// table-directed-tests.h
//========================================================================
// This file contains generic directed tests for tables. All of the
// generic test functions are templated by an "object creation" function
// which should take as a parameter an integer and return a newly created
// object. For integers, the object creation function can just be the
// identity function. For images, the object creation function can create
// a small image and initialize the pixels based on the given integer.

#include "Table.h"
#include "ece2400-stdlib.h"

#include <cstdio>

//------------------------------------------------------------------------
// test_case_simple_add
//------------------------------------------------------------------------
// A simple test case that tests default constructor, add, and contains.
// This uses a single bin.

template < typename T, typename Func, typename HashFunc >
void test_case_simple_add( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Table<T,HashFunc> table( 5, hash );

  // Check size of empty table
  ECE2400_CHECK_INT_EQ( table.size(), 0 );

  // Push back some values
  T data[] = { f(10), f(11), f(12) };
  for ( T v : data )
    table.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( table.size(), 3 );

  // Check values
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_TRUE( table.contains( data[i] ) );
}

//------------------------------------------------------------------------
// test_case_2bin_add
//------------------------------------------------------------------------
// A simple test case that tests default constructor, add, and conatins.
// This uses two bins.

template < typename T, typename Func, typename HashFunc >
void test_case_2bin_add( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Table<T,HashFunc> table( 4, hash );

  // Check size of empty table
  ECE2400_CHECK_INT_EQ( table.size(), 0 );

  // Push back some values
  T data[] = { f(10), f(11), f(12), f(160), f(161), f(162) };
  for ( T v : data )
    table.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( table.size(), 6 );

  // Check values
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_TRUE( table.contains( data[i] ) );
}

//------------------------------------------------------------------------
// test_case_duplicate_add
//------------------------------------------------------------------------
// A simple test case that tests adding duplicates

template < typename T, typename Func, typename HashFunc >
void test_case_duplicate_add( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Table<T,HashFunc> table( 5, hash );

  // Check size of empty table
  ECE2400_CHECK_INT_EQ( table.size(), 0 );

  // Push back some values
  T data[] = { f(1), f(1), f(200), f(200), f(1), f(1), f(200), f(200) };
  for ( T v : data )
    table.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( table.size(), 8 );

  // Check values
  ECE2400_CHECK_TRUE( table.contains( f(1) ) );
  ECE2400_CHECK_TRUE( table.contains( f(200) ) );
}

//------------------------------------------------------------------------
// test_case_empty_bin
//------------------------------------------------------------------------
// A simple test case that tests default constructor, add, and conatins.
// This uses two bins, but one bin is empty.

template < typename T, typename Func, typename HashFunc >
void test_case_empty_bin( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Use the default constructor
  Table<T,HashFunc> table( 4, hash );

  // Check size of empty table
  ECE2400_CHECK_INT_EQ( table.size(), 0 );

  // Push back some values
  T data[] = { f(10), f(11), f(12), f(13), f(14), f(15) };
  for ( T v : data )
    table.add( v );

  // Check size
  ECE2400_CHECK_INT_EQ( table.size(), 6 );

  // Check values
  for ( int i = 0; i < 3; i++ )
    ECE2400_CHECK_TRUE( table.contains( data[i] ) );
}

//------------------------------------------------------------------------
// test_case_construct_empty
//------------------------------------------------------------------------
// A simple test case that tests empty table

template < typename T, typename Func, typename HashFunc >
void test_case_construct_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T,HashFunc> table( 3, hash );

  ECE2400_CHECK_INT_EQ( table.size(), 0 );
}

//------------------------------------------------------------------------
// test_case_contains_simple
//------------------------------------------------------------------------
// A simple test case that tests contains.

template < typename T, typename Func, typename HashFunc >
void test_case_contains_simple( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a table from array

  Table<T,HashFunc> table( 3, hash );

  T data[] = { f(1), f(29), f(90), f(250), f(0), f(240), f(2), f(230) };
  for ( T v : data )
    table.add( v );

  // Search for value, expecting success

  ECE2400_CHECK_TRUE( table.contains( f(1)  ) );
  ECE2400_CHECK_TRUE( table.contains( f(29) ) );
  ECE2400_CHECK_TRUE( table.contains( f(90)  ) );
  ECE2400_CHECK_TRUE( table.contains( f(250) ) );
  ECE2400_CHECK_TRUE( table.contains( f(0)  ) );
  ECE2400_CHECK_TRUE( table.contains( f(240) ) );
  ECE2400_CHECK_TRUE( table.contains( f(2)  ) );
  ECE2400_CHECK_TRUE( table.contains( f(230) ) );

  // Search for value, expecting failure

  ECE2400_CHECK_FALSE( table.contains( f(6) ) );
  ECE2400_CHECK_FALSE( table.contains( f(7) ) );
  ECE2400_CHECK_FALSE( table.contains( f(93) ) );
  ECE2400_CHECK_FALSE( table.contains( f(200) ) );
  ECE2400_CHECK_FALSE( table.contains( f(100) ) );
  ECE2400_CHECK_FALSE( table.contains( f(234) ) );
}

//------------------------------------------------------------------------
// test_case_contains_empty
//------------------------------------------------------------------------
// A simple test case that tests contains for an empty table.

template < typename T, typename Func, typename HashFunc >
void test_case_contains_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct an empty table

  Table<T,HashFunc> table( 2, hash );

  // Search for value, expecting failure

  for ( int i = 0; i < 10; i++ )
    ECE2400_CHECK_FALSE( table.contains( f(i) ) );
}

//------------------------------------------------------------------------
// test_case_find_closest
//------------------------------------------------------------------------
// This will create a relatively balanced table with a total of 16
// elements and four bins.

template < typename T, typename Func, typename DistFunc, typename HashFunc >
void test_case_find_closest( int test_case_num, Func f, DistFunc dist, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T,HashFunc> table( 5, hash );

  T data[] = { f(10), f(60), f(110), f(210),
               f(20), f(70), f(120), f(220),
               f(30), f(80), f(130), f(230),
               f(40), f(90), f(140), f(240), };

  for ( T v : data )
    table.add( v );

  // First find exact matches

  ECE2400_CHECK_TRUE( table.find_closest(f(10), dist) == f(10) );
  ECE2400_CHECK_TRUE( table.find_closest(f(20), dist) == f(20) );
  ECE2400_CHECK_TRUE( table.find_closest(f(30), dist) == f(30) );
  ECE2400_CHECK_TRUE( table.find_closest(f(40), dist) == f(40) );

  ECE2400_CHECK_TRUE( table.find_closest(f(60), dist) == f(60) );
  ECE2400_CHECK_TRUE( table.find_closest(f(70), dist) == f(70) );
  ECE2400_CHECK_TRUE( table.find_closest(f(80), dist) == f(80) );
  ECE2400_CHECK_TRUE( table.find_closest(f(90), dist) == f(90) );

  ECE2400_CHECK_TRUE( table.find_closest(f(110), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(120), dist) == f(120) );
  ECE2400_CHECK_TRUE( table.find_closest(f(130), dist) == f(130) );
  ECE2400_CHECK_TRUE( table.find_closest(f(140), dist) == f(140) );

  ECE2400_CHECK_TRUE( table.find_closest(f(210), dist) == f(210) );
  ECE2400_CHECK_TRUE( table.find_closest(f(220), dist) == f(220) );
  ECE2400_CHECK_TRUE( table.find_closest(f(230), dist) == f(230) );
  ECE2400_CHECK_TRUE( table.find_closest(f(240), dist) == f(240) );

  // Find near matches

  ECE2400_CHECK_TRUE( table.find_closest(f(9),   dist) == f(10)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(11),  dist) == f(10)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(59),  dist) == f(60)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(61),  dist) == f(60)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(109), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(111), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(219), dist) == f(220) );
  ECE2400_CHECK_TRUE( table.find_closest(f(221), dist) == f(220) );
}

//------------------------------------------------------------------------
// test_case_find_closest_empty
//------------------------------------------------------------------------
// This will create a table with a total of 16 elements and four bins,
// but one of the bins will be empty.

template < typename T, typename Func, typename DistFunc, typename HashFunc >
void test_case_find_closest_empty( int test_case_num, Func f, DistFunc dist, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T,HashFunc> table( 5, hash );

  T data[] = { f(10), f(60), f(110), f(210),
               f(20), f(70), f(120), f(220),
               f(30), f(80), f(50),  f(230),
               f(40), f(90), f(250), f(240), };

  for ( T v : data )
    table.add( v );

  // First find exact matches

  ECE2400_CHECK_TRUE( table.find_closest(f(10), dist) == f(10) );
  ECE2400_CHECK_TRUE( table.find_closest(f(20), dist) == f(20) );
  ECE2400_CHECK_TRUE( table.find_closest(f(30), dist) == f(30) );
  ECE2400_CHECK_TRUE( table.find_closest(f(40), dist) == f(40) );

  ECE2400_CHECK_TRUE( table.find_closest(f(60), dist) == f(60) );
  ECE2400_CHECK_TRUE( table.find_closest(f(70), dist) == f(70) );
  ECE2400_CHECK_TRUE( table.find_closest(f(80), dist) == f(80) );
  ECE2400_CHECK_TRUE( table.find_closest(f(90), dist) == f(90) );

  ECE2400_CHECK_TRUE( table.find_closest(f(110), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(120), dist) == f(120) );
  ECE2400_CHECK_TRUE( table.find_closest(f(50), dist) == f(50) );
  ECE2400_CHECK_TRUE( table.find_closest(f(250), dist) == f(250) );

  ECE2400_CHECK_TRUE( table.find_closest(f(210), dist) == f(210) );
  ECE2400_CHECK_TRUE( table.find_closest(f(220), dist) == f(220) );
  ECE2400_CHECK_TRUE( table.find_closest(f(230), dist) == f(230) );
  ECE2400_CHECK_TRUE( table.find_closest(f(240), dist) == f(240) );

  // Find near matches

  ECE2400_CHECK_TRUE( table.find_closest(f(9),   dist) == f(10)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(11),  dist) == f(10)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(59),  dist) == f(60)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(61),  dist) == f(60)  );
  ECE2400_CHECK_TRUE( table.find_closest(f(109), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(111), dist) == f(110) );
  ECE2400_CHECK_TRUE( table.find_closest(f(219), dist) == f(220) );
  ECE2400_CHECK_TRUE( table.find_closest(f(221), dist) == f(220) );

  // Search the empty bin

  ECE2400_CHECK_TRUE( table.find_closest( f(130), dist ) == T() );
  ECE2400_CHECK_TRUE( table.find_closest( f(140), dist ) == T() );
  ECE2400_CHECK_TRUE( table.find_closest( f(150), dist ) == T() );
  ECE2400_CHECK_TRUE( table.find_closest( f(160), dist ) == T() );
}

//------------------------------------------------------------------------
// test_case_to_vector
//------------------------------------------------------------------------
// A simple test case that tests to_vector when the table has only one row
template < typename T, typename Func, typename HashFunc >
void test_case_to_vector( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T, HashFunc> table( 10, hash );

  T data[] = { f(10), f(20), f(90), f(30), f(200), f(100) };

  int data_size = 0;
  for ( T v : data ) {
    table.add( v );
    data_size++;
  }

  Vector<T> vec = table.to_vector();

  int vec_size = vec.size();

  ECE2400_CHECK_TRUE( vec_size == data_size );

  for ( int i = 0; i < vec_size; i++ ) {
    ECE2400_CHECK_TRUE( data[i] == vec[i] );
  }
}

//------------------------------------------------------------------------
// test_case_to_vector_rehash
//------------------------------------------------------------------------
// A simple test case that tests to_vector when the table grows large
// enough to require a rehash
template < typename T, typename Func, typename HashFunc >
void test_case_to_vector_rehash( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T, HashFunc> table( 10, hash );

  T data[] = {  f(10), f(20),  f(90),  f(30), f(200),
               f(100), f(15), f(230), f(240),   f(5),
               f(101), f(21), f(160),  f(31),   f(6) };

  int data_size = 0;
  for ( T v : data ) {
    table.add( v );
    data_size++;
  }

  Vector<T> vec = table.to_vector();

  int vec_size = vec.size();

  ECE2400_CHECK_TRUE( vec_size == data_size );

  ECE2400_CHECK_TRUE( vec[0]  == f(10) );
  ECE2400_CHECK_TRUE( vec[1]  == f(20) );
  ECE2400_CHECK_TRUE( vec[2]  == f(90) );
  ECE2400_CHECK_TRUE( vec[3]  == f(30) );
  ECE2400_CHECK_TRUE( vec[4]  == f(100) );
  ECE2400_CHECK_TRUE( vec[5]  == f(15) );
  ECE2400_CHECK_TRUE( vec[6]  == f(5) );
  ECE2400_CHECK_TRUE( vec[7]  == f(101) );
  ECE2400_CHECK_TRUE( vec[8]  == f(21) );
  ECE2400_CHECK_TRUE( vec[9]  == f(31) );
  ECE2400_CHECK_TRUE( vec[10] == f(6) );
  ECE2400_CHECK_TRUE( vec[11] == f(200) );
  ECE2400_CHECK_TRUE( vec[12] == f(230) );
  ECE2400_CHECK_TRUE( vec[13] == f(240) );
  ECE2400_CHECK_TRUE( vec[14] == f(160) );
}

//------------------------------------------------------------------------
// test_case_to_vector_rehash
//------------------------------------------------------------------------
// A simple test case that tests to_vector when the table grows large
// enough to require two rehashes
template < typename T, typename Func, typename HashFunc >
void test_case_to_vector_2rehash( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  Table<T, HashFunc> table( 5, hash );

  T data[] = {  f(10), f(20),  f(90),  f(30), f(200),
               f(100), f(15), f(230), f(240),   f(5),
               f(101), f(21), f(160),  f(31),   f(6) };

  int data_size = 0;
  for ( T v : data ) {
    table.add( v );
    data_size++;
  }

  Vector<T> vec = table.to_vector();

  int vec_size = vec.size();

  ECE2400_CHECK_TRUE( vec_size == data_size );

  ECE2400_CHECK_TRUE( vec[0]  == f(10) );
  ECE2400_CHECK_TRUE( vec[1]  == f(20) );
  ECE2400_CHECK_TRUE( vec[2]  == f(30) );
  ECE2400_CHECK_TRUE( vec[3]  == f(15) );
  ECE2400_CHECK_TRUE( vec[4]  == f(5) );
  ECE2400_CHECK_TRUE( vec[5]  == f(21) );
  ECE2400_CHECK_TRUE( vec[6]  == f(31) );
  ECE2400_CHECK_TRUE( vec[7]  == f(6) );
  ECE2400_CHECK_TRUE( vec[8]  == f(90) );
  ECE2400_CHECK_TRUE( vec[9]  == f(100) );
  ECE2400_CHECK_TRUE( vec[10] == f(101) );
  ECE2400_CHECK_TRUE( vec[11] == f(160) );
  ECE2400_CHECK_TRUE( vec[12] == f(200) );
  ECE2400_CHECK_TRUE( vec[13] == f(230) );
  ECE2400_CHECK_TRUE( vec[14] == f(240) );
}

//------------------------------------------------------------------------
// test_case_copy_v1
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with first syntax.

template < typename T, typename Func, typename HashFunc >
void test_case_copy_v1( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(10),  f(60),  f(150),  f(61)  };
  for ( T v : data0 )
    table0.add( v );

  // Copy constructor

  Table<T,HashFunc> table1( table0 );

  // Push different values to table0 and table1

  T data1[] = { f(20), f(70), f(210), f(71) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(180), f(31), f(81) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );
  ECE2400_CHECK_INT_EQ( table1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_copy_v2
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with second syntax.

template < typename T, typename Func, typename HashFunc >
void test_case_copy_v2( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(10),  f(60),  f(150),  f(61)  };
  for ( T v : data0 )
    table0.add( v );

  // Copy constructor with second syntax

  Table<T,HashFunc> table1 = table0;

  // Push different values to table0 and table1

  T data1[] = { f(20), f(70), f(210), f(71) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(180), f(31), f(81) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );
  ECE2400_CHECK_INT_EQ( table1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_copy_empty
//------------------------------------------------------------------------
// A simple test case that tests copy constructor with empty table.

template < typename T, typename Func, typename HashFunc >
void test_case_copy_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Copy constructor

  Table<T,HashFunc> table0( 3, hash );
  Table<T,HashFunc> table1 = table0;

  // Check both tables are empty

  ECE2400_CHECK_INT_EQ( table0.size(), 0 );
  ECE2400_CHECK_INT_EQ( table1.size(), 0 );

  // Push different values to table0 and table1

  T data0[] = { f(20), f(70), f(21), f(171) };
  for ( T v : data0 )
    table0.add( v );

  T data1[] = { f(30), f(80), f(31), f(181) };
  for ( T v : data1 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 4 );
  ECE2400_CHECK_INT_EQ( table1.size(), 4 );

  // Check the elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data1[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment
//------------------------------------------------------------------------
// A simple test case that tests assignment operator on a non-empty
// table.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(10),  f(60),  f(11),  f(161)  };
  for ( T v : data0 )
    table0.add( v );

  // Push back some values to table1

  Table<T,HashFunc> table1( 5, hash );
  for ( int i = 0; i < 10; i++ )
    table1.add( f(i) );

  // Assignment operator

  table1 = table0;

  // Push different values to table0 and table1

  T data1[] = { f(20), f(70), f(21), f(171) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(80), f(31), f(181) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );
  ECE2400_CHECK_INT_EQ( table1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_diff_nbins
//------------------------------------------------------------------------
// A test case that tests assignment operator when the two tables have
// different numbers of bins.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment_diff_nbins( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(10),  f(160),  f(11),  f(61)  };
  for ( T v : data0 )
    table0.add( v );

  // Push back some values to table1

  Table<T,HashFunc> table1( 30, hash );
  for ( int i = 0; i < 10; i++ )
    table1.add( f(i) );

  // Assignment operator

  table1 = table0;

  // Push different values to table0 and table1

  T data1[] = { f(20), f(170), f(21), f(71) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(80), f(31), f(81) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );
  ECE2400_CHECK_INT_EQ( table1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_to_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator to empty table from
// non-empty table.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment_to_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(210),  f(60),  f(11),  f(61)  };
  for ( T v : data0 )
    table0.add( v );

  // Assignment operator

  Table<T,HashFunc> table1( 2, hash );
  table1 = table0;

  // Push different values to table0 and table1

  T data1[] = { f(20), f(70), f(221), f(71) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(80), f(31), f(181) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );
  ECE2400_CHECK_INT_EQ( table1.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data0[i] ) );
  }

  // Check the last 4 elements

  for ( auto i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_from_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty table to
// non-empty table.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment_from_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 4, hash );
  T data0[] = { f(10),  f(60),  f(11),  f(61)  };
  for ( T v : data0 )
    table0.add( v );

  // Assignment operator

  Table<T,HashFunc> table1( 4, hash );
  table0 = table1;

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 0 );
  ECE2400_CHECK_INT_EQ( table1.size(), 0 );

  // Push different values to table0 and table1

  T data1[] = { f(220), f(70), f(21), f(71) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(30), f(80), f(231), f(81) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 4 );
  ECE2400_CHECK_INT_EQ( table1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_empty
//------------------------------------------------------------------------
// A simple test case that tests assignment operator from empty table to
// empty table.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment_empty( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Assignment operator

  Table<T,HashFunc> table0( 2, hash );
  Table<T,HashFunc> table1( 2, hash );
  table0 = table1;

  // Push different values to table0 and table1

  T data1[] = { f(20), f(70), f(21), f(171) };
  for ( T v : data1 )
    table0.add( v );

  T data2[] = { f(230), f(80), f(31), f(81) };
  for ( T v : data2 )
    table1.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 4 );
  ECE2400_CHECK_INT_EQ( table1.size(), 4 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ ) {
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
    ECE2400_CHECK_TRUE( table1.contains( data2[i] ) );
  }
}

//------------------------------------------------------------------------
// test_case_assignment_self
//------------------------------------------------------------------------
// A simple test case that tests self assignment.

template < typename T, typename Func, typename HashFunc >
void test_case_assignment_self( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Push back to table0

  Table<T,HashFunc> table0( 3, hash );
  T data0[] = { f(210),  f(60),  f(211),  f(161)  };
  for ( T v : data0 )
    table0.add( v );

  // Assignment operator

  table0 = table0;

  // Push more values into table0

  T data1[] = { f(220), f(170), f(21), f(171) };
  for ( T v : data1 )
    table0.add( v );

  // Check size

  ECE2400_CHECK_INT_EQ( table0.size(), 8 );

  // Check the first 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( table0.contains( data0[i] ) );

  // Check the second 4 elements

  for ( int i = 0; i < 4; i++ )
    ECE2400_CHECK_TRUE( table0.contains( data1[i] ) );
}

//------------------------------------------------------------------------
// test_case_general
//------------------------------------------------------------------------
// A generic test case.

template < typename T, typename Func, typename HashFunc >
void test_case_general( int test_case_num, Func f, HashFunc hash )
{
  std::printf( "\n%d: %s\n", test_case_num, __func__ );

  // Construct a new table

  Table<T,HashFunc> table( 20, hash );

  // Push data into the data structure

  for ( int i = 0; i < 5; i++ )
    table.add( f(50+i) );

  for ( int i = 5; i < 10; i++ )
    table.add( f(100+i) );

  for ( int i = 10; i < 20; i++ )
    table.add( f(150+i) );

  for ( int i = 20; i < 30; i++ )
    table.add( f(200+i) );

  // Test size

  ECE2400_CHECK_INT_EQ( table.size(), 30 );

  // Test data

  for ( int i = 0; i < 5; i++ )
    ECE2400_CHECK_TRUE( table.contains( f(50+i) ) );

  for ( int i = 5; i < 10; i++ )
    ECE2400_CHECK_TRUE( table.contains( f(100+i) ) );

  for ( int i = 10; i < 20; i++ )
    ECE2400_CHECK_TRUE( table.contains( f(150+i) ) );

  for ( int i = 20; i < 30; i++ )
    ECE2400_CHECK_TRUE( table.contains( f(200+i) ) );

  // Test contains, expecting not successful

  for ( int i = 0; i < 50; i++ )
    ECE2400_CHECK_FALSE( table.contains( f(i) ) );
}

