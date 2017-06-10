#include "tap.h"
#include "lexer.h"

void check_token(int lineno, int start, TokenType type, char* value) {
  Token* token = cc_next_token();
  cmp_ok(token->lineno, "==", lineno);
  cmp_ok(token->start, "==", start);
  cmp_ok(token->type, "==", type);
  is(token->value, value);
}

void test_lexer_type() {
  char* code = "int";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, tTYPE, "int");
  cc_free_lexer();
}

void test_lexer_type_identifier() {
  char* code = "main";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, tIDENTIFIER, "main");
  cc_free_lexer();
}

void cc_run_lexer_tests() {
  test_lexer_type();
  test_lexer_type_identifier();
}
