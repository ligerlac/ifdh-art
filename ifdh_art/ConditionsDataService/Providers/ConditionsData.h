#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Name.h"
#include "fhiclcpp/types/Comment.h"
#include "fhiclcpp/types/OptionalSequence.h"
#include "fhiclcpp/types/Sequence.h"
#include "fhiclcpp/types/Tuple.h"
#include "fhiclcpp/types/DelegatedParameter.h"

//#include <nopayloadclient/dunenpc.hpp>


class ConditionsData  {
       
public:
  struct Config {
    using Name = fhicl::Name;
    using Comment = fhicl::Comment;

    fhicl::Atom<std::string> global_tag {
      Name("global_tag"),
      Comment("global configuration parameter for all conditions data")
    };
    //    fhicl::DelegatedParameter delegated_parameter {
    //      Name("override_dicts"),
    //      Comment("override payloads urls for specified condition types like"
    //	      "{type_1: url_1, type_2: url_2, ...}")
    //    };
    fhicl::OptionalSequence<fhicl::Tuple<std::string, std::string>> override_pairs {
      Name("override_pairs"),
      Comment("override url's for given condition types [[type1, url1], ...]")
    };
  };


  ConditionsData(Config const& config) {
    std::cout << "config.global_tag() = " << config.global_tag() << std::endl;
    std::vector<std::tuple<std::string, std::string>> override_pairs;
    if ( !config.override_pairs(override_pairs) ) return;
    for (const auto& pair : override_pairs) {
      std::cout << "std::get<0>(pair) = " << std::get<0>(pair) << std::endl;
      std::cout << "std::get<1>(pair) = " << std::get<1>(pair) << std::endl;
      //      client_.override(std::get<0>(pair), std::get<1>(pair));
    }
  }

  std::string getUrl(int run_number, const std::string& type) const {
    std::cout << "getUrl()" << std::endl;
    std::cout << "run_number = " << run_number << std::endl;
    std::cout << "type = " << type << std::endl;
    return "url";
    //    return client_.getUrl(run_number, type);
  }

  // copy and moving of service providers is "forbidden":
  ConditionsData(ConditionsData const& pset) = delete;
  ConditionsData(ConditionsData&& pset) = delete;
  ConditionsData& operator=(ConditionsData const& pset) = delete;
  ConditionsData& operator=(ConditionsData&& pset) = delete;

private:
  //  dunenpc::DuneClient client_;
};
