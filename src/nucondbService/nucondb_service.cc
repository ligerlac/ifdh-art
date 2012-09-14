#include "nucondbService.h"

namespace nucondb_ns {


// ART constructor...
nucondbService::nucondbService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {}

std::auto_ptr<Folder> 
nucondbService::getFolder(std::string name, std::string url, std:: string tag ) { 
   std::auto_ptr<Folder> res(new Folder(name, url, tag));
   return res;
}

}
#ifdef DEFINE_ART_SERVICE
DEFINE_ART_SERVICE(nucondb_ns::nucondbService);
#endif
