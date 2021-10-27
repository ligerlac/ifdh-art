include_directories(../IFDHService) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics

simple_plugin(IFFileTransfer "service" 
  IFDH
  ART_FRAMEWORK_CORE
  ART_UTILITIES
  MF_MESSAGELOGGER
  FHICLCPP
  CETLIB
  CETLIB_EXCEPT
  BASENAME_ONLY
  )

install_ifdh_headers()
install_source()

