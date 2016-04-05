#include "CallBacks.h"
#include "Logger.h"
#include "SharedConnector.h"

SharedConnector::SharedConnector(std::string serverBaseURL){
  this->serverBaseURL = serverBaseURL;
  curl = curl_easy_init();
}

SharedConnector::~SharedConnector() {
  curl_easy_cleanup(curl);
}

bool SharedConnector::getJsonFromURL(std::string url, Json::Value& jsonData) {
  //estructura en donde se van a guardar los datos.
  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */

  curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->curl, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void *)&chunk);
  this->res = curl_easy_perform(this->curl);
  /* Check for errors */ 
  if(this->returnedError()) return false;
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */ 
    
    //printf("%lu bytes retrieved\n", (long)chunk.size);
    std::string data((char*)chunk.memory);
    Json::Reader reader;
    if(reader.parse(data, jsonData)) {

      free(chunk.memory);
      return true;
    }
    else {
      free(chunk.memory);
      Logger log;;
      log.error("Error parsing Json.");
      return false;
    }
  }
}

bool SharedConnector::getUserByID(int id, Json::Value& userData) {

  string url = this->serverBaseURL + "/users/" + std::to_string(id);
  return this->getJsonFromURL(url, userData);
}


bool SharedConnector::getAllUsers(Json::Value& usersData) {
  string url = this->serverBaseURL + "/users";
  return this->getJsonFromURL(url, usersData);
}

bool SharedConnector::returnedError() {
  if (this->res != CURLE_OK) {
    Logger log;
    string message = "curl_easy_perform() failed: ";
    message = message + curl_easy_strerror(this->res);
    log.error(message);

    return true;
  }
  return false;
}

bool SharedConnector::testConnection(){
 
  if(this->curl) {
    curl_easy_setopt(this->curl, CURLOPT_URL, this->serverBaseURL.c_str());
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(this->curl, CURLOPT_NOBODY, 1L);
 
    /* Perform the request, res will get the return code */ 
    this->res = curl_easy_perform(this->curl);
    /* Check for errors */ 
    return !(this->returnedError());
  }

  Logger log;
  string message = "curl_easy_init failed.";
  log.error(message);
  return false;
}
