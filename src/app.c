#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "robvm.h"
#include "app.h"
#include "parser.h"
#include "lexer.h"

extern int yyparse(rvm_ast_node_t *root);

/**
 * Create app
 */
rvm_app_t *rvm_app_init(void) {
    rvm_app_t *app = talloc(NULL, rvm_app_t);
    if (!app) {
        return NULL;
    }

    app->root = rvm_ast_init(app, RVM_AST_ROOT, NULL);
    if (!app->root) {
        talloc_free(app);
        return NULL;
    }

    app->vm = rvm_vm_init(app);
    if (!app->vm) {
        talloc_free(app);
        return NULL;
    }

    return app;
}

/**
 * Interactive
 */
bool rvm_app_interactive(rvm_app_t *app) {

    // Initialise readline history
    using_history();

    while(true) {
        // Read line
        char *line = readline(RVM_NAME "> ");
        if (line == NULL) {
            fprintf(stderr, "\n");
            break;

        // Ignore empty lines
        } else if (rvm_empty_string(line)) {
            continue;
        }

        // Add to history
        add_history(line);

        // Set bison input
        YY_BUFFER_STATE buffer;
        buffer = yy_scan_string(line);

        // Parse and build AST
        if (yyparse(app->root) != 0) {
            rvm_log(RVM_LOG_ERR, "Error parsing");

        // Execute AST
        } else if (!rvm_vm_execute(app->vm, app->root)) {
            rvm_log(RVM_LOG_ERR, "Error executing");
        }

        // Reset AST
        //talloc_free(app->root);
        app->root = rvm_ast_init(app, RVM_AST_ROOT, NULL);
        if (!app->root) {
            return false;
        }

        // Clean up buffer
        yy_delete_buffer(buffer);

    }

    return true;
}

/**
 * Run the provided input file
 */
bool rvm_app_file(rvm_app_t *app, char *filename) {

    // Open input file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        rvm_log(RVM_LOG_ERR, "Unable to open '%s'", filename);
        return false;
    }
    PDEBUG("Opened input file '%s'...", filename);

    // Set bison input file handle
    yyin = file;
    int r = yyparse(app->root);
    fclose(file);

    // Parse and build AST
    if (r != 0) {
        rvm_log(RVM_LOG_ERR, "Error parsing '%s'", filename);
        return false;

    // Execute AST
    } else if (!rvm_vm_execute(app->vm, app->root)) {
        rvm_log(RVM_LOG_ERR, "Error executing '%s'", filename);
        return false;
    }

    return true;
}

/**
 * Clean-up app
 */
void rvm_app_free(rvm_app_t *app) {
    talloc_free(app);
}
