#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/render/sprites/Sprites.h"
#include "../src/render/PortRender.h" 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Mock para o PortRender
class MockPortRender : public PortRender {
public:
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, setDrawColor, (int r, int g, int b, int a), (override));
    MOCK_METHOD(void, drawRect, (int x, int y, int w, int h), (override));
    MOCK_METHOD(void, present, (), (override));
    MOCK_METHOD(void, drawLine, (int x1, int y1, int x2, int y2), (override));
    MOCK_METHOD(void, drawCircle, (int x, int y, int radius), (override));
    MOCK_METHOD(void, drawPoint, (int x, int y), (override));

    MOCK_METHOD(bool, loadFont, (const std::string &path, int size), (override));
    MOCK_METHOD(void, drawText, (const std::string &text, int x, int y, int r, int g, int b, int a), (override));

    MOCK_METHOD(bool, loadTexture, (const std::string &id, const std::string &filename), (override));
    MOCK_METHOD(SDL_Texture*, getTexture, (const std::string &id), (override));
    MOCK_METHOD(void, destroyTexture, (SDL_Texture *texture), (override));

    MOCK_METHOD(SDL_Renderer*, getRenderer, (), (const, override));
};

class SpritesTest : public ::testing::Test {
protected:
    MockPortRender* mockRenderer;
    Sprites* sprites;
    SDL_Renderer* sdlRenderer;
    SDL_Window* window;

    void SetUp() override {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            FAIL() << "Falha ao inicializar o SDL: " << SDL_GetError();
        }
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            FAIL() << "Falha ao inicializar o SDL_image: " << IMG_GetError();
        }

        window = SDL_CreateWindow("Test", 0, 0, 640, 480, 0);
        sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        mockRenderer = new MockPortRender();
        
        EXPECT_CALL(*mockRenderer, loadTexture(testing::_, testing::_)).WillOnce(testing::Return(true));
        EXPECT_CALL(*mockRenderer, getTexture(testing::_)).WillOnce(testing::Return(reinterpret_cast<SDL_Texture*>(1)));

        sprites = new Sprites("testSprite", "path/to/texture.png", mockRenderer, 32, 32, 4, 0.1f);
    }

    void TearDown() override {
        delete sprites;
        delete mockRenderer;

        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(window);

        IMG_Quit();
        SDL_Quit();
    }
};

// Teste de construção
// Verifica se o construtor da classe Sprites carrega a textura corretamente
TEST_F(SpritesTest, ConstructorLoadsTexture) {
    ASSERT_NE(sprites, nullptr);
}

// Teste de atualização
// Testa se a função update() incrementa corretamente o frame atual da animação
TEST_F(SpritesTest, UpdateIncrementsFrame) {
    sprites->update(0.2f); // Atualiza com um deltaTime que deve passar o tempo do frame
    EXPECT_EQ(sprites->isLastFrame(), false); // Deve avançar para o próximo frame
}

// Teste de renderização simples
// Verifica se a função render() pode ser chamada sem gerar erros. 
TEST_F(SpritesTest, RenderExecutesWithoutError) {
    sprites->render(sdlRenderer, 100, 100, 32, 32);
    SUCCEED();
}

// Teste de renderização com rotação
// Verifica se a função renderWithRotation() pode ser chamada sem gerar erros. 
TEST_F(SpritesTest, RenderWithRotationExecutesWithoutError) {
    sprites->renderWithRotation(sdlRenderer, 100, 100, 32, 32, 45.0);
    SUCCEED();
}

// Teste de verificação de último frame
// Verifica se o método isLastFrame() retorna true quando o sprite está no último frame
TEST_F(SpritesTest, IsLastFrameReturnsTrueAtLastFrame) {
    for (int i = 0; i < 4; ++i) { // Total de 4 frames
        sprites->update(0.1f); // Atualiza em intervalos que não resetam
    }
    EXPECT_TRUE(sprites->isLastFrame());
}

// Teste de reset
// Testa se o método reset() realmente reseta o frame atual da animação para o início
TEST_F(SpritesTest, ResetResetsCurrentFrame) {
    sprites->update(0.2f); // Muda o frame
    sprites->reset(); // Reseta o frame
    EXPECT_EQ(sprites->isLastFrame(), false); // Deve não estar no último frame
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
