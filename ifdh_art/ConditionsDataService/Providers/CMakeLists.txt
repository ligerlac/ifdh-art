cet_make_library(LIBRARY_NAME ConditionsData INTERFACE
  SOURCE ConditionsData.h
  LIBRARIES INTERFACE
  fhiclcpp::types
  )

install_fhicl()
install_headers()
