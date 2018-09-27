#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include "hashicorpvaultclient.hpp"

int main(int argc, char **argv) {
  std::string tokenParameter;

  opterr = 0;

  int c;
  while ((c = getopt(argc, argv, "t:")) != -1) {
    switch (c) {
      case 't':
        tokenParameter = optarg;
        break;
      default:
        exit(1);
    }
  }

  std::cout << "Using token: " << tokenParameter << std::endl;

  HashicorpVaultService vaultService("http://localhost:8200", tokenParameter);


  try {
  std::cout << vaultService.getSecret("test") << std::endl;
  std::cout << vaultService.getSecret("tes") << std::endl;
  } catch (std::logic_error &e) {
    std::cout << e.what() << std::endl;
  }
}
