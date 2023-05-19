cet_build_plugin(ConditionsData art::service
  LIBRARIES
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

