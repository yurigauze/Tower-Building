#include "Sprite.h"
#include <vector>

class Animation {
public:
    void addFrame(const Sprite& frame);
    const Sprite& getFrame(int index) const;
    size_t getFrameCount() const;

private:
    std::vector<Sprite> frames;
};
