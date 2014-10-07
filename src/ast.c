#include "robvm.h"
#include "ast.h"

/**
 * Create AST node
 */
rvm_ast_node_t *rvm_ast_init(TALLOC_CTX *ctx, unsigned int type, char *value) {
    rvm_ast_node_t *node = talloc(ctx, rvm_ast_node_t);
    if (!node) {
        return NULL;
    }

    node->value = talloc(node, rvm_value_t);
    if (!node) {
        return NULL;
    }

    node->type = type;
    node->next = NULL;
    node->children = NULL;

    switch (node->type) {
        case RVM_AST_IDENTIFIER:
            node->value->type = RVM_TYPE_IDENTIFIER;
            node->value->v.s = talloc_strdup(ctx, value);
            break;

        case RVM_AST_STRING:
            node->value->type = RVM_TYPE_STRING;
            node->value->v.s = talloc_strndup(ctx, value+1, strlen(value)-2);
            break;

        case RVM_AST_INTEGER:
            node->value->type = RVM_TYPE_INTEGER;
            node->value->v.i = atoi(value);
            break;

        case RVM_AST_FLOAT:
            node->value->type = RVM_TYPE_FLOAT;
            node->value->v.f = atof(value);
            break;
    }

    return node;
}

/**
 * Add child AST node
 */
void rvm_ast_append(rvm_ast_node_t *parent, rvm_ast_node_t *node) {
    if (parent->children == NULL) {
        parent->children = node;
    } else {
        rvm_ast_node_t *current = parent->children;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}
