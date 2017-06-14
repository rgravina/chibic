#include <stdbool.h>

typedef enum nodeType {nFUNCTION, nEXPRESSION} NodeType;
typedef struct node {
  NodeType type;
  struct node* next;
} Node;

typedef struct nodeTree {
  bool debug;
  Node* root;
  Node* tail;
} NodeTree;

// node root
NodeTree* tree;
