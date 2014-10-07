#ifndef RVM_TEST_H
#define RVM_TEST_H

#define COLOUR_RED      "\033[1;31m"
#define COLOUR_GREEN    "\033[1;32m"
#define COLOUR_END      "\033[0m"

#define COLOUR(r)       (r) ? COLOUR_GREEN : COLOUR_RED
#define SYMBOL(r)       (r) ? "✔" : "✖"

#define ASSERT(exp, e) \
    do { \
        if (!(exp)) { \
            *error = e; \
            return false; \
        } \
    } while (0)

bool rvm_test_app_file_assign_integer(TALLOC_CTX *ctx, char **error);
bool rvm_test_app_file_assign_float(TALLOC_CTX *ctx, char **error);
bool rvm_test_app_file_assign_string(TALLOC_CTX *ctx, char **error);
bool rvm_test_app_file_assign_string_empty(TALLOC_CTX *ctx, char **error);

bool rvm_test_ast_init_identifier(TALLOC_CTX *ctx, char **error);
bool rvm_test_ast_init_integer(TALLOC_CTX *ctx, char **error);
bool rvm_test_ast_init_float(TALLOC_CTX *ctx, char **error);
bool rvm_test_ast_init_other(TALLOC_CTX *ctx, char **error);
bool rvm_test_ast_append(TALLOC_CTX *ctx, char **error);

#endif
