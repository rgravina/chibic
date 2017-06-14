#include <stdio.h>
#include "parser.h"
#include "node.h"
#include "code.h"

int main() {
  printf("chibic\n");
  char* code = "int main() {return 0;}";
  cc_init_parser(code);
  cc_parser_parse();
  cc_generate_code(true);
  cc_free_parser();
  return 0;
}
