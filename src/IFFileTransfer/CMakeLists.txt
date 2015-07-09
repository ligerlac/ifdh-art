
include_directories(../IFDHService)

simple_plugin(IFFileTransfer "service" 
			   ${IFDH} 
                           ${ART_FRAMEWORK_CORE}
                           ${ART_UTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB}
                           ${ROOT_BASIC_LIB_LIST}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
           )

install_ifdh_headers()
install_source()

