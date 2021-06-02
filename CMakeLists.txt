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

find_package(cetmodules REQUIRED)
find_package(art REQUIRED)
cet_find_simple_package(ifbeam)
cet_find_simple_package(ifdh INCPATH_SUFFIXES inc)
cet_find_simple_package(nucondb)
cet_find_simple_package(wda)
cet_find_simple_package(sqlite3)
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
add_subdirectory (tests)
add_subdirectory(cmakeConfig)
if ($ENV{UPS_DIR})
add_subdirectory (ups)
endif()

#packaging utility
include(UseCPack)
