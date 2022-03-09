cet_build_plugin(IFBeam art::service
  LIBRARIES
  ifbeam::ifbeam
  wda::wda
  ifdh::ifdh
  messagefacility::MF_MessageLogger
  art::Utilities
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  BASENAME_ONLY
  )

install_headers()
install_source()
