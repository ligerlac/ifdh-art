#ifndef CONDITIONSDATASERVICE_H
#define CONDITIONSDATASERVICE_H

#include "larcore/CoreUtils/ServiceProviderWrappers.h"
#include "ifdh_art/ConditionsDataService/Providers/ConditionsData.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"

using ConditionsDataService = lar::SimpleServiceProviderWrapper<ConditionsData>;

DECLARE_ART_SERVICE(ConditionsDataService, LEGACY)

#endif
