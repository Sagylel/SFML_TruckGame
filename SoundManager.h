#include <iostream>
#include <SFML/Audio.hpp>

class SoundManager {
public:
    SoundManager();

    void Truck(float vol, float pitch, bool loop);
    void RunOver(float vol, float pitch, bool loop);
private:

    sf::SoundBuffer sb_truck;
    sf::Sound s_truck;
    sf::SoundBuffer sb_runover;
    sf::Sound s_runover;
};