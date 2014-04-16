

simple_plugin(IFDH service 
			   ${IFDH} 
                           ${MF_MESSAGELOGGER}
                           ${MF_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB}
              BASENAME_ONLY
             )

install_ifdh_headers()
install_source()

