#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Name.h"
#include "fhiclcpp/types/Comment.h"

//#include <nopayloadclient/nopayloadclient.hpp>



class ConditionsData  {
       
  public:
    struct Config {
      using Name = fhicl::Name;
      using Comment = fhicl::Comment;

      fhicl::Atom<unsigned int> AtomicNumber{
	Name("AtomicNumber"),
	  Comment("atomic number of the active material in the TPC"),
	  18U // default value
      };
    };
  // ART constructor...
  ConditionsData( __attribute__((unused)) fhicl::ParameterSet const & cfg, __attribute__((unused)) art::ActivityRegistry &r) {}

  //ConditionsData( fhicl::ParameterSet const & cfg, art::ActivityRegistry &r) {};
  void sayHello() {
    std::cout << "ConditionsData::sayHello()" << std::endl;
  }
  void printDBSize() {
    std::cout << "ConditionsData::printDBSize()" << std::endl;
  }

  std::string getUrl(int run_number, const std::string& type) {
    std::cout << "ConditionsData::getUrl()" << std::endl;
    std::cout << "run_number = " << run_number << std::endl;
    std::cout << "type = " << type << std::endl;
    return "example_url";
  }
};
