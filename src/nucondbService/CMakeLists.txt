

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${WDA}
                           ${IFDH}
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIBX}
        )

install_headers()
install_source()

