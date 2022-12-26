#=========================================================================
# CMake script for PA5
#=========================================================================
# To add new implementations or new tests, simply append your new file to
# the corresponding list.
#
# Author: Yanghui Ou, Christopher Batten
#   Date: September 26, 2019
#

set( SRC_FILES
  ece2400-stdlib.cc
  mnist-utils.cc
  Image.cc
  HRSLinearSearch.cc
  HRSBinarySearch.cc
  HRSTreeSearch.cc
  #HRSTableSearch.cc
  HRSAlternative.cc
)

set( TEST_MILESTONE_FILES
  sort-int-directed-test.cc
  sort-int-random-test.cc
  vector-int-directed-test.cc
  vector-int-random-test.cc
  image-directed-test.cc
  image-random-test.cc
  sort-image-directed-test.cc
  sort-image-random-test.cc
  vector-image-directed-test.cc
  vector-image-random-test.cc
)

set( TEST_ALL_FILES
  ${TEST_MILESTONE_FILES}
  tree-int-directed-test.cc
  tree-int-random-test.cc
  tree-image-directed-test.cc
  tree-image-random-test.cc
  #table-int-directed-test.cc
  #table-int-random-test.cc
  #table-image-directed-test.cc
  #table-image-random-test.cc
  hrs-linear-search-directed-test.cc
  hrs-binary-search-directed-test.cc
  hrs-tree-search-directed-test.cc
  #hrs-table-search-directed-test.cc
  hrs-alternative-directed-test.cc
)

set( EVAL_FILES
  hrs-linear-search-eval.cc
  hrs-binary-search-eval.cc
  hrs-tree-search-eval.cc
  #hrs-table-search-eval.cc
  hrs-alternative-eval.cc
  #hrs-backend.cc
)

#-------------------------------------------------------------------------
# remove_extension
#-------------------------------------------------------------------------
# Removes the file extension. For example:
# remove_extension(IMPL, "pow-iter.c") stores "pow-iter" into IMPL.

function( remove_extension VARNAME FILE_NAME )
  string( REGEX REPLACE "\\.[^.]*$" "" NAME_WITHOUT_EXT ${FILE_NAME} )
  set( ${VARNAME} "${NAME_WITHOUT_EXT}" PARENT_SCOPE )
endfunction()

#-------------------------------------------------------------------------
# Set up environment
#-------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8...3.19)
enable_language(CXX)
project(pa5-sys)

# Make sure we are using the correct version of gcc
set(ece2400_gcc_version "6.3.1")
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ece2400_gcc_version)
    message(FATAL_ERROR "It seems like your CMAKE GNU C++ compiler has "
                        "version ${CMAKE_CXX_COMPILER_VERSION} but the "
                        "required version for ECE 2400 PAs is >= "
                        "${ece2400_gcc_version}. Please make sure you "
                        "are developing on ECELinux and that you have "
                        "sourced the setup script for ECE 2400. If "
                        "this error persists, please rerun the build "
                        "system after removing all files in your build "
                        "directory (rm -rf build).")
  endif()
else()
  message(FATAL_ERROR "It seems like your CMAKE C++ compiler is "
                      "${CMAKE_CXX_COMPILER_ID}. The build system of "
                      "ECE 2400 PAs requires a GNU C++ compiler. "
                      "Please make sure you are developing on ECELinux "
                      "and that you have sourced the setup script for "
                      "ECE 2400!")
endif()

# Set the valgrind options (must do this _before_ including CTest!
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --undef-value-errors=no --error-exitcode=1" )

# Include CTest to manage our unit testing
include(CTest)

# Set and cache the build type
set( default_build_type "debug" )
set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "debug" "eval" )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE "${default_build_type}" )
endif()
message( STATUS "Setting build type to '${CMAKE_BUILD_TYPE}'" )

# Flags for g++
set( CMAKE_CXX_FLAGS       "${CMAKE_C_FLAGS} -Wall -Wextra -Wvla -Werror -Werror=vla -Wconversion -Wuninitialized -std=c++11 -pthread" )
set( CMAKE_CXX_FLAGS_DEBUG "-O0 -g --coverage -Wno-unused-parameter" )
set( CMAKE_CXX_FLAGS_EVAL  "-DEVAL -O3 -g -Wno-unused-parameter" )

