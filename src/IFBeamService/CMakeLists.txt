
include($ENV{ART_FQ_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/ifbeam)
include_directories($ENV{IFDHC_DIR}/util)

simple_plugin(IFBeam "service" 
         $ENV{IFDHC_DIR}/ifbeam/libifbeam.a 
         )

install_headers()
install_source()

