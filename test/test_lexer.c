#include "tap.h"
#include "lexer.h"

void check_token(int lineno, int start, int end, TokenType type, char* value) {
  Token* token = cc_next_token();
  cmp_ok(token->lineno, "==", lineno);
  cmp_ok(token->start, "==", start);
  cmp_ok(token->end, "==", end);
  cmp_ok(token->type, "==", type);
  is(token->value, value);
}

void test_lexer_int() {
  char* code = "int";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, 2, tKEYWORD, "int");
  cc_free_lexer();
}

void test_lexer_return() {
  char* code = "return";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, 5, tKEYWORD, "return");
  cc_free_lexer();
}

void test_lexer_identifier() {
  char* code = "main";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, 3, tIDENTIFIER, "main");
  cc_free_lexer();
}

void test_lexer_int_and_identifier() {
  char* code = "int main";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 2);
  check_token(1, 0, 2, tKEYWORD, "int");
  check_token(1, 4, 7, tIDENTIFIER, "main");
  cc_free_lexer();
}

void test_lexer_parens() {
  char* code = "()";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 2);
  check_token(1, 0, 0, tLPAREN, "(");
  check_token(1, 1, 1, tRPAREN, ")");
  cc_free_lexer();
}

void test_lexer_braces() {
  char* code = "{}";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 2);
  check_token(1, 0, 0, tLBRACE, "{");
  check_token(1, 1, 1, tRBRACE, "}");
  cc_free_lexer();
}

void cc_run_lexer_tests() {
  test_lexer_int();
  test_lexer_identifier();
  test_lexer_int_and_identifier();
  test_lexer_parens();
  test_lexer_braces();
  test_lexer_return();
}
