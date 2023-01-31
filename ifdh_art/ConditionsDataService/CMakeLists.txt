cet_build_plugin(ConditionsData art::service
  LIBRARIES
  messagefacility::MF_MessageLogger
  art::Utilities
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  BASENAME_ONLY
  )

#cet_build_plugin(LinosModule art::module
#  LIBRARIES
#  messagefacility::MF_MessageLogger
#  art::Utilities
#  fhiclcpp::fhiclcpp
#  cetlib::cetlib
#  BASENAME_ONLY
#  )

install_headers()
install_source()
