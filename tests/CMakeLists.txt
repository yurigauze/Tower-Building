# CMakeLists.txt em tests/

enable_testing()

# Adicione seu executável de teste
add_executable(test_sprites test_sprites.cpp)

# Vincule o Google Test e GMock
target_link_libraries(test_sprites GTest::GTest GTest::Main seu_projeto_lib)  # substitua 'seu_projeto_lib' pelo nome correto da sua biblioteca
