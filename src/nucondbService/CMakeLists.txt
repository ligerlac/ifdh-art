

simple_plugin(nucondb "service" 
			   ${NUCONDB} 
                           ${WDA}
                           ${IFDH}
			   ${ART_UTILITIES}
                           messagefacility::MF_MessageLogger
			   ${FHICLCPP}
                           ${CETLIB}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
        )

install_ifdh_headers()
install_source()

