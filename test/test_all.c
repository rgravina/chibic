#include "tap.h"
#include "test_lexer.h"
#include "test_parser.h"

int main() {
  plan(NO_PLAN);
  cc_run_lexer_tests();
  cc_run_parser_tests();
  done_testing();
}
