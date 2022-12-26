//========================================================================
// ece2400-stdlib.cc
//========================================================================
// Standard library for ece2400 in C++.
//
// Author: Yanghui Ou, Peitian Pan
//   Date: Nov 5, 2020

#include "ece2400-stdlib.h"
#include <algorithm>
#include <cstring>
#include <string>
#include <sys/time.h>

const double ece2400::million = 1000000.0;

//------------------------------------------------------------------------
// Check-macro variables
//------------------------------------------------------------------------

// __n  > 0: display full [ passed ] line
// __n == 0: do not display anything for passed case
// __n  < 0: display a dot for passed case
int ece2400::__n = 1;

// The status of the current test file. Any failed check sets
// this variable to 1.
int ece2400::__failed = 0;

// Temporary variable to save the condition so that we don't
// evaluate the given expressions multiple times.
int    ece2400::__failure_condition = 0;
char   ece2400::__char_expr0        = '\0';
char   ece2400::__char_expr1        = '\0';
int    ece2400::__int_expr0         = 0;
int    ece2400::__int_expr1         = 0;
double ece2400::__double_expr0      = 0.0;
double ece2400::__double_expr1      = 0.0;

//------------------------------------------------------------------------
// Timer variables
//------------------------------------------------------------------------

struct timeval ece2400::start_time;
struct timeval ece2400::end_time;

//------------------------------------------------------------------------
// OutOfRange
//------------------------------------------------------------------------

ece2400::OutOfRange::OutOfRange()
{
}

ece2400::OutOfRange::OutOfRange( const char* err_msg ) : m_err_msg( err_msg )
{
}

std::string ece2400::OutOfRange::to_str() const
{
  return m_err_msg;
}

//------------------------------------------------------------------------
// InvalidArgument
//------------------------------------------------------------------------

ece2400::InvalidArgument::InvalidArgument()
{
}

ece2400::InvalidArgument::InvalidArgument( const char* err_msg )
    : m_err_msg( err_msg )
{
}

std::string ece2400::InvalidArgument::to_str() const
{
  return m_err_msg;
}

//------------------------------------------------------------------------
// log2
//------------------------------------------------------------------------
// To find log2(x) we can just repeatedly do (( x/2 ) / 2 ) / 2 until the
// result is zero.

int ece2400::log2( int x )
{
  int result = 0;
  while ( x > 1 ) {
    x = x / 2;
    result++;
  }
  return result;
}

//------------------------------------------------------------------------
// print_array
//------------------------------------------------------------------------
// Prints the contents in an integer array.

void ece2400::print_array( int* a, int size )
{
  if ( size > 0 )
    std::printf( "%d", a[0] );
  for ( int i = 1; i < size; i++ )
    std::printf( ", %d", a[i] );
  std::printf( "\n" );
}

//------------------------------------------------------------------------
// sort
//------------------------------------------------------------------------
// A reference sorting function that sorts an array of integer in
// ascending order.

void ece2400::sort( int* a, int size )
{
  std::sort( a, a + size );
}

//------------------------------------------------------------------------
// timer_reset
//------------------------------------------------------------------------
// Resets the timer.

void ece2400::timer_reset()
{
  gettimeofday( &ece2400::start_time, NULL );
}

//------------------------------------------------------------------------
// timer_get_elapsed
//------------------------------------------------------------------------
//  Return the elapased time in seconds.

double ece2400::timer_get_elapsed()
{
  gettimeofday( &ece2400::end_time, NULL );
  double elapsed_sec =
      (double) ( ece2400::end_time.tv_sec - ece2400::start_time.tv_sec );
  double elapsed_usec =
      (double) ( ece2400::end_time.tv_usec - ece2400::start_time.tv_usec );
  double elapsed_time = elapsed_sec + ( elapsed_usec / ece2400::million );
  return elapsed_time;
}

//************************************************************************
// DO NOT DIRECTLY CALL THE FUNCTIONS BELOW!
//************************************************************************
// The functions implemented below are helper functions that should only
// be called in ECE2400_CHECK_* macros.

//------------------------------------------------------------------------
// __get_file_name
//------------------------------------------------------------------------
// Return file name extracted from a __FILE__ string.

const char* ece2400::__get_file_name( const char* full_path )
{
  int len = (int) std::strlen( full_path ), start_pos = 0;

  for ( int i = len - 1; i >= 0; i-- )
    if ( full_path[i] == '/' ) {
      start_pos = i + 1;
      break;
    }

  return full_path + start_pos;
}

//------------------------------------------------------------------------
// __fail
//------------------------------------------------------------------------

