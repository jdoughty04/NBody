#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
// Copyright 2024 Jonathan Doughty
#include <sstream>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>
using std::vector;
using std::endl;
using std::ostream;
using std::istream;
using std::stringstream;
using std::string;
using std::cout;
using std::ifstream;
namespace NB {

class Universe {
 public:
    Universe();
    explicit Universe(string fileName);
    void draw(sf::RenderWindow&);
    friend ostream& operator << (ostream& out, Universe& u);
    friend istream& operator >> (istream& in, Universe& u);
    int numPlanets();
    double radius();
    CelestialBody& operator[] (int idx);
    void step(double seconds);
 private:
    std::unique_ptr<CelestialBody[]> bodies;
    int planets;
    double rad;
};
}  // end namespace NB
#endif
