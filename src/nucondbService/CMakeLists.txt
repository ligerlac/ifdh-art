

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIBX}
        )

install_headers()
install_source()

