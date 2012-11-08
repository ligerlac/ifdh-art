#include "IFCatalogInterface_service.h"
#include "art/Framework/Services/Interfaces/FileDeliveryStatus.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

namespace ifdh_ns {

IFCatalogInterface::IFCatalogInterface(const fhicl::ParameterSet &cfg, art::ActivityRegistry& ar ) : 
    _process_id(""), 
    _proj_uri(""),
    _project_name(""), 
    _sam_station(""), 
    _last_file_uri("")
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
    mf::LogVerbatim("test") << "IFCatalogInterface destructor:";
    if( _last_file_uri.length() ) {
        mf::LogVerbatim("test") << "IFCatalogInterface: updating file status in destructor";
        // XXX should this be  art::FileDisposition::SKIPPED ???
        // shouldn't we have updated the status already?
        doUpdateStatus(_last_file_uri, art::FileDisposition::CONSUMED);
    }
    if( _proj_uri.length()) {
       _ifdh_handle->setStatus(_proj_uri, _process_id, "completed");
    }
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
    mf::LogVerbatim("test") << "IFCatalogInterface entering doGetNextFile\n";
    if ( _last_file_uri.length() ) {
        mf::LogVerbatim("test") << "Updating status in doGetNextFile\n";
        // XXX should this be  art::FileDisposition::SKIPPED ???
        // shouldn't we have updated the status already?
        doUpdateStatus(_last_file_uri, art::FileDisposition::CONSUMED);
    }
    if ( _proj_uri.length())  {
	uri = _ifdh_handle->getNextFile(_proj_uri,_process_id);
        _last_file_uri = uri;
	if (uri.length()) {
            mf::LogVerbatim("test") << "doGetNextFile success\n";
	    return art::FileDeliveryStatus::SUCCESS;
	} else {
            mf::LogVerbatim("test") << "doGetNextFile no_more_files\n";
	    return art::FileDeliveryStatus::NO_MORE_FILES;
        }
    }
    return art::FileDeliveryStatus::BAD_REQUEST;
}

void 
IFCatalogInterface::doUpdateStatus(std::string const & uri, art::FileDisposition status) {
    static const char *statusmap[] = {
	"transferred",
	"consumed",
	"skipped",
    };

    mf::LogVerbatim("test") << "IFCatalogInterface doUpdateStatus " << uri << "status:" << int(status) << "\n";

    if( _proj_uri.length()) {
        _ifdh_handle->updateFileStatus(_proj_uri,_process_id,uri,statusmap[int(status)]);
        if (status != art::FileDisposition::TRANSFERRED) {
           int res = unlink(_ifdh_handle->localPath(_last_file_uri).c_str());
           mf::LogVerbatim("test")  << "unlink of file returns:" << res  << "\n";
           _last_file_uri = "";
        }
    }
}

void 
IFCatalogInterface::doOutputFileOpened(std::string const & module_label) {
   mf::LogVerbatim("test")  << "IFCatalogInteface doOutputFileOpened: " << module_label << "\n";
   ;
}

void 
IFCatalogInterface::doOutputModuleInitiated(std::string const & module_label,
			       fhicl::ParameterSet const & pset) {
   mf::LogVerbatim("test")  << "IFCatalogInteface doOutputModuleInitiated: " << module_label << "\n";
   ;
}

void 
IFCatalogInterface::doOutputFileClosed(std::string const & module_label,
			  std::string const & fileFQname) {
   mf::LogVerbatim("test")  << "IFCatalogInteface doOutputFileClosed: " << module_label << ", " << fileFQname << "\n";
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
