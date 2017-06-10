#include "tap.h"
#include "lexer.h"

void test_lexer_main() {
  char* code = "int main() {\n  return 0;\n}";
  cc_init_lexer(code);
  cc_lexer_lex();
  cc_free_lexer();
}

void cc_run_lexer_tests() {
  test_lexer_main();
}
