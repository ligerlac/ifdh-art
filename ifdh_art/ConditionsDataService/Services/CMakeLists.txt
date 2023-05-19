cet_build_plugin(ConditionsDataService art::service INTERFACE
  IMPL_SOURCE
  LIBRARIES INTERFACE
  larcore::ServiceProviderWrappers
  BASENAME_ONLY
  nopayloadclient
#  dunenpc
  )

# install_fhicl()
install_headers()

