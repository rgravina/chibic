#include <stdio.h>
#include <string.h>
#include "tap.h"
#include "parser.h"
#include "node.h"

void test_parser() {
  char* code = "int main() {return 0;}";
  cc_init_parser(code);
  parser->debug = true;
  cc_parser_parse();
  cc_free_parser();
}

void cc_run_parser_tests() {
  test_parser();
}
