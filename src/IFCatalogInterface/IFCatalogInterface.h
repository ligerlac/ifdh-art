#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/ParameterSet.h"

#include "CatalogInterface.h"

namespace ifdh {

class IFCatalogInterface : public art::CatalogInterface {
public:
  IFCatalogInterface(const fhicl::ParameterSet&, art::ActivityRegistry& );
  ~IFCatalogInterface();
private:
  art::ServiceHandle<IFDHService> ifdh_handle;
  int process_id;

  virtual void doConfigure(std::vector<std::string> const & item);
  virtual int  doGetNextFileURI(std::string & uri, double & waitTime);
  virtual void doUpdateStatus(std::string const & uri, FileDisposition status);
  virtual void doOutputFileOpened(std::string const & module_label);
  virtual void doOutputModuleInitiated(std::string const & module_label,
                                       fhicl::ParameterSet const & pset);
  virtual void doOutputFileClosed(std::string const & module_label,
                                  std::string const & fileFQname);
  virtual void doEventSelected(std::string const & module_label,
                               EventID const & event_id,
                               HLTGlobalStatus const & acceptance_info);
  virtual void doIsSearchable();
  virtual doRewind();
};

}
