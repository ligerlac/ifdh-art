
include($ENV{ART_DIR}/Modules/BuildPlugins.cmake)
include_directories($ENV{IFDHC_DIR}/ifdh)

simple_plugin(IFCatalogInterface "service" 
                    -L$ENV{ART_FQ_DIR}/lib
                    -L../IFDHService
		)

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{IFDHC_DIR}/util)
include_directories(../IFDHService)

install_headers()
install_source()

