cet_build_plugin(ConditionsDataService art::service
  IMPL_SOURCE
  LIBRARIES INTERFACE
  larcore::ServiceProviderWrappers
  BASENAME_ONLY
  )

# install_fhicl()
install_headers()

