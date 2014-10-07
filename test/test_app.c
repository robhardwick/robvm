#include "robvm.h"
#include "app.h"
#include "ast.h"
#include "test.h"

/**
 * App file assign integer
 */
bool rvm_test_app_file_assign_integer(TALLOC_CTX *ctx, char **error) {

    rvm_app_t *app = rvm_app_init();
    ASSERT(app != NULL,
        "App is NULL");

    bool r = rvm_app_file(app, "data/assign-integer.rvm");
    ASSERT(r == true,
        "Parsing/execution failed");

    ASSERT(app->root->children->type == RVM_AST_ASSIGN,
        "First AST node is not assign");
    ASSERT(app->root->children->children->type == RVM_AST_IDENTIFIER,
        "Assign first AST node is not identifier");
    ASSERT(strcmp(app->root->children->children->value->v.s, "test_ident1") == 0,
        "Assign identifier is incorrect");
    ASSERT(app->root->children->children->next->type == RVM_AST_INTEGER,
        "Assign second AST node is not integer");
    ASSERT(app->root->children->children->next->value->v.i == 100,
        "Assign value is incorrect");

    rvm_app_free(app);

    return true;
}

/**
 * App file assign float
 */
bool rvm_test_app_file_assign_float(TALLOC_CTX *ctx, char **error) {

    rvm_app_t *app = rvm_app_init();
    ASSERT(app != NULL,
        "App is NULL");

    bool r = rvm_app_file(app, "data/assign-float.rvm");
    ASSERT(r == true,
        "Parsing/execution failed");

    ASSERT(app->root->children->type == RVM_AST_ASSIGN,
        "First AST node is not assign");
    ASSERT(app->root->children->children->type == RVM_AST_IDENTIFIER,
        "Assign first AST node is not identifier");
    ASSERT(strcmp(app->root->children->children->value->v.s, "test_ident2") == 0,
        "Assign identifier is incorrect");
    ASSERT(app->root->children->children->next->type == RVM_AST_FLOAT,
        "Assign second AST node is not integer");
    ASSERT(app->root->children->children->next->value->v.f == 4919.419,
        "Assign value is incorrect");

    rvm_app_free(app);

    return true;
}

/**
 * App file assign string
 */
bool rvm_test_app_file_assign_string(TALLOC_CTX *ctx, char **error) {

    rvm_app_t *app = rvm_app_init();
    ASSERT(app != NULL,
        "App is NULL");

    bool r = rvm_app_file(app, "data/assign-string.rvm");
    ASSERT(r == true,
        "Parsing/execution failed");

    ASSERT(app->root->children->type == RVM_AST_ASSIGN,
        "First AST node is not assign");
    ASSERT(app->root->children->children->type == RVM_AST_IDENTIFIER,
        "Assign first AST node is not identifier");
    ASSERT(strcmp(app->root->children->children->value->v.s, "test_ident3") == 0,
        "Assign identifier is incorrect");
    ASSERT(app->root->children->children->next->type == RVM_AST_STRING,
        "Assign second AST node is not integer");
    ASSERT(strcmp(app->root->children->children->next->value->v.s, "test string 1234!?!?") == 0,
        "Assign value is incorrect");

    rvm_app_free(app);

    return true;
}

/**
 * App file assign empty string
 */
bool rvm_test_app_file_assign_string_empty(TALLOC_CTX *ctx, char **error) {

    rvm_app_t *app = rvm_app_init();
    ASSERT(app != NULL,
        "App is NULL");

    bool r = rvm_app_file(app, "data/assign-string-empty.rvm");
    ASSERT(r == true,
        "Parsing/execution failed");

    ASSERT(app->root->children->type == RVM_AST_ASSIGN,
        "First AST node is not assign");
    ASSERT(app->root->children->children->type == RVM_AST_IDENTIFIER,
        "Assign first AST node is not identifier");
    ASSERT(strcmp(app->root->children->children->value->v.s, "test_ident4") == 0,
        "Assign identifier is incorrect");
    ASSERT(app->root->children->children->next->type == RVM_AST_STRING,
        "Assign second AST node is not integer");
    ASSERT(strlen(app->root->children->children->next->value->v.s) == 0,
        "Assign value is incorrect");

    rvm_app_free(app);

    return true;
}
