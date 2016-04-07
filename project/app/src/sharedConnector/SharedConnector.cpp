#include "CallBacks.h"
#include "Logger.h"
#include "SharedConnector.h"
using namespace std;


SharedConnector::SharedConnector(std::string serverBaseURL){
  this->serverBaseURL = serverBaseURL;
}

SharedConnector::~SharedConnector() {}

bool SharedConnector::getJsonFromURL(std::string endpoint, Json::Value& jsonData) {
  //concateno baseurl con el endpoint recibido
  string url = this->serverBaseURL + endpoint;
  //estructura en donde se van a guardar los datos.
  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */

  //Inicio y configuro las opciones de curl
  CURL *curl;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  /* Check for errors */ 
  if(this->returnedError(res)) return false;
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */ 
    
    //printf("%lu bytes retrieved\n", (long)chunk.size);
    string data((char*)chunk.memory);
    Json::Reader reader;
    if(reader.parse(data, jsonData)) {

      free(chunk.memory);
      return true;
    }
    else {
      free(chunk.memory);
      LOG_ERROR << "Error parsing Json.";
      return false;
    }
  }
}


bool SharedConnector::returnedError(CURLcode res) {
  if (res != CURLE_OK) {
    LOG_ERROR << "curl_easy_perform() failed: " << curl_easy_strerror(res);
    return true;
  }
  return false;
}

bool SharedConnector::testConnection(){
 
  CURL *curl;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, this->serverBaseURL.c_str());
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
 
    /* Perform the request, res will get the return code */ 
    CURLcode res = curl_easy_perform(curl);
    /* Check for errors */ 
    return !(this->returnedError(res));
  }

  LOG_ERROR << "curl_easy_init failed.";
  return false;
}
