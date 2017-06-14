#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "node.h"

void parse();

void cc_init_parser(char* code) {
  cc_init_lexer(code);
  parser = (Parser*)malloc(sizeof(Parser));
  parser->lexer = lexer;
  parser->debug = false;
}

void cc_parser_parse() {
  cc_lexer_lex();
  parse();
}

void cc_free_parser() {
  cc_free_lexer();
  free(parser);
}

// function:
// 	TYPE IDENTIFIER '(' ')' '{' expression '}'
// 	;
//
// expression:
// 	RETURN NUMBER ';'
// 	;

void parse() {
  cc_next_token();
}

void print_token(Token* token) {
  if (parser->debug == true) {
    if (token != NULL) {
      printf("- token->value: %s\n", token->value);
    } else {
      puts("Token is NULL.");
    }
  }
}