# Path to this PA's source files
set( SRC_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src"  )
set( TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" )
set( EVAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eval" )

# Include path to this PA's header files
include_directories( ${SRC_DIR} )

#-------------------------------------------------------------------------
# Link source files into a library
#-------------------------------------------------------------------------

foreach( SRC_FILE ${SRC_FILES} )
  set( LIB_SRCS ${LIB_SRCS} "${SRC_DIR}/${SRC_FILE}" )
endforeach( SRC_FILE )

add_library( ${PROJECT_NAME} ${LIB_SRCS} )

#-------------------------------------------------------------------------
# Check targets
#-------------------------------------------------------------------------

add_custom_target( check
  COMMAND ${CMAKE_CTEST_COMMAND} --timeout 10 ${CTEST_OUTPUT_ON_FAILURE}
)

add_custom_target( memcheck
  COMMAND ${CMAKE_CTEST_COMMAND} --test-action memcheck
)

foreach( TEST_FILE ${TEST_ALL_FILES} )

  remove_extension( TEST_BIN ${TEST_FILE} )
  set( TEST_SRC "${TEST_DIR}/${TEST_FILE}" )

  add_executable( ${TEST_BIN} EXCLUDE_FROM_ALL ${TEST_SRC} )
  target_link_libraries( ${TEST_BIN} m ${PROJECT_NAME} )
  add_dependencies( check ${TEST_BIN} )
  add_dependencies( memcheck ${TEST_BIN} )
  add_test( ${TEST_BIN} ${TEST_BIN} )

endforeach(TEST_FILE)

#-------------------------------------------------------------------------
# Milestone check targets
#-------------------------------------------------------------------------

add_custom_target( check-milestone
  COMMAND ${CMAKE_CTEST_COMMAND} --timeout 10
                                 --label-regex milestone
)

add_custom_target( memcheck-milestone
  COMMAND ${CMAKE_CTEST_COMMAND} --test-action memcheck
                                 --label-regex milestone
)

foreach( TEST_FILE ${TEST_MILESTONE_FILES} )

  remove_extension( TEST_BIN ${TEST_FILE} )
  add_dependencies( check-milestone ${TEST_BIN} )
  add_dependencies( memcheck-milestone ${TEST_BIN} )
  set_tests_properties( ${TEST_BIN} PROPERTIES LABELS "milestone" )

endforeach( TEST_FILE )

#-------------------------------------------------------------------------
# Evaluation targets
#-------------------------------------------------------------------------

add_custom_target( eval )

foreach( EVAL_FILE ${EVAL_FILES} )

  remove_extension( EVAL_BIN ${EVAL_FILE} )
  set( EVAL_SRC "${EVAL_DIR}/${EVAL_FILE}" )

  add_executable( ${EVAL_BIN} EXCLUDE_FROM_ALL ${EVAL_SRC} )
  target_link_libraries( ${EVAL_BIN} m ${PROJECT_NAME} )
  add_dependencies( eval ${EVAL_BIN} )

endforeach( EVAL_FILE )

#-------------------------------------------------------------------------
# Code coverage target
#-------------------------------------------------------------------------

find_program( LCOV_COMMAND    lcov    )
find_program( GENHTML_COMMAND genhtml )

add_custom_target( coverage
  COMMAND ${LCOV_COMMAND} --capture --directory . --exclude '*stdlib*'
                          --exclude '*std*' --exclude '*test*'
                          --exclude '*stafftest*' --output-file coverage.info
  COMMAND ${GENHTML_COMMAND} coverage.info --output-directory coverage-html
  COMMAND ${LCOV_COMMAND} --list coverage.info
)

#-------------------------------------------------------------------------
# Clang format target
#-------------------------------------------------------------------------

add_custom_target(clang-format
  COMMAND echo ""
  COMMAND echo "========================================================="
  COMMAND echo " clang-format has finished!                              "
  COMMAND echo "========================================================="
  COMMAND echo ""
)

add_custom_target(clang-format-check-git-clean
  COMMAND git diff --exit-code > /dev/null || {
              echo &&
              echo ========================================================= &&
              echo  \ Your git repo has unstaged changes. Please commit all  &&
              echo  \ your changes before running clang-format!              &&
              echo ========================================================= &&
              echo &&
              exit 1\;
          }
)

add_custom_target(clang-format-run
  COMMAND mkdir -p "clang-format-log"
  COMMAND clang-format "-i"
                       "-style=file"
                       "${SRC_DIR}/*.cc"
                       "${SRC_DIR}/*.h"
                       "${SRC_DIR}/*.inl"
                       "${TEST_DIR}/*.cc"
                       "2>&1" "clang-format-log/c_files.stdout" || exit 0
)

add_dependencies(clang-format-run clang-format-check-git-clean)
add_dependencies(clang-format clang-format-run)

#-------------------------------------------------------------------------
# ECE2400 format target
#-------------------------------------------------------------------------

add_custom_target(ece2400-format
  COMMAND echo ""
  COMMAND echo "========================================================="
  COMMAND echo " ece2400-format has finished!                            "
  COMMAND echo "========================================================="
  COMMAND echo ""
)

add_custom_target(ece2400-format-run
  COMMAND python3 ${SRC_DIR}/../../scripts/ece2400-format.py
)

add_dependencies(ece2400-format-run clang-format-check-git-clean)
add_dependencies(ece2400-format clang-format-run)

#-------------------------------------------------------------------------
# autoformat target
#-------------------------------------------------------------------------

add_custom_target(autoformat
  COMMAND echo ""
  COMMAND echo "========================================================="
  COMMAND echo " autoformat has finished! Please check your code or do "
  COMMAND echo " ``git diff'' to inspect the changes.                    "
  COMMAND echo "========================================================="
  COMMAND echo ""
)

add_dependencies(autoformat clang-format ece2400-format)