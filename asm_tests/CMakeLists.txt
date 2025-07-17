find_program(LIT_COMMAND lit)

if(NOT LIT_COMMAND)
    message(STATUS "LIT not found - install with: pip install lit")
    return()
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py.in
    ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
    @ONLY
)

add_test(
    NAME asm-tests
    COMMAND ${LIT_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
