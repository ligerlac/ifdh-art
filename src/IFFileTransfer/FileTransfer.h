#ifndef FILETRANSFER_H
#define FILETRANSFER_H

namespace art {
class FileTransfer {
public:
  int translateToLocalFilename(std::string const & uri,
                               std::string & fileFQname) {
	doTranslateToLocalFilename(uri, fileFQname);
     }

  // Remaining boilerplate:
  virtual ~FileTransfer() = 0;

private:
  // Classes inheriting this interface must provide the following method:
  virtual 
  int 
  doTranslateToLocalFilename(std::string const & uri,
                             std::string & fileFQname) = 0;
};

}
#endif // FILETRANSFER_H
