#include "nucondb_service.h"

namespace nucondb_ns {


// ART constructor...
nucondbService::nucondbService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {}

std::unique_ptr<Folder> 
nucondbService::getFolder(std::string name, std::string url, std:: string tag ) { 
   std::unique_ptr<Folder> res(new Folder(name, url, tag));
   return res;
}

}

//DEFINE_ART_SERVICE(nucondb_ns::nucondbService)
DECLARE_ART_SERVICE_INTERFACE(nucondb_ns::nucondbService,LEGACY)
