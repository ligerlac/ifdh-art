
include($ENV{ART_DIR}/Modules/BuildPlugins.cmake)


include_directories($ENV{ART_DIR}/include)
include_directories($ENV{IFDHC_DIR}/ifbeam)
include_directories($ENV{IFDHC_DIR}/util)

simple_plugin(IFBeam "service" 
         $ENV{IFDHC_FQ_DIR}/lib/libifbeam.so
         -L$ENV{ART_FQ_DIR}/lib
         )

install_headers()
install_source()

