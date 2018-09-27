#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include "hashicorpvaultclient.hpp"

HashicorpVaultService::HashicorpVaultService(const std::string& u, const std::string& t) : uri(u), token(t)  {
  curl = curl_easy_init();
}

HashicorpVaultService::~HashicorpVaultService() {
  curl_easy_cleanup(curl);

}
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *) userp)->append((char *) contents, size * nmemb);
  return size * nmemb;
}

std::string HashicorpVaultService::getSecret(const std::string& secret) const  {
  CURLcode res;
  std::string readBuffer;

  if (curl) {
    const std::string tokenheader = "X-Vault-Token: " + token;
    const std::string getUri(uri + "/v1/secret/" + secret);

    std::cout  << getUri << std::endl;

    struct curl_slist *chunk = NULL;
    chunk = curl_slist_append(chunk, tokenheader.c_str());

    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    if(res != CURLcode::CURLE_OK) {
      const std::string errorMsg ("CURL Failure in adding headers. CURL Error code: "  + std::to_string(res));
      throw std::logic_error(errorMsg);
    }

    curl_easy_setopt(curl, CURLOPT_URL, getUri.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    if(res != CURLcode::CURLE_OK) {
      const std::string errorMsg
          ("CURL Failure in contacting Vault. CURL Error code: "  + std::to_string(res));
      throw std::logic_error(errorMsg);
    }

    long http_code = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (http_code == 200) {
      rapidjson::Document document;
      document.Parse(readBuffer.c_str());

      return document["data"]["secret"].GetString();
    }
    else {
      const std::string errorMsg
          ("Failure in contacting Vault. Error code: "  + std::to_string(http_code)
           + " Response content: " + readBuffer);
      throw std::logic_error(errorMsg);
    }
  }
  return 0;
}
