simple_plugin(IFBeam "service"
  IFBEAM
  wda::wda
  ifdh::ifdh
  messagefacility::MF_MessageLogger
  art::Utilities
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  BASENAME_ONLY
  )

install_ifdh_headers()
install_source()
