#include "Logger.h"
#include "SharedConnector.h"

SharedConnector::SharedConnector(std::string serverBaseURL){
  this->serverBaseURL = serverBaseURL;
  curl = curl_easy_init();
}

SharedConnector::~SharedConnector() {
  curl_easy_cleanup(curl);
}

bool SharedConnector::testConnection(){
 
  if(this->curl) {
    curl_easy_setopt(this->curl, CURLOPT_URL, this->serverBaseURL.c_str());
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(this->curl, CURLOPT_NOBODY, 1L);
 
    /* Perform the request, res will get the return code */ 
    this->res = curl_easy_perform(this->curl);
    /* Check for errors */ 
    if(this->res != CURLE_OK) {
      Logger log;
      string message = "curl_easy_perform() failed: ";
      message = message + curl_easy_strerror(this->res);
      log.error(message);

      return false;
    }
 
    return true;
  }

  Logger log;
  string message = "curl_easy_init failed.";
  log.error(message);
  return false;
}
