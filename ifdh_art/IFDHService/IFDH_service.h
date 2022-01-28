#ifndef ifdh_art_IFDHService_IFDH_service_h
#define ifdh_art_IFDHService_IFDH_service_h
#include "ifdh.h"

// art bits...
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "fhiclcpp/ParameterSet.h"

namespace ifdh_ns {

  class IFDH : public ifdh {
  public:
    // art constructor...
    IFDH(fhicl::ParameterSet const& cfg);
  };

}

DECLARE_ART_SERVICE(ifdh_ns::IFDH, SHARED)

#endif /* ifdh_art_IFDHService_IFDH_service_h */

// Local Variables:
// mode: c++
// End:
