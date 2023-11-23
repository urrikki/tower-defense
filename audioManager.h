#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void loadAudio(const std::string& filePath);
    void playAudio(int index);
    void stopAudio(int index);

private:
    std::vector<sf::SoundBuffer> soundBuffers;
    std::vector<sf::Sound> sounds;
    sf::SoundBuffer buffer;
};
