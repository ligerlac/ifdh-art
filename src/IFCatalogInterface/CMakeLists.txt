
simple_plugin(IFCatalogInterface "service" 
			   ${IFDH} 
                           ${ARTFRAMEWORKCORE}
                           ${ARTUTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB}
		)
include_directories(../IFDHService)

install_headers()
install_source()

