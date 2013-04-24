
include($ENV{ART_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{ART_DIR}/include)
include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{IFDHC_DIR}/util)
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" 
                    -L$ENV{ART_FQ_DIR}/lib
           )

install_headers()
install_source()

