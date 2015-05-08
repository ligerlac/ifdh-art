

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${WDA}
                           ${IFDH}
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIB}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
        )

install_ifdh_headers()
install_source()

