// Copyright 2024 Jonathan Doughty
#include "Universe.hpp"
namespace NB {


Universe::Universe() {
}

void Universe::draw(sf::RenderWindow& window) {
    sf::Vector2<float> origin(400, 400);
    for (int i = 0; i < planets; i++) {
        // normalize position values to screen size and coordinate system
        bodies[i].planet.setPosition((bodies[i].position().x*(origin.x/rad)) + origin.x,
        (bodies[i].position().y*(-1.0 * origin.y/rad)) + origin.y);

        window.draw(bodies[i]);
    }
}

CelestialBody& Universe::operator[] (int idx) {
    return bodies[idx];
}

// Step function to simulate one tick (some amount of seconds), moving each planet linearly based on existing forces
void Universe::step(double seconds) {
    double massProduct;
    double squaredDistance;
    double forceMagnitude;
    sf::Vector2<double> distanceVec;
    for (int i = 0; i < planets; i++) {
        bodies[i].force = sf::Vector2<double>(0, 0);
        bodies[i].acceleration = sf::Vector2<double>(0, 0);
        for (int j = 0; j < planets; j++) {
            if (i == j) {
                continue;
            } else {
            massProduct = bodies[i].pMass * bodies[j].pMass;
            distanceVec = bodies[j].pos - bodies[i].pos;
            squaredDistance = pow(distanceVec.x, 2) + pow(distanceVec.y, 2);
            forceMagnitude = 6.67e-11*massProduct / squaredDistance;
            // getting directional vector to find force vector
            distanceVec /= pow(squaredDistance, 0.5);
            distanceVec *= forceMagnitude;
            bodies[i].force += distanceVec;
            }
        }
        bodies[i].acceleration += bodies[i].force/bodies[i].pMass;
        bodies[i].vel += sf::Vector2<double>
        (seconds * bodies[i].acceleration.x, seconds * bodies[i].acceleration.y);
    }
    for (int i = 0; i < planets; i++) {
        bodies[i].pos += sf::Vector2<double>(seconds * bodies[i].vel.x, seconds * bodies[i].vel.y);
    }
}
Universe::Universe(string fileName) {
    ifstream in(fileName);
    if (!in) cout << "failed" << endl;
    in >> *this;
    in.close();
}

int Universe::numPlanets() {
    return planets;
}

double Universe::radius() {
    return rad;
}

// Reads file into universe object
istream& operator >> (istream& in, Universe& u) {
    string line;
    getline(in, line);
    stringstream ss(line);
    ss >> u.planets;
    getline(in, line);
    ss.clear();
    ss.str(line);
    ss >> u.rad;
    u.bodies = std::unique_ptr<CelestialBody[]>(new CelestialBody[u.planets]);
    for (int i = 0; i < u.planets; i++) {
        ss.clear();
        getline(in, line);
        if (line != "") {
            ss.str(line);
            u.bodies[i] = CelestialBody();
            ss >> u.bodies[i];
        } else {
            i--;
        }
    }
    return in;
}

ostream& operator << (ostream& out, Universe& u) {
    out << u.planets << endl << u.rad << endl;
    for (int i = 0; i < static_cast<int>(u.planets); i++) {
        out << u.bodies[i];
    }
    return out;
}
}  // end namespace NB
