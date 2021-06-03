
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" 
			   ${IFDH} 
                           ${ART_FRAMEWORK_CORE}
                           ${ART_UTILITIES}
                           messagefacility::MF_MessageLogger
                           messagefacility::headers
			   ${FHICLCPP}
                           ${CETLIB} ${CETLIB_EXCEPT}
                           ${ROOT_LIBRARIES}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
           )

install_ifdh_headers()
install_source()

