
simple_plugin(IFCatalogInterface "service" 
			   ${IFDH} 
                           ${ART_FRAMEWORK_CORE}
                           ${ART_UTILITIES}
                           messagefacility::MF_MessageLogger
                           messagefacility::headers
			   ${FHICLCPP}
                           ${CETLIB} ${CETLIB_EXCEPT}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
                           ${ROOT_LIBRARIES}
              BASENAME_ONLY
		)
include_directories(../IFDHService)

install_ifdh_headers()
install_source()

