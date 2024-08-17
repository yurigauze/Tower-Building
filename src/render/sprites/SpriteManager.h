#include "Animation.h"
#include <map>
#include <string>

class AnimationManager {
public:
    void addAnimation(const std::string& name, const Animation& animation);
    const Animation& getAnimation(const std::string& name) const;

private:
    std::map<std::string, Animation> animations;
};
