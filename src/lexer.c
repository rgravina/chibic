#include <stdlib.h>
#include "lexer.h"

void cc_init_lexer(char* code) {
  lexer = (Lexer*)malloc(sizeof(Lexer));
  lexer->code = code;
}

void cc_free_lexer() {
  free(lexer);
}

void cc_lexer_lex() {
}
