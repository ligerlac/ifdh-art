#ifndef ifdh_art_NUconDBService_NUconDB_service_h
#define ifdh_art_NUconDBService_NUconDB_service_h

#include "nucondb.h"

#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "fhiclcpp/fwd.h"

#include <memory>
#include <string>

namespace nucondb_ns {

  class NUconDBService {
  public:
    explicit NUconDBService(fhicl::ParameterSet const& cfg);
    std::unique_ptr<Folder> getFolder(std::string name,
                                      std::string url,
                                      std::string tag = "");
  };

}

DECLARE_ART_SERVICE(nucondb_ns::NUconDBService, LEGACY)

#endif /* ifdh_art_NUconDBService_NUconDB_service_h */

// Local Variables:
// mode: c++
// End:
