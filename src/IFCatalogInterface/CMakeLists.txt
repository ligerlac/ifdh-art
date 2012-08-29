
set( IFCatalogService_sources IFCatalogService.cc )

include_directories($ENV{IFDHC_DIR}/ifbeam)


# This example builds both static and shared libraries
add_library(IFCatalogService   SHARED ${IFCatalogService_sources} )
# the resulting libraries have the same base name
set_target_properties( IFCatalogService PROPERTIES OUTPUT_NAME IFCatalogService )
target_link_libraries( IFCatalogService $ENV{IFDHC_DIR}/ifbeam/libifbeam.a )

install ( TARGETS IFCatalogService DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

