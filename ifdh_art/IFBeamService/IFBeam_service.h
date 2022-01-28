#ifndef ifdh_art_IFBeamService_IFBeam_service_h
#define ifdh_art_IFBeamService_IFBeam_service_h

#include "ifbeam.h"

#include <memory>
#include <string>

#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "fhiclcpp/fwd.h"

namespace ifbeam_ns {

  class IFBeam {
  public:
    explicit IFBeam(fhicl::ParameterSet const&);

    std::unique_ptr<BeamFolder> getBeamFolder(std::string bundle_name,
                                              std::string url = "",
                                              double time_width = 1200.0);
  };

}

DECLARE_ART_SERVICE(ifbeam_ns::IFBeam, LEGACY)

#endif /* ifdh_art_IFBeamService_IFBeam_service_h */

// Local Variables:
// mode: c++
// End:
