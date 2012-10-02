#ifndef IFFILETRANSFER_H
#define IFFILETRANSFER_H

#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ServiceMacros.h"

#include "FileTransfer.h"
#include "IFDHService.h"

namespace ifdh_ns {

class IFFileTransfer : public art::FileTransfer {

public:
  IFFileTransfer(const fhicl::ParameterSet&, art::ActivityRegistry& );
  ~IFFileTransfer();

private:
  art::ServiceHandle<IFDH> _ifdh_handle;
  virtual int doTranslateToLocalFilename(std::string const & uri,
                             std::string & fileFQname);
};

}
#endif //IFFILETRANSFER_H
