#ifndef VAULT_CLIENT_HASHICORPVAULTCLIENT_H
#define VAULT_CLIENT_HASHICORPVAULTCLIENT_H
#include <string>
#include <curl/curl.h>

class HashicorpVaultService {
protected:
  const std::string uri;
  const std::string token;
  CURL *curl;
public:

  HashicorpVaultService(const std::string& u, const std::string& t);

  virtual ~HashicorpVaultService();

  std::string getSecret(const std::string& secret) const;
};
#endif //VAULT_CLIENT_HASHICORPVAULTCLIENT_H
