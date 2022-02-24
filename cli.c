#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APPLICATION_NAME "feminist_cli"
#define CLI_VERSION "0.0.1"
#define MAX_LENGTH 256
#define APPLICATION_CLI_HELP_MSG "\
Usage: %s [OPTION]\n\nMandatory arguments:\n\
  -l, --list\t\tList the server requests;\n\
  -h, --help\t\tPrints out the help menu;\n\
  -v, --version\t\tGet the current CLI version;\n"
#define EVENT_LOG_FILENAME "./logs/events.csv"
#define INVALID_OPTION_MSG "Invalid option. Use --help for more information.\n"

static int strfind(char *str, char c)
{
  int i = 0;

  while (str[i] != c)
    i++;
  return i;
}

static int count_word_matches(char *filename, char *word)
{
  FILE *fp = fopen(filename, "r");
  char buffer[MAX_LENGTH];
  int word_matches = 0;

  if (fp == NULL)
  {
    perror("Error: could not open file.\n");
    return 1;
  }

  while (fgets(buffer, MAX_LENGTH, fp))
  {
    int after_comma_pos = strfind(buffer, ',') + 1;

    if (strncmp(&buffer[after_comma_pos], word, strlen(word)) == 0)
      word_matches++;
  }

  fclose(fp);
  return word_matches;
}

static int handle_logs(char *filename)
{
  enum {
    GET_ROOT,
    GET_QUOTE,
    POST_HELLO,
    ENUM_LENGTH
  };
  int logs[ENUM_LENGTH];

  logs[GET_ROOT] = count_word_matches(filename, "GET,ROOT");
  logs[POST_HELLO] = count_word_matches(filename, "POST,/hello");
  printf("Total GET root calls: %d\n", logs[GET_ROOT]);
  printf("Total POST hello calls: %d\n", logs[POST_HELLO]);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
      printf(APPLICATION_CLI_HELP_MSG, argv[0]);
      return 0;
    }
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
      printf("%s v%s\n", APPLICATION_NAME, CLI_VERSION);
      return 0;
    }
    if (strcmp(argv[1], "--list") == 0 || strcmp(argv[1], "-l") == 0) {
      handle_logs(EVENT_LOG_FILENAME);
      return 0;
    }
    printf(INVALID_OPTION_MSG);
    return 0;
  }
  printf(APPLICATION_CLI_HELP_MSG, argv[0]);
  return 0;
}
