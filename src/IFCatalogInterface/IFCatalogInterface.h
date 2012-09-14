#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"

#include "CatalogInterface.h"
#include "IFDHService.h"

namespace ifdh_ns {

class IFCatalogInterface : public art::CatalogInterface {

public:
  IFCatalogInterface(const fhicl::ParameterSet&, art::ActivityRegistry& );
  ~IFCatalogInterface();
private:
  art::ServiceHandle<IFDH> _ifdh_handle;
  std::string _process_id;
  std::string _proj_uri;
  std::string _project_name;
  std::string _sam_station;

  virtual void doConfigure(std::vector<std::string> const & item);
  virtual int  doGetNextFileURI(std::string & uri, double & waitTime);
  virtual void doUpdateStatus(std::string const & uri, art::FileDisposition status);
  virtual void doOutputFileOpened(std::string const & module_label);
  virtual void doOutputModuleInitiated(std::string const & module_label,
                                       fhicl::ParameterSet const & pset);
  virtual void doOutputFileClosed(std::string const & module_label,
                                  std::string const & fileFQname);
  virtual void doEventSelected(std::string const & module_label,
                               art::EventID const & event_id,
                               art::HLTGlobalStatus const & acceptance_info);
  virtual bool doIsSearchable();
  virtual void doRewind();
};

}
