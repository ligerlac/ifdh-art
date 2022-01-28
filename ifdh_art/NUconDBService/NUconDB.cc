#include "NUconDB_service.h"

namespace nucondb_ns {

  NUconDBService::NUconDBService(fhicl::ParameterSet const&) {}

  std::unique_ptr<Folder>
  NUconDBService::getFolder(std::string name, std::string url, std::string tag)
  {
    return std::make_unique<Folder>(name, url, tag);
  }

}
