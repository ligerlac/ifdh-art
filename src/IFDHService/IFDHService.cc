#include "IFDHService.h"

namespace ifdh_ns {

// ART Service constructor -- currently does nothing.
//
//
IFDHService::IFDHService( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {
  ;
}

}

#ifdef DEFINE_ART_SERVICE
DEFINE_ART_SERVICE(ifdh_ns::IFDHService);
#endif
