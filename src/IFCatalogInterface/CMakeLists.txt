
set( IFCatalogInterface_sources IFCatalogInterface.cc )

include_directories($ENV{IFDHC_DIR}/ifbeam)

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories(../IFDHService)
include_directories($ENV{FHICLCPP_INC} $ENV{CETLIB_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC})
include_directories( $ENV{LIBSIGCPP_INC}/sigc++-2.0 $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include)


# This example builds both static and shared libraries
add_library(IFCatalogInterface   SHARED ${IFCatalogInterface_sources} )
# the resulting libraries have the same base name
set_target_properties( IFCatalogInterface PROPERTIES OUTPUT_NAME IFCatalogInterface )
install ( TARGETS IFCatalogInterface DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

