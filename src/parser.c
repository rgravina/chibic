#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "node.h"

void parse();
void parse_function();
void parse_type();
void parse_identifier();
void parse_left_paren();
void parse_right_paren();
void parse_left_brace();
void parse_expression();
void parse_right_brace();
void parse_return();
void parse_integer();
void parse_colon();

void print_token(Token* token);

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
  cc_node_init(parser->debug);
  parse_function();
}

void parse_function() {
  parse_type();
  parse_identifier();
  parse_left_paren();
  parse_right_paren();
  parse_left_brace();
  parse_expression();
  parse_right_brace();
}

void parse_type() {
}

void parse_identifier() {
}

void parse_left_paren() {
}

void parse_right_paren() {
}

void parse_left_brace() {
}

void parse_expression() {
}

void parse_right_brace() {
  parse_return();
  parse_integer();
  parse_colon();
}

void parse_return() {

}

void parse_integer() {
  cc_node_add_node(nINTEGER);
  cc_node_commit();
}

void parse_colon() {

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
