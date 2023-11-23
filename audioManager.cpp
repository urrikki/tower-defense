#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager() {
    /*if (!buffer.loadFromFile("audio/background.mp3"))
    {
        std::cout << "Erreur lors du chargement du son de background." << std::endl;
    }*/
}

AudioManager::~AudioManager() {
    // Libération des ressources audio, si nécessaire
}

void AudioManager::loadAudio(const std::string& filePath) {
    if (buffer.loadFromFile(filePath)) {
        soundBuffers.push_back(buffer);
    }
    else {
        // Gestion des erreurs lors du chargement du fichier audio
    }
}

void AudioManager::playAudio(int index) {
    if (index >= 0 && index < soundBuffers.size()) {
        sounds.emplace_back();
        sounds.back().setBuffer(soundBuffers[index]);
        sounds.back().play();
    }
    else {
        // Gestion des erreurs si l'indice est hors limites
    }
}

void AudioManager::stopAudio(int index) {
    if (index >= 0 && index < sounds.size()) {
        sounds[index].stop();
        sounds.erase(sounds.begin() + index);
    }
}
