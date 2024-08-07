// Copyright 2024 Jonathan Doughty
#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
using std::vector;
using std::ostream;
using std::istream;
using std::stringstream;
using std::string;
using std::endl;
using std::cout;
namespace NB {
class CelestialBody: public sf::Drawable {
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 public:
    friend istream& operator >> (istream& in, CelestialBody& p);
    friend ostream& operator << (ostream& out, CelestialBody& p);
    sf::Vector2f position();
    float mass();
    sf::Vector2f velocity();
    ~CelestialBody();
    sf::Texture *planetT;
    sf::Sprite planet;
    sf::Vector2<double> force;
    sf::Vector2<double> acceleration;
    sf::Vector2<double> vel;
    sf::Vector2<double> pos;
    double pMass;
 private:
    string name;
};
}  // end namespace NB
#endif
