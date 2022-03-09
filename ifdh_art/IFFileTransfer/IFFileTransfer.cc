#include "IFFileTransfer_service.h"
#include "art/Framework/Services/FileServiceInterfaces/FileTransferStatus.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

namespace ifdh_ns {

  IFFileTransfer::IFFileTransfer(fhicl::ParameterSet const&) {}

  int
  IFFileTransfer::doTranslateToLocalFilename(std::string const& uri,
                                             std::string& fileFQname)
  {
    mf::LogVerbatim("test")
      << "IFFileTransfer: entered for uri: " << uri << "\n";
    fileFQname = _ifdh_handle->fetchInput(uri);
    mf::LogVerbatim("test")
      << "IFFileTransfer: copied " << uri << " to " << fileFQname << "\n";
    return art::FileTransferStatus::SUCCESS;
  }

}
