#ifndef ADA_H
#define ADA_H

#include <stdio.h>
#include <string.h>
#include "fort.h"

#define CLI_VERSION "0.0.2"
#define MAX_LENGTH 256
#define APPLICATION_CLI_HELP_MSG "\
Usage: %s [OPTION]\n\nMandatory arguments:\n\
  -c, --clear\t\tClear the server events log;\n\
  -l, --list\t\tList the server requests;\n\
  -h, --help\t\tPrints out the help menu;\n\
  -v, --version\t\tGet the current CLI version;\n"
#define EVENT_LOG_FILENAME "./logs/events.csv"
#define INVALID_OPTION_MSG "Invalid option. Use --help for more information.\n"

typedef enum {
  GET_ROOT,
  GET_QUOTE,
  GET_MOCK,
  POST_MOCK,
  PUT_MOCK,
  DELETE_MOCK,
  ENUM_LENGTH
} t_req_type;

#endif
