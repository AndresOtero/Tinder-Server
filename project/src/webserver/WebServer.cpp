/*
 * WebServer.cpp
 *
 *  Created on: 18 de mar. de 2016
 *      Author: jonathan
 */

#include <iostream>
#include "WebServer.h"
#include "mongoose.h"
#include "dispatcher/EndPoint.h"
using namespace std;



static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

WebServer::WebServer() {
	// TODO Auto-generated constructor stub

}

WebServer::~WebServer() {
	// TODO Auto-generated destructor stub
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  WebServer * server = (WebServer *) nc->user_data;
  struct http_message *hm = (struct http_message *) ev_data;
  if (ev == MG_EV_HTTP_REQUEST) {
	  string uri = server->getUri(hm);
	  cout<<uri<<endl;
	  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
  }

}

void WebServer::start() {

	  struct mg_mgr mgr;

	  mg_mgr_init(&mgr, NULL);
	  connection = mg_bind(&mgr, s_http_port, ev_handler);
mg_enable_multithreading(connection);
	  // Set up HTTP server parameters
	  mg_set_protocol_http_websocket(connection);
	  s_http_server_opts.document_root = ".";  // Serve current directory
	  s_http_server_opts.dav_document_root = ".";  // Allow access via WebDav
	  s_http_server_opts.enable_directory_listing = "yes";

	  printf("Starting web server on port %s\n", s_http_port);
	  for (;;) {
	    mg_mgr_poll(&mgr, 1000);
	  }
	  mg_mgr_free(&mgr);
}

string WebServer::getUri(http_message* hm) {
	  string uri (*(&hm->uri.p));
	  std::size_t found = uri.find(" ");
	   if (found!=std::string::npos)
	     uri = uri.substr(0,found);
	   return uri;
}
