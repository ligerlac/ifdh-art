#include "ifdh.h"

// ART bits...
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "cetlib/exception.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"

namespace ifdh_ns {

class IFDH : public ifdh {
public:
       
        // ART constructor...
        IFDH( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);

};

}

using namespace ifdh_ns;
