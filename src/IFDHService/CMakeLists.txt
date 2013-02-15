
include($ENV{ART_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/ifdh)
include_directories($ENV{IFDHC_DIR}/util)

simple_plugin(IFDH "service" 
                     $ENV{IFDHC_FQ_DIR}/lib/libifdh.so
                    -L$ENV{ART_FQ_DIR}/lib
             )

install_headers()
install_source()

