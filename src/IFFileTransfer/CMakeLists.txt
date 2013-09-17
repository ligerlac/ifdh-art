
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" 
			   ${IFDH} 
                           ${ARTFRAMEWORKCORE}
                           ${ARTUTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIBX}
           )

install_headers()
install_source()

