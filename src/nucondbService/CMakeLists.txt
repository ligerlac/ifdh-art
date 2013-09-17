

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIB}
        )

install_headers()
install_source()

