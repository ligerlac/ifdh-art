
include($ENV{ART_FQ_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{IFDHC_DIR}/util)
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" )

install_headers()
install_source()

