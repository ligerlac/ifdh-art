
simple_plugin(IFCatalogInterface "service" 
  IFDH
  ART_FRAMEWORK_CORE
  ART_UTILITIES
  MF_MESSAGELOGGER
  FHICLCPP
  CETLIB CETLIB_EXCEPT
  BASENAME_ONLY
	)

include_directories(../IFDHService)

install_ifdh_headers()
install_source()

