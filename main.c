// Copyright (c) 2020 Cesanta Software Limited
// All rights reserved
//
// HTTP server example. This server serves both static and dynamic content.
// It opens two ports: plain HTTP on port 8000 and HTTP on port 8443.
// It implements the following endpoints:
//    /api/f1 - respond with JSON string {"result": 123}
//    /api/f2/:id - wildcard example, respond with JSON string {"result": "URI"}
//    any other URI serves static files from s_root_dir
//
// To enable SSL/TLS (using self-signed certificates in PEM files),
//    1. make MBEDTLS_DIR=/path/to/your/mbedtls/installation
//    2. curl -k https://127.0.0.1:8443

#include "mongoose.h"
#include <time.h>

static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8443";  // HTTPS port
static const char *s_log_file = "./logs/server.log";
static const char *s_events_log_file = "./logs/events.csv";
static const char *s_cert_file = "./config/server.pem";
// static const char *s_root_dir = ".";

/**
 * @brief Generates a formatted timestamp for the current system local time.
 *
 * @param buffer The buffer to write the timestamp to.
 */
static void gen_timestamp(char *buffer) {
  time_t rawtime;
  struct tm *info;
  time(&rawtime);
  info = localtime(&rawtime);
  strftime(buffer,80,"%x - %I:%M%p", info);
}

/**
 * @brief Generates an event log message in the given path.
 *
 * @param logpath The path of the file to log to. The file will be written using CSV standard.
 */
static void gen_root_event_log(const char *logpath) {
  char buffer[80];
  FILE *fp = fopen(logpath, "a+");
  gen_timestamp(buffer);
  strcat(buffer, ",GET,ROOT\n");
  fputs(buffer, fp);
  fclose(fp);
}

// We use the same event handler function for HTTP and HTTPS connections
// fn_data is NULL for plain HTTP, and non-NULL for HTTPS
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  (void) fn_data; // Unused
  if (ev == MG_EV_ACCEPT && fn_data != NULL) {
    struct mg_tls_opts opts = {
        .cert = s_cert_file,     // Certificate PEM file
        .certkey = s_cert_file,  // This pem contains both cert and key
    };
    mg_tls_init(c, &opts);
  } else if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *msg = (struct mg_http_message *) ev_data;
    if (mg_http_match_uri(msg, "/")) {
      gen_root_event_log(s_events_log_file);
      mg_http_reply(
        c, 200, "Content-type: application/json\r\n",
        "{\"message\": \"%s\", \"author\": \"%s\"}\n",
        "It took me quite a long time to develop a voice,\
 and now that I have it, I am not going to be silent.",
        "Madeleine Albright"
      );
    } else {
      mg_http_reply(
        c, 404, "Content-type: text/html\r\n",
        "<html><body>We were unable to find this content.</body></html>"
      );
    }
  }
}


static void log_to_file(const void *buf, size_t len, void *ud)
{
  fwrite(buf, 1, len, (FILE *)ud);
}

int main(void) {
  struct mg_mgr mgr;                            // Event manager
  FILE *fp = fopen(s_log_file, "w");
  mg_log_set("4");                              // Set to 4 will enable all loggings to file
  mg_log_set_callback(&log_to_file, fp);       // Set to log to file
  mg_mgr_init(&mgr);                            // Initialise event manager
  mg_http_listen(&mgr, s_http_addr, fn, NULL);  // Create HTTP listener
  mg_http_listen(&mgr, s_https_addr, fn, (void *) 1);  // HTTPS listener
  for (;;) mg_mgr_poll(&mgr, 1000);                    // Infinite event loop
  mg_mgr_free(&mgr);

  return 0;
}
