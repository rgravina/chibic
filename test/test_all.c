#include "tap.h"
#include "test_lexer.h"

int main() {
  plan(NO_PLAN);
  cc_run_lexer_tests();
  done_testing();
}
