#include "IFDH_service.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include <iostream>
#include <vector>

namespace ifdh_ns {

// ART Service constructor -- currently does nothing.
//
//
IFDH::IFDH( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {
  std::vector<std::string> cfgkeys = cfg.get_keys();
  std::string s;

  mf::LogVerbatim("test") << "IFDH constructor, got keys:";
  for (std::vector<std::string>::iterator p = cfgkeys.begin(); p != cfgkeys.end(); p++ ) {
       mf::LogVerbatim("test")<< *p << ", ";
  }

  if ( cfg.get_if_present("IFDH_BASE_URI", s) ) {
      mf::LogVerbatim("test") << "IFDH: setting uri to:" << s << "\n";
      this->set_base_uri(s);
  } else {
      mf::LogVerbatim("test") << "IFDH: didn't find a base uri...\n";
  }
}      

}

DEFINE_ART_SERVICE(ifdh_ns::IFDH);

