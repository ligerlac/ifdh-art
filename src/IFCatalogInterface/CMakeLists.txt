
include_directories($ENV{IFDHC_DIR}/ifdh)

simple_plugin(IFCatalogInterface "service" )

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{IFDHC_DIR}/util)
include_directories(../IFDHService)

install_headers()
install_source()

