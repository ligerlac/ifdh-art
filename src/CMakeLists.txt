
macro( install_ifdh_headers   )
  _cet_check_inc_directory()
  set(header_install_dir ${${product}_inc_dir} )
  message( STATUS "install_ifdh_headers: headers will be installed in ${header_install_dir}" )
  FILE(GLOB headers [^.]*.h [^.]*.hh [^.]*.icc )
  if( headers )
    message( STATUS "installing headers ${headers} in ${header_install_dir}")
    INSTALL( FILES ${headers}
             DESTINATION ${header_install_dir} )
  endif( headers )
endmacro( install_ifdh_headers )


SET ( CMAKE_VERBOSE_MAKEFILE true )
# cetbuildtools contains our cmake modules
SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
IF (NOT CETBUILDTOOLS_VERSION)
    MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
ENDIF()
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules 
                      $ENV{CETBUILDTOOLS_DIR}/Modules 
                      $ENV{ART_DIR}/Modules 
		      ${CMAKE_MODULE_PATH})

include(CetCMakeEnv)
cet_cmake_env()

#cet_set_compiler_flags(DIAGS VIGILANT WERROR NO_UNDEFINED EXTRA_FLAGS -pedantic)
#cet_set_compiler_flags(DIAGS VIGILANT WERROR NO_UNDEFINED EXTRA_FLAGS -pedantic)
cet_set_compiler_flags(DIAGS VIGILANT NO_UNDEFINED EXTRA_FLAGS -pedantic)
cet_set_compiler_flags(DIAGS VIGILANT NO_UNDEFINED EXTRA_FLAGS -pedantic)
cet_have_qual(e4 E4)
if ( E4 )
  cet_add_compiler_flags(CXX -std=c++11)
endif()
cet_have_qual(sse4 SSE4)
if ( SSE4 )
  cet_add_compiler_flags(CXX -msse2 -ftree-vectorizer-verbose=2)
endif()

cet_report_compiler_flags()

# these are minimum required versions, not the actual product versions
 find_ups_product( art v1_06_00 )
 find_ups_product( ifdhc v1_1_3 )
 find_ups_product( ifbeam v1_1_3 )

cet_check_gcc()

# include search path
# notice use of ENV to invoke an external variable
include_directories ( $ENV{LIBSIGCPP_INC}/sigc++-2.0 )
include_directories ( $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include )
include_directories($ENV{IFDHC_DIR}/inc)
#include_directories($ENV{ART_DIR}/include)
include_directories($ENV{BOOST_INC})
include_directories($ENV{CETLIB_INC})
include_directories($ENV{CPP0X_INC})
include_directories($ENV{CPPUNIT_INC})
include_directories($ENV{FHICLCPP_INC})
include_directories($ENV{MESSAGEFACILITY_INC})
link_directories($ENV{ART_LIB})
link_directories($ENV{BOOST_LIB})
#link_directories($ENV{CETLIB_LIB})
#link_directories($ENV{CPP0X_LIB})
#link_directories($ENV{CPPUNIT_LIB})
#link_directories($ENV{FHICLCPP_LIB})
#link_directories($ENV{MESSAGEFACILITY_LIB})


# have to make sure cmake doesn't select the system libraries
# define libsigc
cet_find_library( SIGC    NAMES sigc-2.0  PATHS ENV LIBSIGCPP_LIB NO_DEFAULT_PATH )
# define cppunit
cet_find_library( CPPUNIT NAMES cppunit   PATHS ENV CPPUNIT_LIB   NO_DEFAULT_PATH )

#ifdhc
cet_find_library( IFDH NAMES ifdh PATHS $ENV{IFDHC_LIB} NO_DEFAULT_PATH )
cet_find_library( IFBEAM NAMES ifbeam PATHS $ENV{IFBEAM_LIB} NO_DEFAULT_PATH )
cet_find_library( NUCONDB NAMES nucondb PATHS $ENV{NUCONDB_LIB} NO_DEFAULT_PATH )

# SQLite
cet_find_library(SQLITE3 NAMES sqlite3 PATHS ENV SQLITE_LIB NO_DEFAULT_PATH)

cet_find_library(ARTFRAMEWORKCORE NAMES art_Framework_Core PATHS $ENV{ART_LIB} NO_DEFAULT_PATH) 
cet_find_library(ARTUTILITIES NAMES art_Utilities PATHS $ENV{ART_LIB} NO_DEFAULT_PATH) 
cet_find_library(MF_MESSAGELOGGER NAMES MF_MessageLogger PATHS $ENV{MESSAGEFACILITY_LIB} NO_DEFAULT_PATH) 
cet_find_library(MF_UTILITIES NAME MF_Utilities PATHS $ENV{MESSAGEFACILITY_LIB} NO_DEFAULT_PATH) 
cet_find_library(CETLIBX NAME cetlib PATHS $ENV{CETLIB_LIB} NO_DEFAULT_PATH)
cet_find_library(FHICLCPP NAME fhiclcpp PATHS $ENV{FHICLCPP_LIB} NO_DEFAULT_PATH)

# macros for art_dictionary and simple_plugin
include(ArtDictionary)
include(BuildPlugins)


# packaging utility
include(UseCPack)
# source
subdirs (IFDHService)
subdirs (IFBeamService)
subdirs (nucondbService)
subdirs (IFFileTransfer)
subdirs (IFCatalogInterface)
subdirs (bin)

