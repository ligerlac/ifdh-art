simple_plugin(nucondb "service" 
  NUCONDB
  wda::wda
  ifdh::ifdh
  art::Utilities
  messagefacility::MF_MessageLogger
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  BASENAME_ONLY
  )

install_ifdh_headers()
install_source()
