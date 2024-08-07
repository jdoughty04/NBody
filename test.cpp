// Copyright 2023
// Jonathan Doughty
// test.cpp for ps4b
// updated 03/18/2024
#include <fstream>
#include <iostream>
#include <string>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using NB::CelestialBody;
using NB::Universe;
BOOST_AUTO_TEST_CASE(stepTest) {
    Universe l("planets.txt");
    Universe r("planets.txt");
    l.step(0);
    BOOST_REQUIRE_EQUAL(l[0].position().x, r[0].position().x);

    Universe e("planets.txt");
    Universe w("planets.txt");
    e.step(500000);
    w.step(500000);
    BOOST_REQUIRE_EQUAL(e[1].velocity().y, w[1].velocity().y);
    BOOST_REQUIRE_EQUAL(e[2].velocity().y, w[2].velocity().y);
    BOOST_REQUIRE_EQUAL(e[4].velocity().y, w[4].velocity().y);
}
BOOST_AUTO_TEST_CASE(radiusGetter) {
    Universe l("1body.txt");
    BOOST_REQUIRE_EQUAL(l.radius(), 100);

    Universe u("3body.txt");
    BOOST_REQUIRE_EQUAL(u.radius(), 1.25e+11);
}

BOOST_AUTO_TEST_CASE(numPlanetsGetter) {
    Universe l("1body.txt");
    BOOST_REQUIRE_EQUAL(l.numPlanets(), 1);

    Universe u("3body.txt");

    BOOST_REQUIRE_EQUAL(u.numPlanets(), 3);
}

// these rely on universe indexing

BOOST_AUTO_TEST_CASE(positionGetter) {
    Universe l("1body.txt");
    BOOST_REQUIRE_EQUAL(l[0].position().x, sf::Vector2f(10, 20).x);
    BOOST_REQUIRE_EQUAL(l[0].position().y, sf::Vector2f(10, 20).y);

    Universe u("3body.txt");
    BOOST_REQUIRE_EQUAL(u[0].position().x, sf::Vector2f(0, 0).x);
    BOOST_REQUIRE_EQUAL(u[0].position().y, sf::Vector2f(0, 0).y);
}

BOOST_AUTO_TEST_CASE(velocityGetter) {
    Universe l("1body.txt");
    BOOST_REQUIRE_EQUAL(l[0].velocity().x, sf::Vector2f(2, 1).x);
    BOOST_REQUIRE_EQUAL(l[0].velocity().y, sf::Vector2f(2, 1).y);

    Universe u("3body.txt");
    BOOST_REQUIRE_EQUAL(u[0].velocity().x, sf::Vector2f(0.05e04, 0).x);
    BOOST_REQUIRE_EQUAL(u[0].velocity().y, sf::Vector2f(0.05e04, 0).y);
}
BOOST_AUTO_TEST_CASE(massGetter) {
    Universe l("1body.txt");
    BOOST_REQUIRE_EQUAL(l[0].mass(), static_cast<float>(1e20));

    Universe u("3body.txt");
    BOOST_REQUIRE_EQUAL(u[0].mass(), static_cast<float>(5.974e24));
}
