#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/render/SDLRenderer.h"
#include "MockRenderer.h"

TEST(SDLRendererTest, Clear) {
    MockRenderer mockRenderer;
    SDLRenderer renderer(&mockRenderer);

    EXPECT_CALL(mockRenderer, clear()).Times(1);

    renderer.clear();
}

TEST(SDLRendererTest, SetDrawColor) {
    MockRenderer mockRenderer;
    SDLRenderer renderer(&mockRenderer);

    EXPECT_CALL(mockRenderer, setDrawColor(255, 0, 0, 255)).Times(1);

    renderer.setDrawColor(255, 0, 0, 255);
}

TEST(SDLRendererTest, DrawRect) {
    MockRenderer mockRenderer;
    SDLRenderer renderer(&mockRenderer);

    EXPECT_CALL(mockRenderer, drawRect(10, 10, 100, 50)).Times(1);

    renderer.drawRect(10, 10, 100, 50);
}

TEST(SDLRendererTest, LoadTexture) {
    MockRenderer mockRenderer;
    SDLRenderer renderer(&mockRenderer);
    std::string id = "test_texture";
    std::string filePath = "path/to/test_texture.png";

    EXPECT_CALL(mockRenderer, loadTexture(id, filePath)).WillOnce(testing::Return(true));

    EXPECT_TRUE(renderer.loadTexture(id, filePath));
}

// Continue adicionando testes para outros métodos...

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
