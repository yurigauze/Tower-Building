#include <gmock/gmock.h>
#include "../src/render/IRenderer.h"

class MockRenderer : public IRenderer {
public:
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, setDrawColor, (int, int, int, int), (override));
    MOCK_METHOD(void, drawRect, (int, int, int, int), (override));
    MOCK_METHOD(void, drawLine, (int, int, int, int), (override));
    MOCK_METHOD(void, drawCircle, (int, int, int), (override));
    MOCK_METHOD(void, drawPoint, (int, int), (override));
    MOCK_METHOD(void, present, (), (override));
    MOCK_METHOD(bool, loadTexture, (const std::string&, const std::string&), (override));
    MOCK_METHOD(SDL_Texture*, getTexture, (const std::string&), (override));
    MOCK_METHOD(void, drawTexture, (const std::string&, int, int, SDL_Rect*), (override));
    MOCK_METHOD(void, destroyTexture, (SDL_Texture*), (override));
    MOCK_METHOD(bool, loadFont, (const std::string&, int), (override));
    MOCK_METHOD(void, drawText, (const std::string&, int, int, int, int, int, int), (override));
};
