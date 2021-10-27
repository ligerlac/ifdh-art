
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

include_directories(../IFDHService) ### MIGRATE-ACTION-RECOMMENDED: use target_link_directories() with target semantics

install_ifdh_headers()
install_source()

