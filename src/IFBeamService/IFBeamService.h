#include "ifbeam.h"
#include <memory>

#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

namespace ifbeam_ns {

class IFBeam  {
       
public:
        
        std::auto_ptr<BeamFolder> getBeamFolder(std::string bundle_name, std::string url, double time_width);

        // ART constructor...
        IFBeam( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);
};

}


// this is redundant, given the ifbeam include,  but just to be clear

using namespace ifbeam_ns;
