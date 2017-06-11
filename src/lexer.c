#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// lexer movement/inspection
bool should_abort_now();
char peek();
void pushback();

// token inspection
static void print_token(Token* token);
bool valid_identifier_char();
bool is_keyword(Token* token);

// token creation and processing
Token* new_token();
void add_token();
void add_single_character_token(TokenType type);
void process_token();
void advance_token();
void find_next_token();
void start_token(TokenType type);

/*
 * Lexer lifecyle functions
 */

// used for iterating through the tokens from outside
static bool started_walking;
static Token* curr_token;

void cc_init_lexer(char* code) {
  lexer = (Lexer*)malloc(sizeof(Lexer));
  lexer->debug = false;
  lexer->code = code;
  lexer->head = NULL;
  lexer->tail = NULL;
  lexer->in_token = false;
  lexer->num_tokens = 0;
  lexer->curr_lineno = 1;
  lexer->curr_pos = 0;
  lexer->curr_start_pos = 0;
  lexer->curr_end_pos = 0;
  started_walking = false;
}

void cc_free_lexer() {
  Token* token = lexer->head;
  while (token != NULL) {
    Token* temp = token;
    token = token->next;
    free(temp->value);
    free(temp);
  }
  free(lexer);
  curr_token = NULL;
}

/*
 * Lexer movement
 */

Token* cc_next_token() {
  if (curr_token == NULL && !started_walking) {
    curr_token = lexer->head;
    started_walking = true;
  } else {
    curr_token = curr_token->next;
  }
  return curr_token;
}

/*
 * Lexing
 */

void cc_lexer_lex() {
  while (lexer->curr_pos < strlen(lexer->code)) {
    lexer->curr_char = lexer->code[lexer->curr_pos];
    if (should_abort_now()) {
      break;
    }
    if (lexer->in_token == true) {
      process_token();
    } else {
      find_next_token();
    }
    lexer->curr_pos++;
  }
  // add the final token if there is one
  if (lexer->in_token == true) {
    add_token();
  }
}

bool should_abort_now() {
  switch(lexer->curr_char) {
    case '\0':    // NULL
    case '\004':  // ^D
    case '\032':  // ^Z
    case -1:      // end of script
      return true;
    default:
      return false;
  }
}

char peek() {
  return lexer->code[lexer->curr_pos+1];
}

void pushback() {
  lexer->in_token = false;
  lexer->curr_type = tNONE;
  lexer->curr_pos--;
}

void process_token() {
  switch(lexer->curr_type) {
    case tIDENTIFIER:
      if (!valid_identifier_char()) {
        add_token();
      } else {
        advance_token();
      }
      break;
    default:
      break;
  }
}

void find_next_token() {
  switch(lexer->curr_char) {
    case ' ': case '\t': case '\f': case '\r': case '\13':
      break;
    case '(':
      add_single_character_token(tLPAREN);
      break;
    case ')':
      add_single_character_token(tRPAREN);
      break;
    case '{':
      add_single_character_token(tLBRACE);
      break;
    case '}':
      add_single_character_token(tRBRACE);
      break;
    default:
      if (valid_identifier_char()) {
        start_token(tIDENTIFIER);
      }
  }
}

bool valid_identifier_char() {
  return isalpha(lexer->curr_char);
}

void start_token(TokenType type) {
  lexer->curr_type = type;
  lexer->curr_start_pos = lexer->curr_end_pos = lexer->curr_pos;
  lexer->in_token = true;
}

void advance_token() {
  lexer->curr_end_pos++;
}

void add_single_character_token(TokenType type) {
  start_token(type);
  add_token();
}

void add_token() {
  Token* token = new_token();
  if (lexer->debug) {
    print_token(token);
  }
  lexer->in_token = false;
  lexer->curr_type = tNONE;
  lexer->curr_start_pos = lexer->curr_pos;
  if (lexer->head == NULL) {
    lexer->head = lexer->tail = token;
  } else {
    lexer->tail->next = token;
    token->previous = lexer->tail->next;
    lexer->tail = token;
  }
  lexer->num_tokens++;
}

Token* new_token() {
  Token* token = (Token*)malloc(sizeof(Token));
  token->start = lexer->curr_start_pos;
  token->end = lexer->curr_end_pos;
  token->lineno = lexer->curr_lineno;
  token->next = NULL;
  token->previous = NULL;
  int token_length = lexer->curr_end_pos - lexer->curr_start_pos+1;
  token->value = (char *)malloc(sizeof(char) * token_length+1);
  token->value[token_length] = 0;
  strncpy(token->value, lexer->code+lexer->curr_start_pos, token_length);
  token->type = lexer->curr_type;
  if (token->type == tIDENTIFIER && is_keyword(token)) {
    token->type = tKEYWORD;
  }
  return token;
}

static const char *TypeString[] = {
  "None", "Keyword", "Identifier", "Left Paren", "Right Paren", "Left Brace", "Right Brace"
};

#define NUM_KEYWORDS 1
static char* KEYWORDS[NUM_KEYWORDS] = {"int", "return"};

bool is_keyword(Token* token) {
  char* value = token->value;
  for(int i = 0; i < NUM_KEYWORDS; i++) {
    if (strcmp(value, KEYWORDS[i]) == 0) {
      return true;
    }
  }
  return false;
}

static void print_token(Token* token) {
  printf("-- token %s '%s' line: %lu, start: %lu, end: %lu\n", TypeString[token->type], token->value, token->lineno, token->start, token->end);
}
