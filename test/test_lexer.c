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

void test_lexer_integer() {
  char* code = "123";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, 2, tINTEGER, "123");
  cc_free_lexer();
}

void test_lexer_semicolon() {
  char* code = ";";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 1);
  check_token(1, 0, 0, tSEMICOLON, ";");
  cc_free_lexer();
}

void test_lexer_simple_program() {
  char* code = "int main() {return 0;}";
  cc_init_lexer(code);
  cc_lexer_lex();
  ok(lexer->num_tokens == 9);
  check_token(1, 0, 2, tKEYWORD, "int");
  check_token(1, 4, 7, tIDENTIFIER, "main");
  check_token(1, 8, 8, tLPAREN, "(");
  check_token(1, 9, 9, tRPAREN, ")");
  check_token(1, 11, 11, tLBRACE, "{");
  check_token(1, 12, 17, tKEYWORD, "return");
  check_token(1, 19, 19, tINTEGER, "0");
  check_token(1, 20, 20, tSEMICOLON, ";");
  check_token(1, 21, 21, tRBRACE, "}");
  cc_free_lexer();
}

void cc_run_lexer_tests() {
  test_lexer_int();
  test_lexer_identifier();
  test_lexer_int_and_identifier();
  test_lexer_parens();
  test_lexer_braces();
  test_lexer_return();
  test_lexer_integer();
  test_lexer_semicolon();
  test_lexer_simple_program();
}
