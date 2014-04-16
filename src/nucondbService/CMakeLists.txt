

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${WDA}
                           ${IFDH}
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIB}
              BASENAME_ONLY
        )

install_ifdh_headers()
install_source()

