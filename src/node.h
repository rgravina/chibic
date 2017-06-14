#include <stdbool.h>
#include "lexer.h"
#ifndef __NODE_H__
#define __NODE_H__

typedef enum nodeType {nINTEGER} NodeType;
typedef struct node {
  NodeType type;
  Token* token;
  struct node* next;
} Node;

typedef struct nodeTree {
  bool debug;
  Node* root;
  Node* tail;
} NodeTree;

// node root
NodeTree* tree;

void cc_node_init(bool debug);
void cc_node_add_node(NodeType type, Token* token);
void cc_node_commit();
void cc_node_print_tree();

#endif
