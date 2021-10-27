# ======================================================================
#  ifdh_art main build file
#
# ======================================================================
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

find_package(cetmodules 2.29.07 REQUIRED)
project(ifdh_art VERSION 2.12.05 LANGUAGES CXX)

include(CetCMakeEnv)
cet_cmake_env()

# Find our own CMake modules, and tell everyone else where to find them.
cet_cmake_module_directories(Modules)

cet_set_compiler_flags(DIAGS VIGILANT
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic
)

cet_report_compiler_flags(REPORT_THRESHOLD VERBOSE)

find_package(art REQUIRED)
find_package(libwda REQUIRED)
find_package(ifdhc REQUIRED)
find_package(ifbeam REQUIRED)
find_package(nucondb REQUIRED)
find_package(cetlib_except REQUIRED)

# macros
include(ArtMake)
include(BuildPlugins)

add_subdirectory (src)
#add_subdirectory (tests)

# packaging utility
cet_cmake_config()
