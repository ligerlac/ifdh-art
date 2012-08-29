
set( IFDHService_sources IFDHService.cc )

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{FHICLCPP_INC} $ENV{CETLIB_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC})
include_directories( $ENV{LIBSIGCPP_INC}/sigc++-2.0 $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include)

# This example builds both static and shared libraries
add_library(IFDHService   SHARED ${IFDHService_sources} )
# the resulting libraries have the same base name
set_target_properties( IFDHService PROPERTIES OUTPUT_NAME IFDHService )
target_link_libraries( IFDHService $ENV{IFDHC_DIR}/ifdh/ifdh.a )

install ( TARGETS IFDHService DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

