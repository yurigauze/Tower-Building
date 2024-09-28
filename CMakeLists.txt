cmake_minimum_required(VERSION 3.10)
project(TestSpritesProject)

# Defina o diretório de includes para Google Test e Google Mock
include_directories(/usr/src/googletest/googletest/include)
include_directories(/usr/src/googletest/googlemock/include)

# Adicione o diretório de includes do SDL2
include_directories(/usr/include/SDL2)

# Diretórios de link para Google Test
link_directories(/usr/src/googletest/googletest/lib)

# Adicione o executável de teste, incluindo o arquivo de teste e o arquivo da classe Sprites
add_executable(test_sprites
    tests/test_sprites.cpp
    ../src/render/sprites/Sprites.cpp # Certifique-se de que o caminho para o Sprites.cpp está correto
)

# Vincule as bibliotecas necessárias
target_link_libraries(test_sprites
    gtest
    gmock
    gtest_main
    pthread
    SDL2
    SDL2_image # Adicione esta se você estiver usando SDL_image para carregar texturas
)
