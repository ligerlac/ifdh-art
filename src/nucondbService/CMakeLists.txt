
include($ENV{ART_DIR}/Modules/BuildPlugins.cmake)

include_directories($ENV{IFDHC_DIR}/nucondb)
include_directories($ENV{IFDHC_DIR}/util)

simple_plugin(nucondb "service" 
	$ENV{IFDHC_DIR}/nucondb/libnucondb.so
        -L$ENV{ART_FQ_DIR}/lib
        )

install_headers()
install_source()

