#include "IFCatalogInterface_service.h"
#include "art/Framework/Services/FileServiceInterfaces/FileDeliveryStatus.h"
#include "fhiclcpp/ParameterSet.h"

#include "messagefacility/MessageLogger/MessageLogger.h"

namespace ifdh_ns {

  IFCatalogInterface::IFCatalogInterface(fhicl::ParameterSet const& cfg)
  {
    mf::LogVerbatim("test") << "IFCatalogInterface constructor, got keys:";
    for (auto const& key : cfg.get_names()) {
      mf::LogVerbatim("test") << key << ", ";
    }

    if (cfg.get_if_present("webURI", _proj_uri)) {
      mf::LogVerbatim("test")
        << "IFCatalogInterface: set _proj_uri to:" << _proj_uri << "\n";
    }
  }

  IFCatalogInterface::~IFCatalogInterface()
  {
    std::string process_status("completed");
    mf::LogVerbatim("test") << "IFCatalogInterface destructor:";
    if (_last_file_uri.length()) {
      mf::LogVerbatim("test")
        << "IFCatalogInterface: updating file status in destructor";
      doUpdateStatus(_last_file_uri, art::FileDisposition::SKIPPED);
      process_status = "bad";
    }
    if (_proj_uri.length() && _process_id.length()) {
      _ifdh_handle->setStatus(_proj_uri, _process_id, process_status);
    }
  }

  void
  IFCatalogInterface::doConfigure(std::vector<std::string> const& item)
  {
    if (item.size()) {
      _process_id = item[0];
      mf::LogVerbatim("test")
        << "IFCatalogInterface doConfigure, got id:" << item[0];
    }
  }

  int
  IFCatalogInterface::doGetNextFileURI(std::string& uri, double& /*waitTime*/)
  {
    mf::LogVerbatim("test") << "IFCatalogInterface entering doGetNextFile\n";
    if (_last_file_uri.length()) {
      mf::LogVerbatim("test") << "Updating status in doGetNextFile\n";
      // XXX should this be  art::FileDisposition::SKIPPED ???
      // shouldn't we have updated the status already?
      doUpdateStatus(_last_file_uri, art::FileDisposition::CONSUMED);
    }
    if (_proj_uri.length()) {
      uri = _ifdh_handle->getNextFile(_proj_uri, _process_id);
      _last_file_uri = uri;
      if (uri.length()) {
        mf::LogVerbatim("test") << "doGetNextFile success\n";
        return art::FileDeliveryStatus::SUCCESS;
      }
      mf::LogVerbatim("test") << "doGetNextFile no_more_files\n";
      return art::FileDeliveryStatus::NO_MORE_FILES;
    }
    return art::FileDeliveryStatus::BAD_REQUEST;
  }

  void
  IFCatalogInterface::doUpdateStatus(std::string const& uri,
                                     art::FileDisposition status)
  {
    constexpr const char* statusmap[] = {
      "transferred", "consumed", "skipped", "consumed", /* INCOMPLETE */
    };

    mf::LogVerbatim("test") << "IFCatalogInterface doUpdateStatus " << uri
                            << " status: " << int(status) << "\n";

    if (_proj_uri.length()) {
      _ifdh_handle->updateFileStatus(
        _proj_uri, _process_id, uri, statusmap[int(status)]);
      if (status != art::FileDisposition::TRANSFERRED) {
        int res = unlink(_ifdh_handle->localPath(_last_file_uri).c_str());
        mf::LogVerbatim("test") << "unlink of file returns:" << res << "\n";
        _last_file_uri = "";
      }
    }
  }

  void
  IFCatalogInterface::doOutputFileOpened(std::string const&)
  {}

  void
  IFCatalogInterface::doOutputModuleInitiated(
    std::string const& /*module_label*/,
    fhicl::ParameterSet const& pset)
  {
    mf::LogVerbatim("test")
      << "IFCatalogInterface doOutputModuleInitiated, got keys:";
    for (auto const& key : pset.get_names()) {
      mf::LogVerbatim("test") << key << ", ";
    }

    if (auto fileName = pset.get_if_present<std::string>("fileName")) {
      _output_files.push_back(*fileName);
    }
    _output_ignore.push_back(pset.get<bool>("sam_ignore", false));
  }

  void
  IFCatalogInterface::doOutputFileClosed(std::string const& module_label,
                                         std::string const& fileFQname)
  {
    mf::LogVerbatim("test")
      << "IFCatalogInteface doOutputFileClosed: " << module_label << ", "
      << fileFQname << "\n";
  }

  void
  IFCatalogInterface::doEventSelected(std::string const&,
                                      art::EventID const&,
                                      art::HLTGlobalStatus const&)
  {}

  bool
  IFCatalogInterface::doIsSearchable()
  {
    return false;
  }

  void
  IFCatalogInterface::doRewind()
  {}

}
