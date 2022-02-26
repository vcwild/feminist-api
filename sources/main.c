#include "mongoose.h"
#include <signal.h>
#include <time.h>

static const char *s_http_addr = "http://0.0.0.0:8000";    // HTTP port
static const char *s_https_addr = "https://0.0.0.0:8443";  // HTTPS port
static const char *s_log_file = "./logs/server.log";
static const char *s_events_log_file = "./logs/events.csv";
static const char *s_cert_file = "./config/server.pem";
static int s_signo;

static void signal_handler(int signo) {
  s_signo = signo;
}

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
static void gen_event_log(const char *logpath, const char *method_path_pair) {
  char buffer[80];
  FILE *fp = fopen(logpath, "a+");
  gen_timestamp(buffer);
  strcat(buffer, method_path_pair);
  fputs(buffer, fp);
  fclose(fp);
}

/**
 * @brief A helper function to bring up a random quote. Not so pretty to be here.
 *
 * @param c The connection object.
 */
void dispatch_quote(struct mg_connection *c);

/**
 * @brief A handler function to communicate with the client.
 *
 * @param c A mongoose connection object.
 * @param ev The environment variable.
 * @param ev_data The data from the environment variable.
 * @param fn_data The function data.
 */
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
    if (mg_http_match_uri(msg, "/api")) {
      gen_event_log(s_events_log_file, ",GET,/api\n");
      dispatch_quote(c);
    } else if (mg_http_match_uri(msg, "/")) {
      gen_event_log(s_events_log_file, ",GET,ROOT\n");
    } else if (mg_http_match_uri(msg, "/mock")) {
      gen_event_log(s_events_log_file, ",GET,MOCK\n");
      mg_http_reply(
        c, 200, "Content-type: application/json\r\n",
        "{\"message\": \"%s\"}\n",
        "Hello mock!!"
      );
    } else {
      struct mg_http_serve_opts opts = {.root_dir = "sources/pages"};
      mg_http_serve_dir(c, msg, &opts);
    }
  }
}

/**
 * @brief Generates logs to the given path.
 *
 * @param buf The buffer to write the logs to.
 * @param len The length of the buffer.
 * @param ud The file pointer to write to.
 */
static void log_to_file(const void *buf, size_t len, void *ud)
{
  fwrite(buf, 1, len, (FILE *)ud);
}

int main(void) {
  signal(SIGINT, signal_handler);                // Listen for Ctrl-C
  signal(SIGTERM, signal_handler);               // Listen for kill
  FILE *fp = fopen(s_log_file, "w");             // Open the log file
  mg_log_set("4");                               // Set to 4 will enable all loggings to file
  mg_log_set_callback(&log_to_file, fp);         // Set log to file

  struct mg_mgr mgr;                             // Event manager
  mg_mgr_init(&mgr);                             // Initialise event manager
  mg_http_listen(&mgr, s_http_addr, fn, NULL);   // Create HTTP listener
  mg_http_listen(&mgr, s_https_addr, fn, (void *) 1);  // HTTPS listener
  while (s_signo == 0)
    mg_mgr_poll(&mgr, 1000);                     // Event loop
  mg_mgr_free(&mgr);                             // Free event manager

  return 0;
}
