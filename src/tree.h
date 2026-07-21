
// #define MAX_BRANCHES 64
//
// typedef struct TreeNode {
// 	struct TreeNode *parent;
// 	struct TreeNode *children[MAX_BRANCHES];
// } TreeNode;

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int line;
  int index;
} TokenPosition;

typedef struct TreeNode {
    TokenPosition start_paren;
    TokenPosition close_paren;
    struct TreeNode* parent;
    struct TreeNode** children;
    int child_count;
    int capacity;
} TreeNode;

TreeNode* create_node() {
    // Allocate memory
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) return NULL;

    new_node->start_paren = (TokenPosition){ -1, -1 };
    new_node->close_paren = (TokenPosition){ -1, -1 };

    new_node->children = NULL;
    new_node->child_count = 0;
    new_node->capacity = 0;
    return new_node;
}

void free_tree(TreeNode* root) {
    if (!root) {
        printf("Missing argument for free_tree.\n");
        return;
    }

    // Free all children first
    for (int i = 0; i < root->child_count; i++) {
        free_tree(root->children[i]);
    }

    // Free the treenodes data and itself
    free(root->children);
    free(root);
}

void add_child(TreeNode* parent, TreeNode* child) {
    if (!parent || !child) {
        printf("Missing argument for add_child.\n");
        return;
    }

    // When the array is full, expand its size
    if (parent->child_count >= parent->capacity) {
        parent->capacity = parent->capacity == 0 ? 2 : parent->capacity * 2;
        TreeNode** temp = (TreeNode**)realloc(parent->children, parent->capacity * sizeof(TreeNode*));
        if (!temp) {
            fprintf(stderr, "Error: Could not allocate memory.\n");
            return;
        }
        parent->children = temp;
    }

    // Set parent of child node
    child->parent = parent;

    // Insert child, assign id, and increment
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

void print_tree(TreeNode* root, int depth) {
    if (!root) return;

    // Indention
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("|-- %d-%d\n", root->start_paren.index, root->close_paren.index);

    // Recursive printing
    for (int i = 0; i < root->child_count; i++) {
        print_tree(root->children[i], depth + 1);
    }
}
