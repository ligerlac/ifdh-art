#include "nucondb.h"

// ART bits...
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "cetlib/exception.h"

namespace nucondb_ns {

class nucondbService  {
       
public:
        // ART constructor...
        nucondbService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r);
        std::auto_ptr<Folder> getFolder(std::string name, std::string url, std::string tag = "");
};

}

// this is redundant, given the include,  but just to be clear

using namespace nucondb_ns;
