#include <stdbool.h>
#include "lexer.h"

typedef struct parser {
  Lexer* lexer;
  bool debug;
} Parser;

// the primary lexer struct
Parser* parser;

// functions to direct the parser
void cc_init_parser();
void cc_parser_parse();
void cc_free_parser();
