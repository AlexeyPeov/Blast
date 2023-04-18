#include "../Headers/Animation.h"

void Animation::update() {
    elapsedTime += 1;
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0;
        currentFrame = (currentFrame + 1) % numFrames;
        int left = currentFrame * frameWidth;
        sprite.setTextureRect(sf::IntRect(left, 0, frameWidth, frameHeight));
    }
    if (currentFrame == numFrames - 1) {
        finished = true;
    }
}
