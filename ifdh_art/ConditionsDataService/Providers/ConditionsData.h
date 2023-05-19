#include "ConditionsData_service.h"


ConditionsData::ConditionsData( __attribute__((unused)) fhicl::ParameterSet const & cfg, __attribute__((unused)) art::ActivityRegistry &r) {
     ;
}
        
void ConditionsData::sayHello() {
    std::cout << "ConditionsData::sayHello()" << std::endl;
}

void ConditionsData::printDBSize() {
    std::cout << "ConditionsData::printDBSize()" << std::endl;
}

std::string ConditionsData::getUrl(int run_number, const std::string& type) {
  std::cout << "ConditionsData::getUrl()" << std::endl;
  std::cout << "run_number = " << run_number << std::endl;
  std::cout << "type = " << type << std::endl;
  return "example_url";
}
