#include "SoundManager.h"

using namespace sf;

// Constructor
SoundManager::SoundManager() {
    if (!sb_truck.loadFromFile("Resources/Sounds/truck.wav")) {
        std::cout << "ERROR: sounds/fire.wav didn't load" << "\n";
    }
    else {
        s_truck.setBuffer(sb_truck);
    }

    if (!sb_runover.loadFromFile("Resources/Sounds/run_over.wav")) {
        std::cout << "ERROR: sounds/explo_asteroid.wav didn't load" << "\n";
    }
    else {
        s_runover.setBuffer(sb_runover);
    }
}

//Functions
void SoundManager::Truck(float vol, float pitch, bool loop) {
    s_truck.setVolume(vol);
    s_truck.setPitch(pitch);
    s_truck.setLoop(loop);
    s_truck.play();
}

void SoundManager::RunOver(float vol, float pitch, bool loop) {
    s_runover.setVolume(vol);
    s_runover.setPitch(pitch);
    s_runover.setLoop(loop);
    s_runover.play();
}