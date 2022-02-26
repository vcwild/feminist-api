/*
ada CLI

GNU GPL v3

Copyright (c) 2022 Victor Wildner
*/
#ifndef ADA_H
#define ADA_H
#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fort.h"

#define CLI_VERSION "0.1.1"

#define MAX_LENGTH 256

#define APPLICATION_CLI_HELP_MSG "\
Usage: %s [OPTION]\
\n\n\
Optional arguments:\n\
  -c, --clear\t\t\tClear the server events log;\n\
  -e, --endpoints\t\tShow the available endpoints;\n\
  -h, --help\t\t\tPrints out the help menu;\n\
  -l, --list, --logs\t\tList the server requests;\n\
  -s, --show\t\t\tAlias to --endpoints;\n\
  -v, --version\t\t\tGet the current CLI version.\n"

#define HOST_NAME "localhost"
#define HOST_PORT "8000"
#define HOST_URL "http://" HOST_NAME ":" HOST_PORT
#define AVAILABLE_ENDPOINTS_MSG "Available endpoints:\n"\
"  " HOST_URL "/\n"\
"  " HOST_URL "/api\n"\
"  " HOST_URL "/mock\n"

#define EVENT_LOG_FILENAME "./logs/events.csv"

#define INVALID_OPTION_MSG "Invalid option. Use --help for more information.\n"

typedef enum s_req_type{
  GET_ROOT,
  GET_API,
  GET_MOCK,
  POST_MOCK,
  PUT_MOCK,
  DELETE_MOCK,
  ENUM_LENGTH
} t_req_type;

#endif
