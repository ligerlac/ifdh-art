cet_make_library(LIBRARY_NAME ConditionsData INTERFACE
  SOURCE ConditionsData.h
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

