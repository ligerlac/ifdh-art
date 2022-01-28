#ifndef NUCONDBSERVICE_H
#define NUCONDBSERVICE_H
#include "nucondb.h"

// ART bits...
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "cetlib_except/exception.h"
#include "fhiclcpp/ParameterSet.h"

namespace nucondb_ns {

  class NUconDBService {

  public:
    // ART constructor...
    NUconDBService(fhicl::ParameterSet const& cfg, art::ActivityRegistry& r);
    std::unique_ptr<Folder> getFolder(std::string name,
                                      std::string url,
                                      std::string tag = "");
  };

}

DECLARE_ART_SERVICE(nucondb_ns::NUconDBService, LEGACY)

// this is redundant, given the include,  but just to be clear

using namespace nucondb_ns;
#endif // NUCONDBSERVICE_H
