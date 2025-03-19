#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonManager.hpp"

#define EPSILON (float)1e-6
#define MAX (a,b) a >= b ? a : b
#define MIN (a,b) a <= b ? a : b
#define DEG2RAD 0.01745329f
#define RAD2DEG 57.295779f
#define PI 3.141592f
#define LERP(a, b, t) (b-a) * t + a
#define SIGN(nbr) nbr >= 0.f ? 1.f : -1.f

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

namespace tools
{
    void initTools();

    void restartClock(sf::Time& _time, sf::Clock& _clock);

    float getDeltaTime(sf::Time const& _time);

    int randInt(int const& min, int const& max);

    sf::Vector2f createVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2);

    float getSqrMagnitude(sf::Vector2f const& _a);

    float getSqrMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

    float getMagnitude(sf::Vector2f const& _a);

    float getMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

    sf::Vector2f normalizef(sf::Vector2f const& _a);

    sf::Vector2f getNormBetween2Vectorsf(sf::Vector2f const& _a, sf::Vector2f const& _b);

    sf::Vector2f polarCoord(sf::Vector2f const& a, float const& r, float const& teta);

    float getAngleBetweenVectors(sf::Vector2f const& _a, sf::Vector2f const& _b);

    float getAngleBetweenVectors2(sf::Vector2f const& _a, sf::Vector2f const& _b);
    float getAngleBetweenVectorsReversedY(sf::Vector2f const& _a, sf::Vector2f const& _b);

    void truncate(sf::Vector2f& _a, float _max);

    sf::Vector2f catmullRomInterpolation(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2,
        const sf::Vector2f& p3, float t);
}
