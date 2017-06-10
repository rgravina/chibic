typedef struct lexer {
  char* code;
} Lexer;

// the primary lexer struct
Lexer* lexer;

// functions to direct the lexer
void cc_init_lexer(char* code);
void cc_free_lexer();
void cc_lexer_lex();
