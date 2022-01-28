#include "IFBeam_service.h"

namespace ifbeam_ns {

  IFBeam::IFBeam(fhicl::ParameterSet const&) {}

  std::unique_ptr<BeamFolder>
  IFBeam::getBeamFolder(std::string bundle_name,
                        std::string url,
                        double time_width)
  {
    return std::make_unique<BeamFolder>(bundle_name, url, time_width);
  }
}
