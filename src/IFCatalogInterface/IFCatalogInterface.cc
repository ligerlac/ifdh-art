
namespace ifdh {

IFCatalogInterface::IFCatalogInterface(const fhicl::ParameterSet&, art::ActivityRegistry& ) { 
   ; 
}
IFCatalogInterface::~IFCatalogInterface() { 
   _ifdh_handle->setStatus(_proj_uri, _process_id, "ok");
}

virtual void 
IFCatalogInterface::doConfigure(std::vector<std::string> const & item) {
    _process_id = item[0];  /* is this right??? */
    _project_name = item[1];
    _proj_uri = _ifdh_handle->findProject(_project_name);
}

virtual int  
IFCatalogInterface::doGetNextFileURI(std::string & uri, double & waitTime) {
    uri = _ifdh_handle->getNextFile(_proj_uri,_process_id);
    if (uri.length()) {
        return art::FileDeliveryStatus::ok
    } else {
        return art::FileDeliveryStatus::no_more_files;
    }
}

virtual void 
IFCatalogInterface::doUpdateStatus(std::string const & uri, FileDisposition status) {
   _ifdh_handle->updateStatus(_proj_uri,_process_id,uri,status);
}

virtual void 
IFCatalogInterface::doOutputFileOpened(std::string const & module_label) {
   ;
}

virtual void 
IFCatalogInterface::doOutputModuleInitiated(std::string const & module_label,
			       fhicl::ParameterSet const & pset) {
   ;
}

virtual void 
IFCatalogInterface::doOutputFileClosed(std::string const & module_label,
			  std::string const & fileFQname) {
    _ifdh_handle->addOutputFile(fileFQname);
}

virtual void 
IFCatalogInterface::doEventSelected(std::string const & module_label,
		       EventID const & event_id,
		       HLTGlobalStatus const & acceptance_info) {
    ;
}

virtual void 
IFCatalogInterface::doIsSearchable() {
   return 0;
}

virtual 
IFCatalogInterface::doRewind() {
   throw NotImplemented;
}

