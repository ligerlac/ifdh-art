
simple_plugin(IFCatalogInterface "service" 
			   ${IFDH} 
                           ${ARTFRAMEWORKCORE}
                           ${ARTUTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
                           ${CETLIB}
			   ${FHICLCPP}
		)
include_directories(../IFDHService)

install_headers()
install_source()

