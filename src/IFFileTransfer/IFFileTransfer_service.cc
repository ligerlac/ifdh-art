
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art/Framework/Services/Interfaces/FileTransferStatus.h"
#include "IFFileTransfer_service.h"


namespace ifdh_ns {

IFFileTransfer::IFFileTransfer(const fhicl::ParameterSet&, art::ActivityRegistry& ) {
   ;
}
IFFileTransfer::~IFFileTransfer() throw () {
  ; 
}

int 
IFFileTransfer::doTranslateToLocalFilename( std::string const & uri, std::string & fileFQname) {
    fileFQname = _ifdh_handle->fetchInput(uri);
    mf::LogVerbatim("test") << "IFFileTransfer: copied " << uri << " to " << fileFQname << "\n";
    return art::FileTransferStatus::CREATED;
}

}

//DEFINE_ART_SERVICE(ifdh_ns::IFFileTransfer);
DEFINE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFFileTransfer, art::FileTransfer);
