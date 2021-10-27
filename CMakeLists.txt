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
# use cmake 3.12 or later
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)


find_package(cetmodules 2.29.07 REQUIRED)
project(ifdh_art VERSION 2.12.05 LANGUAGES CXX)

# cetbuildtools contains our cmake modules ### MIGRATE-ACTION-REQUIRED: remove
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} ) ### MIGRATE-ACTION-REQUIRED: remove
IF (NOT CETBUILDTOOLS_VERSION) ### MIGRATE-ACTION-REQUIRED: remove
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules") ### MIGRATE-ACTION-REQUIRED: remove
ENDIF()

set(CMAKE_MODULE_PATH $ENV{ART_DIR}/Modules ### MIGRATE-ACTION-REQUIRED: remove
                      $ENV{CETBUILDTOOLS_DIR}/Modules ### MIGRATE-ACTION-REQUIRED: remove
                      ${CMAKE_MODULE_PATH}) ### MIGRATE-ACTION-REQUIRED: remove

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic
)

cet_report_compiler_flags(REPORT_THRESHOLD VERBOSE)

find_ups_product( art ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_ups_product( ifdhc  ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_ups_product( ifbeam  ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_ups_product( nucondb  ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_ups_product( libwda  ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
find_ups_product( cetlib_except ) ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking

# include search path
# decide if we have IFDHC_FQ_DIR or IFDHC_DIR
if ( $ENV{IFDHC_FQ_DIR} MATCHES "ifdhc" )
  message(STATUS "using FQ_DIR")
  include_directories($ENV{IFDHC_FQ_DIR}/inc) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{LIBWDA_FQ_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{IFBEAM_FQ_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{NUCONDB_FQ_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
else()
  message(STATUS "using DIR")
  include_directories($ENV{IFDHC_DIR}/inc) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{LIBWDA_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{IFBEAM_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
  include_directories($ENV{NUCONDB_DIR}/include) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics
endif()

#ifdhc
cet_find_library( IFDH    NAMES ifdh    PATHS ENV IFDHC_LIB   NO_DEFAULT_PATH ) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
cet_find_library( IFBEAM  NAMES ifbeam  PATHS ENV IFBEAM_LIB  NO_DEFAULT_PATH ) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
cet_find_library( NUCONDB NAMES nucondb PATHS ENV NUCONDB_LIB NO_DEFAULT_PATH ) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking
cet_find_library( WDA     NAMES wda     PATHS ENV LIBWDA_LIB  NO_DEFAULT_PATH ) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking

# SQLite
cet_find_library(SQLITE3 NAMES sqlite3 PATHS ENV SQLITE_LIB NO_DEFAULT_PATH) ### MIGRATE-ACTION-RECOMMENDED: use of ENV ... may be UPS-dependent ### MIGRATE-ACTION-RECOMMENDED: use cet_find_package() with target semantics for linking

# macros
include(ArtMake)
include(BuildPlugins)

add_subdirectory (src)
#add_subdirectory (tests)

# packaging utility
cet_cmake_config()
