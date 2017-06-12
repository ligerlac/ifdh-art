

simple_plugin(IFDH service 
			   ${IFDH} 
			   ${ART_UTILITIES}
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB} ${CETLIB_EXCEPT}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
             )

install_ifdh_headers()
install_source()

