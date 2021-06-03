

simple_plugin(IFDH service 
			   ${IFDH} 
			   ${ART_UTILITIES}
                           messagefacility::MF_MessageLogger
                           messagefacility::headers
			   ${FHICLCPP}
                           ${CETLIB} ${CETLIB_EXCEPT}
                           ${Boost_FILESYSTEM_LIBRARY}
                           ${Boost_SYSTEM_LIBRARY}
              BASENAME_ONLY
             )

install_ifdh_headers()
install_source()

