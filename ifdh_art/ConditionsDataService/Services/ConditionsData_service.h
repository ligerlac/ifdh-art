#ifndef CONDITIONSDATASERVICE_H
#define CONDITIONSDATASERVICE_H
#include <memory>

#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Name.h"
#include "fhiclcpp/types/Comment.h"

#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"

#include "ifdh_art/ConditionsDataService/Providers/ConditionsData.h"


DECLARE_ART_SERVICE(ConditionsData, LEGACY)

#endif
