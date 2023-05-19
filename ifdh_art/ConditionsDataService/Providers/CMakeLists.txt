cet_make_library(LIBRARY_NAME ConditionsData INTERFACE
  SOURCE ConditionsData.h
  LIBRARIES INTERFACE
  messagefacility::MF_MessageLogger
  fhiclcpp::types
  nopayloadclient
#  dunenpc
  )

message(STATUS "from Providers: npc_lib: [${npc_lib}]") 

install_headers()
install_source()

