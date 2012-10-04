
#include "IFFileTransfer.h"

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
}

}

//DEFINE_ART_SERVICE(ifdh_ns::IFFileTransfer);
DEFINE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFFileTransfer, art::FileTransfer);
