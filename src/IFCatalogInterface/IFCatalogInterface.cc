#include "IFCatalogInterface.h"

namespace ifdh {

IFCatalogInterface::IFCatalogInterface(const fhicl::ParameterSet&, art::ActivityRegistry& ) { 
   ; 
}
IFCatalogInterface::~IFCatalogInterface() { 
   _ifdh_handle->setStatus(_proj_uri, _process_id, "ok");
}

void 
IFCatalogInterface::doConfigure(std::vector<std::string> const & item) {
    _process_id = item[0];  /* is this right??? */
    _project_name = item[1];
    _sam_station =  item[2];
    _proj_uri = _ifdh_handle->findProject(_project_name, _sam_station);
}

int  
IFCatalogInterface::doGetNextFileURI(std::string & uri, double & waitTime) {
    uri = _ifdh_handle->getNextFile(_proj_uri,_process_id);
    if (uri.length()) {
        return 1;
    } else {
        return 0;
    }
}

void 
IFCatalogInterface::doUpdateStatus(std::string const & uri, art::FileDisposition status) {
   _ifdh_handle->updateFileStatus(_proj_uri,_process_id,uri,(int)status?"ok":"bad");
}

void 
IFCatalogInterface::doOutputFileOpened(std::string const & module_label) {
   ;
}

void 
IFCatalogInterface::doOutputModuleInitiated(std::string const & module_label,
			       fhicl::ParameterSet const & pset) {
   ;
}

void 
IFCatalogInterface::doOutputFileClosed(std::string const & module_label,
			  std::string const & fileFQname) {
    _ifdh_handle->addOutputFile(fileFQname);
}

void 
IFCatalogInterface::doEventSelected(std::string const & module_label,
		       art::EventID const & event_id,
		       art::HLTGlobalStatus const & acceptance_info) {
    ;
}

bool
IFCatalogInterface::doIsSearchable() {
   return 0;
}

void
IFCatalogInterface::doRewind() {
   // throw NotImplemented;
   ;
}

}
