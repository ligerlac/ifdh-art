#ifndef ifdh_art_IFFileTransfer_IFFileTransfer_service_h
#define ifdh_art_IFFileTransfer_IFFileTransfer_service_h

#include "art/Framework/Services/FileServiceInterfaces/FileTransfer.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/fwd.h"

#include "ifdh_art/IFDHService/IFDH_service.h"

namespace ifdh_ns {

  class IFFileTransfer : public art::FileTransfer {
  public:
    IFFileTransfer(fhicl::ParameterSet const&);

  private:
    art::ServiceHandle<IFDH> _ifdh_handle;
    int doTranslateToLocalFilename(std::string const& uri,
                                   std::string& fileFQname) override;
  };

}

DECLARE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFFileTransfer,
                                   art::FileTransfer,
                                   SHARED)

#endif /* ifdh_art_IFFileTransfer_IFFileTransfer_service_h */

// Local Variables:
// mode: c++
// End:
