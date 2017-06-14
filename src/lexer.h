#include <stdbool.h>

typedef enum tokenType {
  tNONE, tKEYWORD, tIDENTIFIER, tLPAREN, tRPAREN, tLBRACE, tRBRACE, tINTEGER, tSEMICOLON
} TokenType;

typedef struct token {
  char* value;
  TokenType type;
  unsigned long lineno;
  unsigned long start;
  unsigned long end;
  struct token* next;
  struct token* previous;
} Token;

typedef struct lexer {
  char* code;
  Token* head;
  Token* tail;
  TokenType curr_type;
  char curr_char;
  bool debug;
  bool in_token;
  unsigned long curr_pos;
  unsigned long num_tokens;
  unsigned long curr_lineno;
  unsigned long curr_start_pos;
  unsigned long curr_end_pos;
} Lexer;

// the primary lexer struct
Lexer* lexer;

// functions to direct the lexer
void cc_init_lexer(char* code);
void cc_free_lexer();
void cc_lexer_lex();
Token* cc_next_token();
Token* cc_curr_token();
Token* cc_previous_token();
