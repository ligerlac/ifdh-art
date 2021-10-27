
simple_plugin(IFCatalogInterface "service" 
  ifdh::ifdh
  art::Framework_Core
  art::Utilities
  messagefacility::MF_MessageLogger
  fhiclcpp::fhiclcpp
  cetlib::cetlib
  cetlib_except::cetlib_except
  BASENAME_ONLY
	)

install_headers()
install_source()

