cet_build_plugin(ConditionsData art::service
  IMPL_SOURCE
  LIBRARIES INTERFACE
  messagefacility::MF_MessageLogger
  art::Utilities
  fhiclcpp::fhiclcpp
  cetlib::cetlib
#  nopayloadclient
#  dunenpc
  BASENAME_ONLY
  )

install_headers()
install_source()

