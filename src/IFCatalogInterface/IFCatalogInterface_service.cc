#include "IFCatalogInterface_service.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

namespace ifdh_ns {

IFCatalogInterface::IFCatalogInterface(const fhicl::ParameterSet &cfg, art::ActivityRegistry& ar ) : 
    _process_id(""), 
    _project_name(""), 
    _sam_station(""), 
    _proj_uri("") 
{ 
    std::vector<std::string> cfgkeys = cfg.get_keys();
    std::string s;

    mf::LogVerbatim("test") << "IFCatalogInterface constructor, got keys:";
    for (std::vector<std::string>::iterator p = cfgkeys.begin(); p != cfgkeys.end(
  ); p++ ) {
	 mf::LogVerbatim("test")<< *p << ", ";
    }

    if ( cfg.get_if_present("webURI", s) ) {
	mf::LogVerbatim("test") << "IFCatalogInterface: setting _proj_uri to:" << s << "\n";
	_proj_uri = s;
    }
}

IFCatalogInterface::~IFCatalogInterface() throw () { 
   if( _proj_uri.length())  
       _ifdh_handle->setStatus(_proj_uri, _process_id, "ok");
}

void 
IFCatalogInterface::doConfigure(std::vector<std::string> const & item) {
    if (item.size() ) {
        _process_id = item[0]; 
       mf::LogVerbatim("test") << "IFCatalogInterface doConfigure, got id:" << item[0];
    }
}

int  
IFCatalogInterface::doGetNextFileURI(std::string & uri, double & waitTime) {
    if( _proj_uri.length())  {
	uri = _ifdh_handle->getNextFile(_proj_uri,_process_id);
	if (uri.length()) {
	    return 1;
	}
    }
    return 0;
}

void 
IFCatalogInterface::doUpdateStatus(std::string const & uri, art::FileDisposition status) {
   if( _proj_uri.length()) {
       _ifdh_handle->updateFileStatus(_proj_uri,_process_id,uri,(status==art::FileDisposition::CONSUMED)?"ok":"bad");
   }
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

//DEFINE_ART_SERVICE(ifdh_ns::IFCatalogInterface);
DEFINE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFCatalogInterface, art::CatalogInterface)
