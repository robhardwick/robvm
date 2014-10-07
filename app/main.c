#include "robvm.h"

/**
 * Application entry
 */
int main(int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "usage: %s [infile]\n", argv[0]);
        return EXIT_FAILURE;
    }

    bool r = false;
    rvm_app_t *app = rvm_app_init();
    if (!app) {
        rvm_log(RVM_LOG_ERR, "Unable to initialise app object");

    } else if (argc == 2) {
        r = rvm_app_file(app, argv[1]);

    } else {
        r = rvm_app_interactive(app);
    }

    rvm_app_free(app);
    return (r) ? EXIT_SUCCESS : EXIT_FAILURE;
}
