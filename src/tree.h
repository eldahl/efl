
// #define MAX_BRANCHES 64
//
// typedef struct TreeNode {
// 	struct TreeNode *parent;
// 	struct TreeNode *children[MAX_BRANCHES];
// } TreeNode;

#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// OPERATOR TYPE CONSTANTS
const int OPERATOR_TYPE_ADDITION = 0;
const int OPERATOR_TYPE_SUBTRACT = 1;
const int OPERATOR_TYPE_MULTIPLY = 2;
const int OPERATOR_TYPE_DIVISION = 3;

// STATEMENT TYPE CONSTANTS
const int STATEMENT_TYPE_OPERATOR = 0;
const int STATEMENT_TYPE_KEYWORD = 1;
const int STATEMENT_TYPE_FUNCTION = 2;

typedef struct {
    int statement_type;
    int statement_sub_type;
    char* statement_identifier;
} Statement;

typedef struct {
    int line;
    int index;
} TokenPosition;

// ARGUMENT TYPE CONSTANTS
const int ARGUMENT_TYPE_NUMBER = 0;
const int ARGUMENT_TYPE_STRING = 1;
const int ARGUMENT_TYPE_FUNCTION = 2;

typedef struct {
    int argument_type;
    char* argument_data;
    char* argument_identifier;
} Argument;

typedef struct TreeNode {
    TokenPosition start_paren;
    TokenPosition close_paren;
    Statement statement;
    Argument arg_lhs;
    Argument arg_rhs;
    struct TreeNode* parent;
    struct TreeNode** children;
    int child_count;
    int capacity;
} TreeNode;

char* argument_as_number(int _number) {
    char* number = malloc(sizeof(int));
    if (number == NULL) {
        printf("failed to allocate memory for argument as number.\n");
        assert(number != NULL);
        return NULL;
    }
    *number = _number;
    return number;
}

char* argument_as_string(char* _char_array, int _char_array_size) {
    char* string = malloc(_char_array_size + 1);
    if (string == NULL) {
        printf("failed to allocate memory for argument as number.\n");
        assert(string != NULL);
        return NULL;
    }
    memcpy(string, _char_array, _char_array_size);
    string[_char_array_size] = '\0';
    return string;
}

TreeNode* create_node() {
    // Allocate memory
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!new_node) return NULL;

    new_node->start_paren = (TokenPosition){ -1, -1 };
    new_node->close_paren = (TokenPosition){ -1, -1 };

    new_node->statement = (Statement) { -1, -1, NULL};

    new_node->arg_lhs = (Argument) { -1, NULL, NULL};
    new_node->arg_rhs = (Argument) { -1, NULL, NULL};

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
    
    // Arguments
    free(root->arg_lhs.argument_data);
    free(root->arg_rhs.argument_data);

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
    printf("|-- %d-%d | %s - %s %s\n", root->start_paren.index, root->close_paren.index, root->statement.statement_identifier, root->arg_lhs.argument_identifier, root->arg_rhs.argument_identifier);

    // Recursive printing
    for (int i = 0; i < root->child_count; i++) {
        print_tree(root->children[i], depth + 1);
    }
}