void ece2400::__fail( const char* file, int lineno, const char* expr )
{
  file = ece2400::__get_file_name( file );
  if ( ece2400::__n < 0 )
    std::printf( "\n" );
  std::printf( " - [ " RED "FAILED" RESET " ] %s:%d:  %s\n", file, lineno,
               expr );
  ece2400::__failed = 1;
}

//------------------------------------------------------------------------
// __check_and_print_uniop
//------------------------------------------------------------------------

void ece2400::__check_and_print_uniop( const char* file, int lineno,
                                       const char* expr )
{
  file = ece2400::__get_file_name( file );
  if ( ece2400::__failure_condition ) {
    if ( ece2400::__n < 0 )
      std::printf( "\n" );
    std::printf( " - [ " RED "FAILED" RESET " ] %s:%d:  %s (%d)\n", file,
                 lineno, expr, ece2400::__int_expr0 );
    ece2400::__failed = 1;
  }
  else if ( ece2400::__n > 0 ) {
    std::printf( " - [ " GREEN "passed" RESET " ] %s:%d:  %s (%d)\n", file,
                 lineno, expr, ece2400::__int_expr0 );
  }
  else if ( ece2400::__n < 0 ) {
    std::printf( GREEN "." RESET );
  }
}

//------------------------------------------------------------------------
// __check_and_print_int_binop
//------------------------------------------------------------------------

void ece2400::__check_and_print_int_binop( const char* file, int lineno,
                                           const char* expr1,
                                           const char* expr2 )
{
  file = ece2400::__get_file_name( file );
  if ( ece2400::__failure_condition ) {
    if ( ece2400::__n < 0 )
      std::printf( "\n" );
    std::printf( " - [ " RED "FAILED" RESET " ] %s:%d:  %s != %s (%d != %d)\n",
                 file, lineno, expr1, expr2, ece2400::__int_expr0,
                 ece2400::__int_expr1 );
    ece2400::__failed = 1;
  }
  else if ( ece2400::__n > 0 ) {
    std::printf(
        " - [ " GREEN "passed" RESET " ] %s:%d:  %s == %s (%d == %d)\n", file,
        lineno, expr1, expr2, ece2400::__int_expr0, ece2400::__int_expr1 );
  }
  else if ( ece2400::__n < 0 ) {
    std::printf( GREEN "." RESET );
  }
}

//------------------------------------------------------------------------
// __check_and_print_char_binop
//------------------------------------------------------------------------

void ece2400::__check_and_print_char_binop( const char* file, int lineno,
                                            const char* expr1,
                                            const char* expr2 )
{
  file = ece2400::__get_file_name( file );
  if ( ece2400::__failure_condition ) {
    if ( ece2400::__n < 0 )
      std::printf( "\n" );
    std::printf( " - [ " RED "FAILED" RESET " ] %s:%d:  %s != %s (%c != %c)\n",
                 file, lineno, expr1, expr2, ece2400::__char_expr0,
                 ece2400::__char_expr1 );
    ece2400::__failed = 1;
  }
  else if ( ece2400::__n > 0 ) {
    std::printf(
        " - [ " GREEN "passed" RESET " ] %s:%d:  %s == %s (%c == %c)\n", file,
        lineno, expr1, expr2, ece2400::__char_expr0, ece2400::__char_expr1 );
  }
  else if ( ece2400::__n < 0 ) {
    std::printf( GREEN "." RESET );
  }
}

//------------------------------------------------------------------------
// __check_and_print_double_binop
//------------------------------------------------------------------------

void ece2400::__check_and_print_double_binop( const char* file, int lineno,
                                              const char* expr1,
                                              const char* expr2 )
{
  file = ece2400::__get_file_name( file );
  if ( ece2400::__failure_condition ) {
    if ( ece2400::__n < 0 )
      std::printf( "\n" );
    std::printf( " - [ " RED "FAILED" RESET
                 " ] %s:%d:  %s != %s (%.10e != %.10e)\n",
                 file, lineno, expr1, expr2, ece2400::__double_expr0,
                 ece2400::__double_expr1 );
    ece2400::__failed = 1;
  }
  else if ( ece2400::__n > 0 ) {
    std::printf( " - [ " GREEN "passed" RESET
                 " ] %s:%d:  %s == %s (%.10e == %.10e)\n",
                 file, lineno, expr1, expr2, ece2400::__double_expr0,
                 ece2400::__double_expr1 );
  }
  else if ( ece2400::__n < 0 ) {
    std::printf( GREEN "." RESET );
  }
}
