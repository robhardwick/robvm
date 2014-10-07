#include <time.h>
#include "robvm.h"
#include "test.h"

typedef struct {
    const char *name;
    bool (*func)(TALLOC_CTX *ctx, char **error);
} rvm_test_t;

/**
 * Tests
 */
static rvm_test_t rvm_tests[] = {
    {.name = "App file assign integer", .func = rvm_test_app_file_assign_integer},
    {.name = "App file assign float", .func = rvm_test_app_file_assign_float},
    {.name = "App file assign string", .func = rvm_test_app_file_assign_string},
    {.name = "App file assign empty string", .func = rvm_test_app_file_assign_string_empty},
    {.name = "AST initialise identifier", .func = rvm_test_ast_init_identifier},
    {.name = "AST initialise integer", .func = rvm_test_ast_init_integer},
    {.name = "AST initialise float", .func = rvm_test_ast_init_float},
    {.name = "AST initialise other", .func = rvm_test_ast_init_other},
    {.name = "AST append node", .func = rvm_test_ast_append},
};

/**
 * Test Runner
 */
int main(int argc, char **argv) {
    bool result = true;
    char *error = NULL;
    unsigned int num_tests = sizeof(rvm_tests) / sizeof(rvm_tests[0]);

    fputs("Running robvm tests...\n", stderr);

    clock_t start = clock();
    for (unsigned int i = 0; i < num_tests; i++) {

        // Use new talloc context for each test
        TALLOC_CTX *ctx = talloc_init("test");

        // Run test
        bool r = rvm_tests[i].func(ctx, &error);

        // Print result
        fprintf(stderr, "\t%s%s  %s" COLOUR_END "\n",
            COLOUR(r),
            SYMBOL(r),
            rvm_tests[i].name
        );

        if (!r) {
            // Print error
            fprintf(stderr, "\t\t%s%s" COLOUR_END "\n",
                COLOUR(r),
                error
            );
            result = false;
        }

        talloc_free(ctx);

    }

    // Print summary
    fprintf(stderr, "\n%s%s  %u tests run in %0.2fs" COLOUR_END "\n",
        COLOUR(result),
        SYMBOL(result),
        num_tests,
        (double)(clock() - start) / CLOCKS_PER_SEC
    );

    return (result) ? EXIT_SUCCESS : EXIT_FAILURE;
}
