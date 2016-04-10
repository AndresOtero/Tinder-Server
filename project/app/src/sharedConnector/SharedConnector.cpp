#include "CallBacks.h"
#include "../log/Logger.h"
#include "SharedConnector.h"
using namespace std;


SharedConnector::SharedConnector(std::string serverBaseURL){
  this->serverBaseURL = serverBaseURL;
}

SharedConnector::~SharedConnector() {}

bool SharedConnector::deleteToURL(std::string endpoint) {
  CURL* curl;
  CURLcode res;

  curl = curl_easy_init();
  string url = this->serverBaseURL + endpoint;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  res = curl_easy_perform(curl);

  /* always cleanup */ 
  curl_easy_cleanup(curl);
  if(this->returnedError(res)) return false;
  return true;
}

bool SharedConnector::postDataToURL(std::string endpoint, string data) {

  CURL *curl;
  CURLcode res;
  //Estructura donde se guardan los datos a enviar.
  struct SendStruct pooh;
  pooh.memory = data.c_str();
  pooh.size = strlen(data.c_str());

  //estructura en donde se van a guardar los datos.
  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */

  curl = curl_easy_init();
  /* First set the URL that is about to receive our POST. */ 
  string url = this->serverBaseURL + endpoint;
  struct curl_slist *headers = NULL;
  curl_slist_append(headers, "Accept: application/json");
  curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
  curl_slist_append(headers, "charsets: utf-8");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  /* Now specify we want to POST data */ 
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  /* we want to use our own read function */ 
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  /* pointer to pass to our read function */ 
  curl_easy_setopt(curl, CURLOPT_READDATA, &pooh);
  /* get verbose debug output please */ 
  //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  /* Set the expected POST size. If you want to POST large amounts of data,
     consider CURLOPT_POSTFIELDSIZE_LARGE */ 
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t)pooh.size);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
  /* Perform the request, res will get the return code */ 
  res = curl_easy_perform(curl);

  string response((char*)chunk.memory);
  //LOG_ERROR << response;

  /* always cleanup */ 
  curl_easy_cleanup(curl);
  if(this->returnedError(res)) return false;
  return true;
}


bool SharedConnector::putDataToURL(std::string endpoint, std::string data) {
  //concateno baseurl con el endpoint recibido
  string url = this->serverBaseURL + endpoint;

  //estructura en donde se van a guardar los datos.
  struct MemoryStruct chunk;
  chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */

  //preparo el objeto curl
  CURL *curl;
  curl = curl_easy_init();
  struct curl_slist *headers = NULL;
  curl_slist_append(headers, "Accept: application/json");
  curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
  curl_slist_append(headers, "charsets: utf-8");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
  //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  string response((char*)chunk.memory);
  //LOG_ERROR << response;

  if(this->returnedError(res)) return false;
  return true;
}

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
