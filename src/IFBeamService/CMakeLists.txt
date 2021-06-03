


simple_plugin(IFBeam "service" 
			   ${IFBEAM} 
                           ${WDA}
                           ${IFDH}
                           messagefacility::MF_MessageLogger
			   ${ART_UTILITIES}
			   ${FHICLCPP}
                           ${CETLIB}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
         )

install_ifdh_headers()
install_source()

