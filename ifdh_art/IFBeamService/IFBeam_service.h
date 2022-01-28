#ifndef ifdh_art_IFBeamService_IFBeam_service_h
#define ifdh_art_IFBeamService_IFBeam_service_h
#include "ifbeam.h"
#include <memory>

#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "fhiclcpp/ParameterSet.h"

namespace ifbeam_ns {

  class IFBeam {

  public:
    std::unique_ptr<BeamFolder> getBeamFolder(std::string bundle_name,
                                              std::string url = "",
                                              double time_width = 1200.0);

    // ART constructor...
    IFBeam(fhicl::ParameterSet const& cfg, art::ActivityRegistry& r);
  };

}

DECLARE_ART_SERVICE(ifbeam_ns::IFBeam, LEGACY)
// this is redundant, given the ifbeam include,  but just to be clear

using namespace ifbeam_ns;
#endif /* ifdh_art_IFBeamService_IFBeam_service_h */

// Local Variables:
// mode: c++
// End:
