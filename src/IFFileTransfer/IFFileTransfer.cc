
#include "IFFileTransfer.h"

namespace ifdh {

IFFileTransfer::IFFileTransfer(const fhicl::ParameterSet&, art::ActivityRegistry& ) {
   ;
}
IFFileTransfer::~IFFileTransfer() {
  ; 
}

virtual int 
IFFileTransfer::doTranslateToLocalFilename( std::string const & uri, std::string & fileFQname) {
   fileFQname = _ifdh_handle->fetchInput(uri);
}

}
