#include "robvm.h"
#include "ast.h"
#include "test.h"

/**
 * AST identifier initialisation tests
 */
bool rvm_test_ast_init_identifier(TALLOC_CTX *ctx, char **error) {

    // Test valid identifier token
    rvm_ast_node_t *node = rvm_ast_init(ctx, RVM_AST_IDENTIFIER, "test_ident1");
    ASSERT(node != NULL,
        "Node is NULL");
    ASSERT(node->next == NULL,
        "Node sibling is not NULL");
    ASSERT(node->children == NULL,
        "Node children is not NULL");
    ASSERT(node->type == RVM_AST_IDENTIFIER,
        "Node type is not identifier");
    ASSERT(node->value != NULL,
        "Node value is NULL");
    ASSERT(node->value->type == RVM_TYPE_IDENTIFIER,
        "Node value type is not string");
    ASSERT(strcmp(node->value->v.s, "test_ident1") == 0,
        "Node value is incorrect");

    return true;
}

/**
 * AST integer initialisation tests
 */
bool rvm_test_ast_init_integer(TALLOC_CTX *ctx, char **error) {

    // Test valid integer token
    rvm_ast_node_t *node = rvm_ast_init(ctx, RVM_AST_INTEGER, "4919");
    ASSERT(node != NULL,
        "Node is NULL");
    ASSERT(node->next == NULL,
        "Node sibling is not NULL");
    ASSERT(node->children == NULL,
        "Node children is not NULL");
    ASSERT(node->type == RVM_AST_INTEGER,
        "Node type is not integer");
    ASSERT(node->value != NULL,
        "Node value is NULL");
    ASSERT(node->value->type == RVM_TYPE_INTEGER,
        "Node value type is not integer");
    ASSERT(node->value->v.i == 4919,
        "Node value is incorrect");

    // Test invalid integer token
    rvm_ast_node_t *node2 = rvm_ast_init(ctx, RVM_AST_INTEGER, "INVALID");
    ASSERT(node2 != NULL,
        "Invalid node is NULL");
    ASSERT(node2->value != NULL,
        "Invalid node value is NULL");
    ASSERT(node2->value->type == RVM_TYPE_INTEGER,
        "Invalid node value type is not integer");
    ASSERT(node2->value->v.i == 0,
        "Invalid node value is incorrect");

    return true;
}

/**
 * AST float initialisation tests
 */
bool rvm_test_ast_init_float(TALLOC_CTX *ctx, char **error) {

    // Test valid integer token
    rvm_ast_node_t *node = rvm_ast_init(ctx, RVM_AST_FLOAT, "4919.419");
    ASSERT(node != NULL,
        "Node is NULL");
    ASSERT(node->next == NULL,
        "Node sibling is not NULL");
    ASSERT(node->children == NULL,
        "Node children is not NULL");
    ASSERT(node->type == RVM_AST_FLOAT,
        "Node type is not float");
    ASSERT(node->value != NULL,
        "Node value is NULL");
    ASSERT(node->value->type == RVM_TYPE_FLOAT,
        "Node value type is not float");
    ASSERT(node->value->v.f == 4919.419,
        "Node value is incorrect");

    // Test invalid integer token
    rvm_ast_node_t *node2 = rvm_ast_init(ctx, RVM_AST_FLOAT, "INVALID");
    ASSERT(node2 != NULL,
        "Invalid node is NULL");
    ASSERT(node2->value != NULL,
        "Invalid node value is NULL");
    ASSERT(node2->value->type == RVM_TYPE_FLOAT,
        "Invalid node value type is not float");
    ASSERT(node2->value->v.i == 0,
        "Invalid node value is incorrect");

    return true;
}

/**
 * AST other initialisation tests
 */
bool rvm_test_ast_init_other(TALLOC_CTX *ctx, char **error) {

    const unsigned long types[] = {
        RVM_AST_ROOT,
        RVM_AST_ASSIGN,
        RVM_AST_ADD,
        RVM_AST_SUBTRACT,
        RVM_AST_MULTIPLY,
        RVM_AST_DIVIDE,
    };

    const char *type_names[] = {
        "root",
        "assign",
        "add",
        "subtract",
        "multiply",
        "divide",
    };

    for (int i = 0; i < sizeof(types) / sizeof(types[0]); i++) {

        rvm_ast_node_t *node = rvm_ast_init(ctx, types[i], NULL);
        ASSERT(node != NULL,
            talloc_asprintf(ctx, "%s node is NULL", type_names[i]));
        ASSERT(node->next == NULL,
            talloc_asprintf(ctx, "%s node sibling is not NULL", type_names[i]));
        ASSERT(node->children == NULL,
            talloc_asprintf(ctx, "%s node children is not NULL", type_names[i]));
        ASSERT(node->type == types[i],
            talloc_asprintf(ctx, "%s node type is incorrect", type_names[i]));

    }

    return true;
}

/**
 * AST append tests
 */
bool rvm_test_ast_append(TALLOC_CTX *ctx, char **error) {

    rvm_ast_node_t *root = rvm_ast_init(ctx, RVM_AST_ROOT, NULL),
                   *child1 = rvm_ast_init(ctx, RVM_AST_IDENTIFIER, "id1"),
                   *child2 = rvm_ast_init(ctx, RVM_AST_IDENTIFIER, "id2");

    // Test appending first node
    rvm_ast_append(root, child1);
    ASSERT(root->children == child1,
        "Child node not appended to root");
    ASSERT(child1->next == NULL,
        "Child node not NULL terminated");

    // Test appending another node
    rvm_ast_append(root, child2);
    ASSERT(child1->next == child2,
        "Child node not appended to sibling");
    ASSERT(child2->next == NULL,
        "Child node list not NULL terminated");

    return true;
}
