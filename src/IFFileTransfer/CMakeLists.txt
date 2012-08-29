
set( IFFileTransferService_sources IFFileTransferService.cc )

include_directories($ENV{IFDHC_DIR}/ifbeam)


# This example builds both static and shared libraries
add_library(IFFileTransferService   SHARED ${IFFileTransferService_sources} )
# the resulting libraries have the same base name
set_target_properties( IFFileTransferService PROPERTIES OUTPUT_NAME IFFileTransferService )
target_link_libraries( IFFileTransferService $ENV{IFDHC_DIR}/ifbeam/libifbeam.a )

install ( TARGETS IFFileTransferService DESTINATION ${flavorqual_dir}/lib )

install_headers()
install_source()

