
simple_plugin(IFCatalogInterface "service" 
			   ${IFDH} 
                           ${ART_FRAMEWORK_CORE}
                           ${ART_UTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB}
                           ${ROOT_BASIC_LIB_LIST}
              BASENAME_ONLY
		)
include_directories(../IFDHService)

install_ifdh_headers()
install_source()

