
set( IFBeamService_sources IFBeamService.cc )

include_directories($ENV{IFDHC_DIR}/ifbeam)


# This example builds both static and shared libraries
add_library(IFBeamService   SHARED ${IFBeamService_sources} )
# the resulting libraries have the same base name
set_target_properties( IFBeamService PROPERTIES OUTPUT_NAME IFBeamService )
target_link_libraries( IFBeamService $ENV{IFDHC_DIR}/ifbeam/libifbeam.a )

install ( TARGETS IFBeamService DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

