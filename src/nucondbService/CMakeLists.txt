
include($ENV{ART_FQ_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/nucondb)
include_directories($ENV{IFDHC_DIR}/util)

simple_plugin(nucondb "service" $ENV{IFDHC_DIR}/nucondb/nucondb.a )

install_headers()
install_source()

