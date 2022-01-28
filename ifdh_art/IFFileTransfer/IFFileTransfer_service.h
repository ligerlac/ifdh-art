#ifndef ifdh_art_IFFileTransfer_IFFileTransfer_service_h
#define ifdh_art_IFFileTransfer_IFFileTransfer_service_h

#include "art/Framework/Services/FileServiceInterfaces/FileTransfer.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "art/Framework/Services/FileServiceInterfaces/FileTransfer.h"

#include "ifdh_art/IFDHService/IFDH_service.h"

namespace ifdh_ns {

  class IFFileTransfer : public art::FileTransfer {

  public:
    IFFileTransfer(const fhicl::ParameterSet&, art::ActivityRegistry&);

  private:
    art::ServiceHandle<IFDH> _ifdh_handle;
    virtual int doTranslateToLocalFilename(std::string const& uri,
                                           std::string& fileFQname);
  };

}
DECLARE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFFileTransfer,
                                   art::FileTransfer,
                                   SHARED)

#endif /* ifdh_art_IFFileTransfer_IFFileTransfer_service_h */

// Local Variables:
// mode: c++
// End:
