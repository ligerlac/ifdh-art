#include "ifdh_art/IFDHService/IFDH_service.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

namespace ifdh_ns {

  IFDH::IFDH(fhicl::ParameterSet const& cfg)
  {
    mf::LogVerbatim("test") << "IFDH constructor, got keys:";
    for (auto const& key : cfg.get_names()) {
      mf::LogVerbatim("test") << key << ", ";
    }

    if (auto base_uri = cfg.get_if_present<std::string>("IFDH_BASE_URI")) {
      mf::LogVerbatim("test") << "IFDH: setting uri to:" << *base_uri << "\n";
      this->set_base_uri(*base_uri);
    } else {
      mf::LogVerbatim("test") << "IFDH: didn't find a base uri...\n";
    }
    if (auto debug = cfg.get_if_present<std::string>("debug")) {
      mf::LogVerbatim("test") << "IFDH: turning on debug\n";
      this->set_debug(*debug);
    }
  }

}
