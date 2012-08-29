#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"

#include "FileTransfer.h"

namespace ifdh {

class IFFileTransfer : public art::FileTransfer {
public:
  IFFileTransfer(const fhicl::ParameterSet&, art::ActivityRegistry& );
  ~IFFileTransfer();
private:
  art::ServiceHandle<IFDHService> ifdh_handle;
  virtual int doTranslateToLocalFilename(std::string const & uri,
                             std::string & fileFQname);
};

}
