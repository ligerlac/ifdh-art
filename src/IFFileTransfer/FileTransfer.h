class art::FileTransfer {
public:
  int translateToLocalFilename(std::string const & uri,
                               std::string & fileFQname);

  // Remaining boilerplate:
  virtual ~FileTransfer() = default;

private:
  // Classes inheriting this interface must provide the following method:
  virtual 
  int 
  doTranslateToLocalFilename(std::string const & uri,
                             std::string & fileFQname) = 0;
};
