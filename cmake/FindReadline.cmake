# - Try to find readline include dirs and libraries
#
# Usage of this module as follows:
#
# find_package(Readline)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
# Readline_ROOT_DIR Set this variable to the root installation of
# readline if the module has problems finding the
# proper installation path.
#
# Variables defined by this module:
#
# READLINE_FOUND System has readline, include and lib dirs found
# Readline_INCLUDE_DIR The readline include directories.
# Readline_LIBRARY The readline library.
find_path(READLINE_ROOT_DIR
    NAMES include/readline/readline.h)
find_path(READLINE_INCLUDE_DIRS
    NAMES readline/readline.h
    HINTS ${READLINE_ROOT_DIR}/include)
find_library(READLINE_LIBRARIES
    NAMES readline
    HINTS ${READLINE_ROOT_DIR}/lib)
if(READLINE_INCLUDE_DIRS AND READLINE_LIBRARIES AND Ncurses_LIBRARY)
    set(READLINE_FOUND TRUE)
else(READLINE_INCLUDE_DIRS AND READLINE_LIBRARIES AND Ncurses_LIBRARY)
    FIND_LIBRARY(READLINE_LIBRARIES NAMES readline)
    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(READLINE DEFAULT_MSG READLINE_INCLUDE_DIRS READLINE_LIBRARIES)
    MARK_AS_ADVANCED(READLINE_INCLUDE_DIRS READLINE_LIBRARIES)
endif(READLINE_INCLUDE_DIRS AND READLINE_LIBRARIES AND Ncurses_LIBRARY)
mark_as_advanced(
    READLINE_ROOT_DIR
    READLINE_INCLUDE_DIRS
    READLINE_LIBRARIES)
