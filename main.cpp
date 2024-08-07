// Copyright 2024 Jonathan Doughty
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <SFML/Audio.hpp>
using NB::Universe;
using NB::CelestialBody;

int main(int argc, char* argv[]) {
    std::string one = argv[1];
    std::string two = argv[2];
    double T = std::__cxx11::stod(one);
    double dT = std::__cxx11::stod(two);
    cout << "T: " << T << " " << dT << endl;
    double timeElapsed = 0;
    string file{std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>()};
    bool done = false;
    stringstream input(file);
    Universe u;
    input >> u;
    sf::Clock timer;
    sf::Sprite space;
    sf::Texture spaceT;
    spaceT.loadFromFile("space.png");
    space.setTexture(spaceT);
    sf::SoundBuffer spaceSB;
    spaceSB.loadFromFile("spaceSound.wav");
    sf::Sound spaceS(spaceSB);
    spaceS.setLoop(true);
    space.setScale(1.2, 1.2);
    spaceS.play();
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text timerDisplay("0.00", font);
    timerDisplay.setPosition(0, 0);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Solar System");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(space);
        if (timeElapsed < T) {
            timeElapsed += dT;
            u.step(dT);
            timerDisplay.setString(std::to_string(timeElapsed) + " seconds");
        } else {
            if (!done) {
                cout << u;
                done = true;
            }
        }
        u.draw(window);
        window.draw(timerDisplay);
        timer.restart();
        window.display();
    }
    return 0;
}
