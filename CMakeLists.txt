# ======================================================================
#  art main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/art/ups/setup_for_development
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path]
#        -DCMAKE_BUILD_TYPE=$CETPKG_TYPE
#        $CETPKG_SOURCE
#  make
#  make test
#  make install
#  make package (builds distribution tarfile)
# ======================================================================

# use cmake 3.19 or later
cmake_minimum_required (VERSION 3.19)

project(ifdh_art VERSION 2.12.02 LANGUAGES CXX)

set(${product}_inc_dir ${CMAKE_INSTALL_PREFIX}/include)

find_package(cetmodules REQUIRED)
find_package(art REQUIRED)
find_package(messagefacility REQUIRED)
#ifdhc
find_library( IFDH    NAMES ifdh    PATHS ENV IFDHC_LIB )
find_library( IFBEAM  NAMES ifbeam  PATHS ENV IFBEAM_LIB)
find_library( NUCONDB NAMES nucondb PATHS ENV NUCONDB_LIB)
find_library( WDA     NAMES wda     PATHS ENV LIBWDA_LIB)
# SQLite
find_library(SQLITE3 NAMES sqlite3 PATHS ENV SQLITE_LIB)

get_filename_component(IFDH_LIB    ${IFDH}    DIRECTORY)
get_filename_component(IFBEAM_LIB  ${IFBEAM}  DIRECTORY)
get_filename_component(NUCONDB_LIB ${NUCONDB} DIRECTORY)
get_filename_component(WDA_LIB     ${WDA}     DIRECTORY)

message("IFDH is ${IFDH}, IFDH_LIB is ${IFDH_LIB}")

include_directories("${IFDH_LIB}/../inc")
include_directories("${IFBEAM_LIB}/../include")
include_directories("${NUCONDB_LIB}/../include")
include_directories("${WDA_LIB}/../include")

find_package(cetlib_except REQUIRED)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic
)

cet_report_compiler_flags()
# macros
include(ArtMake)
include(BuildPlugins)

add_subdirectory (src)

if ($WANT_UPS)
add_subdirectory (ups)
endif()

#packaging utility
include(UseCPack)
