#include "IFBeamService.h"

namespace ifbeam_ns {

IFBeamService::IFBeamService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {
     ;
}
        
std::auto_ptr<BeamFolder>
IFBeamService::getBeamFolder(std::string bundle_name, std::string url, double time_width) {
    std::auto_ptr<BeamFolder> res(new BeamFolder(bundle_name, url, time_width));
    return res;
}
}

#ifdef DEFINE_ART_SERVICE
DEFINE_ART_SERVICE(ifbeam_ns::IFBeamService);
#endif
