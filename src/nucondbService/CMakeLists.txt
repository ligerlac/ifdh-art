

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${WDA}
                           ${IFDHC}
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIBX}
        )

install_headers()
install_source()

