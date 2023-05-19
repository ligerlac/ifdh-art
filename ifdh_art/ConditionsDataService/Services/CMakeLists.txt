cet_build_plugin(ConditionsDataService art::service
  IMPL_SOURCE
  LIBRARIES INTERFACE
  ifdh_art::ConditionsData
  larcore::ServiceProviderWrappers
)

install_fhicl()
install_headers()
