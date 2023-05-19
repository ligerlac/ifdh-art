#ifndef CONDITIONSDATASERVICE_H
#define CONDITIONSDATASERVICE_H
#include <memory>

#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"


class ConditionsData  {
       
public:
    // ART constructor...
    ConditionsData( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);
    void sayHello() {
        std::cout << "ConditionsData::sayHello() (from header)" << std::endl;
    };
};


DECLARE_ART_SERVICE(ConditionsData, LEGACY)

#endif
