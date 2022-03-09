#ifndef ifdh_art_IFCatalogInterface_IFCatalogInterface_service_h
#define ifdh_art_IFCatalogInterface_IFCatalogInterface_service_h

#include "art/Framework/Services/FileServiceInterfaces/CatalogInterface.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "fhiclcpp/fwd.h"

#include <vector>

#include "ifdh_art/IFDHService/IFDH_service.h"

namespace ifdh_ns {

  class IFCatalogInterface : public art::CatalogInterface {
  public:
    IFCatalogInterface(fhicl::ParameterSet const&);
    ~IFCatalogInterface();

  private:
    art::ServiceHandle<IFDH> _ifdh_handle;
    std::string _process_id{};
    std::string _proj_uri{};
    std::string _project_name{};
    std::string _sam_station{};
    std::string _last_file_uri{};
    std::vector<std::string> _output_files;
    std::vector<bool> _output_ignore;

    void doConfigure(std::vector<std::string> const& item) override;
    int doGetNextFileURI(std::string& uri, double& waitTime) override;
    void doUpdateStatus(std::string const& uri,
                        art::FileDisposition status) override;
    void doOutputFileOpened(std::string const& module_label) override;
    void doOutputModuleInitiated(std::string const& module_label,
                                 fhicl::ParameterSet const& pset) override;
    void doOutputFileClosed(std::string const& module_label,
                            std::string const& fileFQname) override;
    void doEventSelected(std::string const& module_label,
                         art::EventID const& event_id,
                         art::HLTGlobalStatus const& acceptance_info) override;
    bool doIsSearchable() override;
    void doRewind() override;
  };

}

DECLARE_ART_SERVICE_INTERFACE_IMPL(ifdh_ns::IFCatalogInterface,
                                   art::CatalogInterface,
                                   SHARED)

#endif /* ifdh_art_IFCatalogInterface_IFCatalogInterface_service_h */

// Local Variables:
// mode: c++
// End:
