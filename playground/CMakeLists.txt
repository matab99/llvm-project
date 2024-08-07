include(CMakeDependentOption)
include(GNUInstallDirs)

include_directories(SYSTEM ${LLVM_MAIN_SRC_DIR}/../clang/include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/tools/clang/include)

add_clang_tool(clangPlayground
    src/main.cpp
    src/test/LexerTest.cpp
)

clang_target_link_libraries(clangPlayground
    PRIVATE
    clangAST
    clangBasic
)