
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" 
			   ${IFDH} 
                           ${ARTFRAMEWORKCORE}
                           ${ARTUTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
                           ${CETLIB}
			   ${FHICLCPP}
           )

install_headers()
install_source()

