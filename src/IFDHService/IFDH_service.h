#ifndef IFDHSERVICE_H
#define IFDHSERVICE_H
#include "ifdh.h"

// ART bits...
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ServicesManager.h"
#include "art/Framework/Services/Registry/detail/ServiceHelper.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "cetlib_except/exception.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"

namespace ifdh_ns {

class IFDH : public ifdh {
public:
       
        // ART constructor...
        IFDH( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);

};

}

DECLARE_ART_SERVICE(ifdh_ns::IFDH,LEGACY)
using namespace ifdh_ns;

#endif // IFDHSERVICE_H
