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
 * @brief A helper function to render table lines in the CLI.
 *
 * @param table The table to render.
 * @param logs The logs to get info from.
 * @param e_req The request type to filter.
 * @param method The HTTP method to display.
 * @param path The url PATH to display.
 * @param msg The about message.
 */
static int table_render_line(
  ft_table_t *table,
  int *logs,
  t_req_type e_req,
  char *method,
  char *path,
  char *msg) {
  char tmp[10];

  if (logs[e_req]) {
    sprintf(tmp, "%2d", logs[e_req]);
    ft_write_ln(table, method, path, tmp, msg);
    return 1;
  }
  return 0;
}

/**
 * @brief Generates a table with the server events log.
 *
 * @param table The table reference to populate.
 * @param logs The logs counted by the server.
 */
static void populate_table(ft_table_t *table, int *logs) {
  int nlines = 0;
  ft_write_ln(table, "HTTP Method", "PATH", "Requests", "About");

  nlines += table_render_line(table, logs, GET_ROOT, "GET", "/", "GET a random quote");
  nlines += table_render_line(table, logs, GET_API, "GET", "/api", "GET a random quote in JSON format");
  nlines += table_render_line(table, logs, GET_MOCK, "GET", "/mock", "GET information about /mock");
  nlines += table_render_line(table, logs, POST_MOCK, "POST", "/mock", "POST an update to /mock");
  nlines += table_render_line(table, logs, PUT_MOCK, "PUT", "/mock", "PUT an update to /mock");
  nlines += table_render_line(table, logs, DELETE_MOCK, "DELETE", "/mock", "DELETE data from /mock");

  if (!nlines) {
    ft_write_ln(table, "None", "None", "None", "None");
  }

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
static int handle_list(char *filename)
{
  int logs[ENUM_LENGTH];
  logs[GET_ROOT] = count_word_matches(filename, "GET,ROOT");
  logs[GET_API] = count_word_matches(filename, "GET,/api");
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
  fprintf(stdout, "Clearing server events log...\n");
  return 0;
}

static int handle_log_print(ft_table_t *table, char *filename)
{
    FILE *fp;
    char *args[MAX_LENGTH];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(filename, "r")) == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
      args[0] = strtok(line, ",");
      args[1] = strtok(NULL, ",");
      args[2] = strtok(NULL, "\n");
      ft_write_ln(table, args[0], args[1], args[2]);
    }
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

static int handle_logs(char *filename) {
  ft_table_t *table = ft_create_table();
  prepare_table_styles(table);
  handle_log_print(table, filename);
  ft_set_cell_prop(
    table, FT_ANY_ROW, FT_ANY_COLUMN,
    FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER
  );
  printf("%s\n", ft_to_string(table));
  ft_destroy_table(table);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2 ||
      strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
    return fprintf(stdout, APPLICATION_CLI_HELP_MSG, argv[0]);
  if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
    return fprintf(stdout, "%s v%s\n", argv[0], CLI_VERSION);
  if (strcmp(argv[1], "--list") == 0 || strcmp(argv[1], "-l") == 0)
    return handle_list(EVENT_LOG_FILENAME);
  if (strcmp(argv[1], "--logs") == 0 || strcmp(argv[1], "-o") == 0)
    return handle_logs(EVENT_LOG_FILENAME);
  if (strcmp(argv[1], "--clear") == 0 || strcmp(argv[1], "-c") == 0)
    return clear_event_log(EVENT_LOG_FILENAME);
  if (strcmp(argv[1], "--show") == 0 || strcmp(argv[1], "-s") == 0 ||
      strcmp(argv[1], "--endpoints") == 0 || strcmp(argv[1], "-e") == 0)
    return fprintf(stdout, AVAILABLE_ENDPOINTS_MSG);
  fprintf(stderr, INVALID_OPTION_MSG);
  return -1;
}
