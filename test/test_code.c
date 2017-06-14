#include <stdio.h>
#include <string.h>
#include "tap.h"
#include "parser.h"
#include "code.h"

void test_code() {
  char* code = "int main() {return 0;}";
  cc_init_parser(code);
  cc_parser_parse();
  cc_generate_code();
  cc_free_parser();
}

void cc_run_code_tests() {
  test_code();
}
