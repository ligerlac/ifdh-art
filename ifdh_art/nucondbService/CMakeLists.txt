cet_build_plugin(nucondb art::service
  LIBRARIES
  nucondb::nucondb
  wda::wda
  ifdh::ifdh
  art::Utilities
  messagefacility::MF_MessageLogger
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  BASENAME_ONLY
  )

install_headers()
install_source()
