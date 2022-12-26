//========================================================================
// ece2400-stdlib.h
//========================================================================
// Standard library for ece2400 in C++.
//
// Author: Yanghui Ou, Peitian Pan
//   Date: Nov 5, 2020

#ifndef ECE2400_STDLIB_H
#define ECE2400_STDLIB_H

#include <cmath>
#include <cstdio>
#include <string>
#include <sys/time.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

//------------------------------------------------------------------------
// ECE2400_UNUSED()
//------------------------------------------------------------------------
#define ECE2400_UNUSED( x )                                   \
  do {                                                        \
    __attribute__( ( __unused__ ) ) int unused_##x = (int) x; \
  } while ( 0 )

//========================================================================
// ECE2400_CHECK_* macros
//========================================================================

//------------------------------------------------------------------------
// ECE2400_CHECK_FAIL()
//------------------------------------------------------------------------
// Unconditionally fail a test case.

#define ECE2400_CHECK_FAIL()                                     \
  do {                                                           \
    ece2400::__fail( __FILE__, __LINE__, "ECE2400_CHECK_FAIL" ); \
    return;                                                      \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_CHECK_TRUE( expr_ )
//------------------------------------------------------------------------
// Checks to see if the expression is true.

#define ECE2400_CHECK_TRUE( expr_ )                                 \
  do {                                                              \
    ece2400::__int_expr0         = expr_;                           \
    ece2400::__failure_condition = !ece2400::__int_expr0;           \
    ece2400::__check_and_print_uniop( __FILE__, __LINE__, #expr_ ); \
    if ( ece2400::__failure_condition )                             \
      return;                                                       \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_CHECK_FALSE( expr_ )
//------------------------------------------------------------------------
// Checks to see if the expression is false.

#define ECE2400_CHECK_FALSE( expr_ )                                \
  do {                                                              \
    ece2400::__int_expr0         = expr_;                           \
    ece2400::__failure_condition = ece2400::__int_expr0;            \
    ece2400::__check_and_print_uniop( __FILE__, __LINE__, #expr_ ); \
    if ( ece2400::__failure_condition )                             \
      return;                                                       \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_CHECK_CHAR_EQ( expr0_, expr1_ )
//------------------------------------------------------------------------
// Checks to see if the two expressions are equal using the != operator.

#define ECE2400_CHECK_CHAR_EQ( expr0_, expr1_ )                         \
  do {                                                                  \
    ece2400::__char_expr0 = (char) ( expr0_ );                          \
    ece2400::__char_expr1 = (char) ( expr1_ );                          \
    ece2400::__failure_condition =                                      \
        ece2400::__char_expr0 != ece2400::__char_expr1;                 \
    ece2400::__check_and_print_char_binop( __FILE__, __LINE__, #expr0_, \
                                           #expr1_ );                   \
    if ( ece2400::__failure_condition )                                 \
      return;                                                           \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_CHECK_INT_EQ( expr0_, expr1_ )
//------------------------------------------------------------------------
// Checks to see if the two expressions are equal using the != operator.

#define ECE2400_CHECK_INT_EQ( expr0_, expr1_ )                         \
  do {                                                                 \
    ece2400::__int_expr0 = (int) ( expr0_ );                           \
    ece2400::__int_expr1 = (int) ( expr1_ );                           \
    ece2400::__failure_condition =                                     \
        ece2400::__int_expr0 != ece2400::__int_expr1;                  \
    ece2400::__check_and_print_int_binop( __FILE__, __LINE__, #expr0_, \
                                          #expr1_ );                   \
    if ( ece2400::__failure_condition )                                \
      return;                                                          \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_CHECK_APPROX_EQ( expr0_, expr1_, pct_ )
//------------------------------------------------------------------------
// Checks to see if the two expressions are within percent of each other.

#define ECE2400_CHECK_APPROX_EQ( expr0_, expr1_, pct_ )                   \
  do {                                                                    \
    ece2400::__double_expr0 = expr0_;                                     \
    ece2400::__double_expr1 = expr1_;                                     \
    ece2400::__failure_condition =                                        \
        std::fabs( ece2400::__double_expr0 - ece2400::__double_expr1 ) >  \
        std::fabs( (double) (pct_) *ece2400::__double_expr1 );            \
    ece2400::__check_and_print_double_binop( __FILE__, __LINE__, #expr0_, \
                                             #expr1_ );                   \
    if ( ece2400::__failure_condition )                                   \
      return;                                                             \
  } while ( 0 )

//------------------------------------------------------------------------
// ECE2400_DEBUG( ... ) and ECE2400_DEBUG_NEWLINE
//------------------------------------------------------------------------
// Print out debug info when not in eval build. Note that debug info is
// only dumped to stdout when __n > 0 (i.e., we are looking at a specific
// test function).

#ifndef EVAL

#define ECE2400_DEBUG( ... )                                         \
  do {                                                               \
    if ( ece2400::__n > 0 ) {                                        \
      std::printf( " - [ " YELLOW "-info-" RESET " ] %s:%d: ",       \
                   ece2400::__get_file_name( __FILE__ ), __LINE__ ); \
      std::printf( __VA_ARGS__ );                                    \
      std::printf( "\n" );                                           \
    }                                                                \
  } while ( 0 )

#else

#define ECE2400_DEBUG( ... ) ;

#endif  // #ifndef EVAL

namespace ece2400 {

extern const double million;

//------------------------------------------------------------------------
// Check-macro variables
//------------------------------------------------------------------------

// __n  > 0: display full [ passed ] line
// __n == 0: do not display anything for passed case
// __n  < 0: display a dot for passed case
extern int __n;

// The status of the current test file. Any failed check sets
// this variable to 1.
extern int __failed;

// Temporary variable to save the condition so that we don't
// evaluate the given expressions multiple times.
extern int    __failure_condition;
extern char   __char_expr0;
extern char   __char_expr1;
extern int    __int_expr0;
extern int    __int_expr1;
extern double __double_expr0;
extern double __double_expr1;

//------------------------------------------------------------------------
// Timer variables
//------------------------------------------------------------------------

extern struct timeval start_time;
extern struct timeval end_time;

//------------------------------------------------------------------------
// Exception
//------------------------------------------------------------------------
// Base class for exceptions.

class Exception {
};

//------------------------------------------------------------------------
// OutOfRangeException
//------------------------------------------------------------------------
// Exception for out of range access.

class OutOfRange : Exception {
 public:
  OutOfRange();
  OutOfRange( const char* err_msg );

  std::string to_str() const;

 private:
  std::string m_err_msg;
};

//------------------------------------------------------------------------
// InvalidArgumentException
//------------------------------------------------------------------------
// Exception for out of range access.

class InvalidArgument : Exception {
 public:
  InvalidArgument();
  InvalidArgument( const char* err_msg );

  std::string to_str() const;

 private:
  std::string m_err_msg;
};

//------------------------------------------------------------------------
// log2
//------------------------------------------------------------------------
// Return nearest log base 2.

int log2( int x );

//------------------------------------------------------------------------
// print_array
//------------------------------------------------------------------------
// Prints the contents in an integer array.

void print_array( int* a, int size );

//------------------------------------------------------------------------
// sort
//------------------------------------------------------------------------
// A reference sorting function that sorts an array of integer in
// ascending order.

void sort( int* a, int size );

//------------------------------------------------------------------------
// timer_reset
//------------------------------------------------------------------------
// Resets the timer.

void timer_reset();

//------------------------------------------------------------------------
// timer_get_elapsed
//------------------------------------------------------------------------
// Return the elapased time in seconds.

double timer_get_elapsed();

//------------------------------------------------------------------------
// Check-macro helper functions
//------------------------------------------------------------------------
// These are internal helper functions and should not be called directly.

const char* __get_file_name( const char* );
void        __fail( const char*, int, const char* );
void        __check_and_print_uniop( const char*, int, const char* );
void __check_and_print_int_binop( const char*, int, const char*, const char* );
void __check_and_print_char_binop( const char*, int, const char*, const char* );
void __check_and_print_double_binop( const char*, int, const char*,
                                     const char* );

}  // namespace ece2400

#endif  // ECE2400_STDLIB_H
