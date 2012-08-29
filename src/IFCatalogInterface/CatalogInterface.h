namespace art {
// all stubs, really...
enum FileDisposition { e_dispo_ok, e_dispo_no_more, e_dispo_bad };
enum FileDeliveryStatus { e_delivery_ok, e_delivery_bad };
class HLTGlobalStatus { int status; };
class EventID { int status; };

class CatalogInterface {

public:

  void configure(std::vector<std::string> const & items);
  int  getNextFileURI(std::string & uri, double & waitTime);
  void updateStatus(std::string const & uri, FileDisposition status);
  void outputFileClosed(std::string const & module_label,
                        std::string const & fileFQname);
  void outputFileOpened(std::string const & module_label);
  void outputModuleInitiated(std::string const & module_label,
                             fhicl::ParameterSet const & pset);
  void eventSelected(std::string const & module_label,
                     EventID const & event_id,
                     HLTGlobalStatus const & acceptance_info);
  bool isSearchable();
  void rewind();
  virtual ~CatalogInterface() = 0;
private:
  // Classes inheriting this interface must provide the following methods:
  virtual void doConfigure(std::vector<std::string> const & item) = 0;
  virtual int  doGetNextFileURI(std::string & uri, double & waitTime) = 0;
  virtual void doUpdateStatus(std::string const & uri, FileDisposition status) = 0;
  virtual void doOutputFileOpened(std::string const & module_label) = 0;
  virtual void doOutputModuleInitiated(std::string const & module_label,
                                       fhicl::ParameterSet const & pset) = 0;
  virtual void doOutputFileClosed(std::string const & module_label,
                                  std::string const & fileFQname) = 0;
  virtual void doEventSelected(std::string const & module_label,
                               EventID const & event_id,
                               HLTGlobalStatus const & acceptance_info) = 0;
  virtual bool doIsSearchable() = 0;
  virtual void doRewind() = 0;
};
}
