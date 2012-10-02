#include "IFDHService.h"

namespace ifdh_ns {

// ART Service constructor -- currently does nothing.
//
//
IFDH::IFDH( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {
  ;
}

}

DEFINE_ART_SERVICE(ifdh_ns::IFDH);
