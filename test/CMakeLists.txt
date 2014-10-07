file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

add_executable(rvm-test
    test.c
    test_app.c
    test_ast.c
)

target_link_libraries(rvm-test librobvm)
