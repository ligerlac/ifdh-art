#include "ifbeam.h"
#include <memory>

#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

namespace ifbeam_ns {

class IFBeamService  {
       
public:
        
        std::auto_ptr<BeamFolder> getBeamFolder(std::string bundle_name, std::string url, double time_width);

        // ART constructor...
        IFBeamService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);
};

}

#ifdef DEFINE_ART_SERVICE
DEFINE_ART_SERVICE(ifbeam_ns::IFBeamService);
#endif

// this is redundant, given the ifbeam include,  but just to be clear

using namespace ifbeam_ns;
