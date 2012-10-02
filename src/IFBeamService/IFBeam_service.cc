#include "IFBeamService.h"

namespace ifbeam_ns {

IFBeam::IFBeam( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {
     ;
}
        
std::auto_ptr<BeamFolder>
IFBeam::getBeamFolder(std::string bundle_name, std::string url, double time_width) {
    std::auto_ptr<BeamFolder> res(new BeamFolder(bundle_name, url, time_width));
    return res;
}
}

DEFINE_ART_SERVICE(ifbeam_ns::IFBeam);
