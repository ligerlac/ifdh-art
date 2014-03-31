


simple_plugin(IFBeam "service" 
			   ${IFBEAM} 
                           ${WDA}
                           ${IFDH}
                           ${MF_MESSAGELOGGER}
			   ${FHICLCPP}
                           ${CETLIB}
              BASENAME_ONLY
         )

install_ifdh_headers()
install_source()

