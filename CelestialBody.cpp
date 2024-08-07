// Copyright 2024 Jonathan Doughty
#include "CelestialBody.hpp"

namespace NB {
void CelestialBody::draw(sf::RenderTarget& target,
sf::RenderStates states = sf::RenderStates::Default) const {
    sf::Vector2<float> origin(400, 400);
    target.draw(planet, states);
}

sf::Vector2f CelestialBody::position() {
    return sf::Vector2f(pos.x, pos.y);
}

sf::Vector2f CelestialBody::velocity() {
    return sf::Vector2f(vel.x, vel.y);
}

ostream& operator << (ostream& out, CelestialBody& p) {
    out << p.pos.x << " " << p.pos.y << " " << p.vel.x << " " << p.vel.y
<< " " << p.pMass << " " << p.name << endl;
    return out;
}

float CelestialBody::mass() {
    return pMass;
}

istream& operator >> (istream& in, CelestialBody& p) {
    in >> p.pos.x >> p.pos.y >> p.vel.x >> p.vel.y >> p.pMass;
    char c = ' ';
    while (c == ' ') {
        in >> c;
    }
    getline(in, p.name);
    string v = "";
    v += c;
    p.name.insert(0, v);
    p.planetT = new sf::Texture;
    p.planetT->loadFromFile(p.name);
    p.planet.setTexture(*(p.planetT));
    p.force = sf::Vector2<double>(0, 0);
    return in;
}

CelestialBody::~CelestialBody() {
    delete planetT;
}


}  // end namespace NB
