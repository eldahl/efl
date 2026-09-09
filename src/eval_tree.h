#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

typedef struct EvalTreeNode {
  Statement statement;
  Argument arg_lhs;
  Argument arg_rhs;
  Argument result;
  //EvalErr error;
  struct EvalTreeNode *parent;
  struct EvalTreeNode **children;
  int child_count;
  int capacity;
} EvalTreeNode;

EvalTreeNode *et_create_node() {
  // Allocate memory
  EvalTreeNode *new_node = (EvalTreeNode *)malloc(sizeof(EvalTreeNode));
  if (!new_node)
    return NULL;

  new_node->statement = (Statement){-1, -1, NULL};

  new_node->arg_lhs = (Argument){-1, NULL, NULL};
  new_node->arg_rhs = (Argument){-1, NULL, NULL};

  new_node->result = (Argument){-1, NULL, NULL};

  new_node->children = NULL;
  new_node->child_count = 0;
  new_node->capacity = 0;
  return new_node;
}

void et_free_tree(EvalTreeNode *root) {
  if (!root) {
    printf("Missing argument for free_tree.\n");
    return;
  }

  // Free all children first
  for (int i = 0; i < root->child_count; i++) {
    et_free_tree(root->children[i]);
  }

  // Free the treenodes data and itself
  free(root->children);

  free(root->result.argument_data);

  free(root);
}

void et_add_child(EvalTreeNode *parent, EvalTreeNode *child) {
  if (!parent || !child) {
    printf("Missing argument for add_child.\n");
    return;
  }

  // When the array is full, expand its size
  if (parent->child_count >= parent->capacity) {
    int newCapacity = parent->capacity == 0 ? 2 : parent->capacity * 2;
    EvalTreeNode **temp = (EvalTreeNode **)realloc(
        parent->children, newCapacity * sizeof(EvalTreeNode *));
    if (!temp) {
      fprintf(stderr, "Error: Could not allocate memory.\n");
      return;
    }
    parent->capacity = newCapacity;
    parent->children = temp;
  }

  // Set parent of child node
  child->parent = parent;

  // Insert child, assign id, and increment
  parent->children[parent->child_count] = child;
  parent->child_count++;
}

void et_print_tree(EvalTreeNode *root, int depth) {
  if (!root)
    return;

  // Indention
  for (int i = 0; i < depth; i++) {
    printf("  ");
  }
  printf("|%s - %s %s\n", root->statement.statement_identifier,
         root->arg_lhs.argument_identifier, root->arg_rhs.argument_identifier);

  // Recursive printing
  for (int i = 0; i < root->child_count; i++) {
    et_print_tree(root->children[i], depth + 1);
  }
}
