#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"

static const char *TypeString[] = {
  "nINTEGER"
};

// for adding to before we know the production was matched.
static Node* tempNodeRoot;
static Node* tempNodeTail;

void cc_node_init(bool debug) {
  tree = (NodeTree*)malloc(sizeof(NodeTree));
  tree->debug = debug;
  tree->root = NULL;
  tree->tail = NULL;
  tempNodeRoot = NULL;
  tempNodeTail = NULL;
}

void cc_node_add_node(NodeType type, Token* token) {
  // TODO: implement this properly. For now just replacing the old node.
  Node* node = (Node*)malloc(sizeof(Node));
  node->type = type;
  node->token = token;
  node->next = NULL;
  if (tempNodeRoot == NULL) {
    tempNodeRoot = tempNodeTail = node;
  } else {
    tempNodeTail->next = node;
    tempNodeTail = node;
  }
  if (tree->debug) {
    printf("adding node: %s\n", TypeString[type]);
    printf("      value: %s\n", node->token->value);
  }
}

void cc_node_commit() {
  // point the tail of the real node tree to the temp tree
  if (tempNodeRoot == NULL) {
    return;
  }
  if (tree->debug) {
    puts("committing nodes...");
  }
  if (tree->root == NULL) {
    tree->root = tree->tail = tempNodeRoot;
  } else {
    Node* node = tree->tail;
    node->next = tempNodeRoot;
    tree->tail = tempNodeRoot;
  }
  tempNodeRoot = tempNodeTail = NULL;
}
