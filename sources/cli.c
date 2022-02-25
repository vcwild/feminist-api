#include "ada.h"

/**
 * @brief Finds the character position in a given `str` string.
 * The given `str` param must be a NULL terminated string.
 *
 * @param str The string to search
 * @param c The character to be searched
 * @return int Returns the position of the character in the string or -1 if not found.
 */
static int strfind(char *str, char c)
{
  int i = 0;

  if (str == NULL)
    return -1;
  while (str[i] != c)
    i++;
  return i;
}

/**
 * @brief Counts the number of occurrences of a given word in a file.
 *
 * @param filename The file to be read.
 * @param word The word to search for.
 * @return int Returns the number of occurrences of the word in the file.
 */
static int count_word_matches(char *filename, char *word)
{
  FILE *fp = fopen(filename, "r");
  char buffer[MAX_LENGTH];
  int word_matches = 0;
  if (fp == NULL) {
    perror("Error: could not open file.\n");
    return 1;
  }
  while (fgets(buffer, MAX_LENGTH, fp)) {
    int after_comma_pos = strfind(buffer, ',') + 1;

    if (strncmp(&buffer[after_comma_pos], word, strlen(word)) == 0)
      word_matches++;
  }
  fclose(fp);
  return word_matches;
}

/**
 * @brief Applies styling to the given table.
 *
 * @param table The table to receive styling.
 */
static void prepare_table_styles(ft_table_t *table) {
  ft_set_border_style(table, FT_DOUBLE2_STYLE);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
}

/**
 * @brief Generates a table with the server events log.
 *
 * @param table The table reference to populate.
 * @param logs The logs counted by the server.
 */
static void populate_table(ft_table_t *table, int *logs) {
  char tmp[10];
  ft_write_ln(table, "HTTP Method", "PATH", "Requests", "About");
  sprintf(tmp, "%2d", logs[GET_ROOT]);
  ft_write_ln(table, "GET", "/", tmp, "Number of GET requests to the root");
  sprintf(tmp, "%2d", logs[GET_MOCK]);
  ft_write_ln(table, "GET", "/mock", tmp, "Number of GET requests to /mock");
  sprintf(tmp, "%2d", logs[POST_MOCK]);
  ft_write_ln(table, "POST", "/mock", tmp, "Number of POST requests to /mock");
  sprintf(tmp, "%2d", logs[PUT_MOCK]);
  ft_write_ln(table, "PUT", "/mock", tmp, "Number of PUT requests to /mock");
  sprintf(tmp, "%2d", logs[DELETE_MOCK]);
  ft_write_ln(table, "DELETE", "/mock", tmp, "Number of DELETE requests to /mock");
  ft_set_cell_prop(
    table, FT_ANY_ROW, FT_ANY_COLUMN,
    FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER
  );
}

/**
 * @brief The main routine to write the table to the stdout.
 *
 * @param logs The logs counted by the server.
 */
static void draw_table(int *logs) {
  ft_table_t *table = ft_create_table();
  prepare_table_styles(table);
  populate_table(table, logs);
  printf("%s\n", ft_to_string(table));
  ft_destroy_table(table);
}

/**
 * @brief A handler function to understand the number of requests for each endpoint.
 *
 * @param filename The path of the file to be read.
 * @return int Returns `0` on success.
 */
static int handle_logs(char *filename)
{
  int logs[ENUM_LENGTH];
  logs[GET_ROOT] = count_word_matches(filename, "GET,ROOT");
  logs[GET_MOCK] = count_word_matches(filename, "GET,/mock");
  logs[PUT_MOCK] = count_word_matches(filename, "PUT,/mock");
  logs[DELETE_MOCK] = count_word_matches(filename, "DELETE,/mock");
  logs[POST_MOCK] = count_word_matches(filename, "POST,/mock");
  draw_table(logs);
  return 0;
}

/**
 * @brief Clears the server events log.
 *
 * @return int Returns `0` on success.
 */
static int clear_event_log(char *filename)
{
  char *buffer = "TIMESTAMP,METHOD,PATH\n";
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("Error: could not open file.\n");
    return 1;
  }
  fputs(buffer, fp);
  fclose(fp);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2 ||
    strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    return fprintf(stdout, APPLICATION_CLI_HELP_MSG, argv[0]);
  if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
    return fprintf(stdout, "%s v%s\n", argv[0], CLI_VERSION);
  if (strcmp(argv[1], "--list") == 0 || strcmp(argv[1], "-l") == 0)
    return handle_logs(EVENT_LOG_FILENAME);
  if (strcmp(argv[1], "--clear") != 0 || strcmp(argv[1], "-c") != 0)
    return clear_event_log(EVENT_LOG_FILENAME);
  fprintf(stderr, INVALID_OPTION_MSG);
  return -1;
}
