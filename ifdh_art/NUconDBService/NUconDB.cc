#include "NUconDB_service.h"

namespace nucondb_ns {

  // ART constructor...
  NUconDBService::NUconDBService(__attribute__((unused))
                                 fhicl::ParameterSet const& cfg,
                                 __attribute__((unused))
                                 art::ActivityRegistry& r)
  {}

  std::unique_ptr<Folder>
  NUconDBService::getFolder(std::string name, std::string url, std::string tag)
  {
    std::unique_ptr<Folder> res(new Folder(name, url, tag));
    return res;
  }

}
