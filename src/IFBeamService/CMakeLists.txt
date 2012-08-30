
include($ENV{ART_FQ_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/ifbeam)

include_directories($ENV{IFDHC_DIR}/ifdh)

simple_plugin(IFBeam "service" 
         $ENV{IFDHC_DIR}/ifbeam/libifbeam.a 
         )


#include_directories($ENV{FHICLCPP_INC} $ENV{CETLIB_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC} $ENV{CPP0X_INC} $ENV{BOOST_INC} $ENV{ART_INC} $ENV{MESSAGEFACILITY_INC})
#include_directories( $ENV{LIBSIGCPP_INC}/sigc++-2.0 $ENV{LIBSIGCPP_LIB}/sigc++-2.0/include)


# This example builds both static and shared libraries
#add_library(IFBeamService   SHARED ${IFBeamService_sources} )
# the resulting libraries have the same base name
#set_target_properties( IFBeamService PROPERTIES OUTPUT_NAME IFBeamService )
#install ( TARGETS IFBeamService DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

