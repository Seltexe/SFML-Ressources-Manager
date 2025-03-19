#include "pch.h"
#include "tools.hpp"

namespace tools
{
	void initTools()
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void restartClock(sf::Time& _time, sf::Clock& _clock)
	{
		_time = _clock.restart();
	}

	float getDeltaTime(sf::Time const& _time)
	{
		return _time.asSeconds();
	}

	int randInt(int const& min, int const& max)
	{
		return (rand() % (max - min + 1)) + min;
	}

	sf::Vector2f createVectorWithVector(sf::Vector2f const& _v1, sf::Vector2f const& _v2)
	{
		return sf::Vector2f(_v2.x - _v1.x, _v2.y - _v1.y);
	}

	float getSqrMagnitude(sf::Vector2f const& _a)
	{
		return (_a.x * _a.x) + (_a.y * _a.y);
	}

	float getSqrMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		return getSqrMagnitude(createVectorWithVector(_a, _b));
	}

	float getMagnitude(sf::Vector2f const& _a)
	{
		return sqrtf(getSqrMagnitude(_a));
	}

	float getMagnitudeBetween2Vectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		return sqrtf(getSqrMagnitudeBetween2Vectors(_a, _b));
	}

	sf::Vector2f normalizef(sf::Vector2f const& _a)
	{
		float magnitude = getMagnitude(_a);
		if (magnitude < EPSILON) {
			return _a;
		}
		return sf::Vector2f(_a.x / magnitude, _a.y / magnitude);
	}

	sf::Vector2f getNormBetween2Vectorsf(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		return normalizef(createVectorWithVector(_a, _b));
	}

	sf::Vector2f polarCoord(sf::Vector2f const& _a, float const& _r, float const& _teta)
	{
		return sf::Vector2f(_a.x + (_r * cosf(_teta)), _a.y + (_r * sinf(_teta)));
	}

	float getAngleBetweenVectors(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		float angle = atan2f(_b.y, _b.x) - atan2f(_a.y, _a.x);
		if (angle > PI)
			angle -= 2 * PI;
		else if (angle < -PI)
			angle += 2 * PI;
		return angle;
	}

	float getAngleBetweenVectors2(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		float angle = atan2f(_a.x - _b.x, _a.y - _b.y);
		if (angle > PI)
			angle -= 2 * PI;
		else if (angle < -PI)
			angle += 2 * PI;
		return angle;
	}

	float getAngleBetweenVectorsReversedY(sf::Vector2f const& _a, sf::Vector2f const& _b)
	{
		float angle = atan2f(_a.x - _b.x, _a.y * -1.f - _b.y);
		if (angle > PI)
			angle -= 2 * PI;
		else if (angle < -PI)
			angle += 2 * PI;
		return angle;
	}

	void truncate(sf::Vector2f& _a, float _max)
	{
		if (_a.x > _max)
			_a.x = _max;
		else if (_a.x < _max * -1.f)
			_a.x = _max * -1.f;
		if (_a.y > _max)
			_a.y = _max;
		else if (_a.y < _max * -1.f)
			_a.y = _max * -1.f;

	}

	sf::Vector2f catmullRomInterpolation(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, float t)
	{
		t = 0.016f;
		float t2 = t * t;
		float t3 = t * t2;

		float x = 0.5f * ((2.0f * p1.x) + (-p0.x + p2.x) * t + (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 + (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);
		float y = 0.5f * ((2.0f * p1.y) + (-p0.y + p2.y) * t + (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 + (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);

		return sf::Vector2f(x, y);
	}
}
