#ifndef CONDITIONSDATASERVICE_H
#define CONDITIONSDATASERVICE_H
#include <memory>

#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
//#include <nopayloadclient/nopayloadclient.hpp>


class ConditionsData  {
       
 public:
  // ART constructor...
  ConditionsData( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);
  void sayHello();
  void printDBSize();
  std::string getUrl(int run_number, const std::string& type);
};


DECLARE_ART_SERVICE(ConditionsData, LEGACY)

#endif
