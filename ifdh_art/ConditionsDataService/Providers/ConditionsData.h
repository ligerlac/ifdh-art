#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Name.h"
#include "fhiclcpp/types/Comment.h"
#include "fhiclcpp/types/OptionalSequence.h"
#include "fhiclcpp/types/Sequence.h"
#include "fhiclcpp/types/Tuple.h"
#include "fhiclcpp/types/DelegatedParameter.h"

//#include <nopayloadclient/nopayloadclient.hpp>
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
    //      Name("override_dict"),
    //      Comment("override payloads urls for specified condition types like"
    //	      "{type_1: url_1, type_2: url_2, ...}")
    //    };
    fhicl::OptionalSequence<fhicl::Tuple<std::string, std::string>> override_dict {
      Name("override_dict"),
      Comment("override url's for given condition types [[type1, url1], ...]")
    };
  };


  ConditionsData(Config const& config) {
    std::cout << "config.global_tag() = " << config.global_tag() << std::endl;
    //    std::cout << "config.override_dict() = " << config.override_dict() << std::endl;
    global_tag_ = config.global_tag();
    //    override_dict_ = config.override_dict();
  }

  // ART constructor...
  ConditionsData( __attribute__((unused)) fhicl::ParameterSet const & cfg, __attribute__((unused)) art::ActivityRegistry &r) {}

  //ConditionsData( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {};
  void sayHello() const {
    std::cout << "ConditionsData::sayHello()" << std::endl;
    std::cout << "global_tag = " << global_tag_ << std::endl;
    //    std::cout << "override_dict = " << override_dict_ << std::endl;
  }

  void printDBSize() const {
    std::cout << "ConditionsData::printDBSize()" << std::endl;
  }

  std::string getUrl(int run_number, const std::string& type) const {
    std::cout << "ConditionsData::getUrl()" << std::endl;
    std::cout << "run_number = " << run_number << std::endl;
    std::cout << "type = " << type << std::endl;
    return "example_url";
  }

  // copy and moving of service providers is "forbidden":
  ConditionsData(ConditionsData const& pset) = delete;
  ConditionsData(ConditionsData&& pset) = delete;
  ConditionsData& operator=(ConditionsData const& pset) = delete;
  ConditionsData& operator=(ConditionsData&& pset) = delete;

private:
  std::string global_tag_;
  //  nlohmann::json override_dict_;
};
