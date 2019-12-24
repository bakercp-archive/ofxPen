//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Pen/Point.h"
#include "ofMath.h"


namespace ofx {
namespace Pen {



Point::Point(): Point(glm::vec3(0.0f, 0.0f, 0.0f), 0.0)
{
}


Point::Point(const glm::vec2& position, double timestampSeconds):
    Point({ position.x, position.y, 0.0f }, timestampSeconds)
{
}


Point::Point(const glm::vec3& position, double timestampSeconds):
    Point(position, timestampSeconds, 0.0f, 0.0f, 0.0f)
{
}


Point::Point(const glm::vec3& position,
             double timestampSeconds,
             float pressure,
             float tiltXDeg,
             float tiltYDeg):
    Point(position,
          timestampSeconds,
          pressure,
          0.0f,
          0.0f,
          tiltXDeg,
          tiltYDeg)
{
}


Point::Point(const glm::vec3& position,
             double timestampSeconds,
             float pressure,
             float tangentialPressure,
             float twistDeg,
             float tiltXDeg,
             float tiltYDeg):
    _position(position),
    _timestampSeconds(timestampSeconds),
    _pressure(pressure),
    _tangentialPressure(tangentialPressure),
    _twistDeg(twistDeg),
    _tiltXDeg(tiltXDeg),
    _tiltYDeg(tiltYDeg)
{
}


Point::Point(const PointerEventArgs& evt):
    Point({ evt.position().x, evt.position().y, 0 },
          evt.timestampSeconds(),
          evt.point().pressure(),
          evt.point().tangentialPressure(),
          evt.point().twistDeg(),
          evt.point().tiltXDeg(),
          evt.point().tiltYDeg())
{
}


Point::~Point()
{
}


glm::vec3 Point::position() const
{
    return _position;
}


double Point::timestampSeconds() const
{
    return _timestampSeconds;
}


float Point::pressure() const
{
    return _pressure;
}


float Point::tangentialPressure() const
{
    return _tangentialPressure;
}


float Point::twistDeg() const
{
    return _twistDeg;
}


float Point::twistRad() const
{
    return glm::radians(_twistDeg);
}


float Point::tiltXDeg() const
{
    return _tiltXDeg;
}


float Point::tiltXRad() const
{
    return glm::radians(_tiltXDeg);
}


float Point::tiltYDeg() const
{
    return _tiltYDeg;
}


float Point::tiltYRad() const
{
    return glm::radians(_tiltYDeg);
}


float Point::azimuthDeg() const
{
    if (!_azimuthAltitudeCached)
        _cacheAzimuthAltitude();
    return _azimuthDeg;
}


float Point::azimuthRad() const
{
    return glm::radians(azimuthDeg());
}


float Point::altitudeDeg() const
{
    if (!_azimuthAltitudeCached)
        _cacheAzimuthAltitude();
    return _altitudeDeg;
}


float Point::altitudeRad() const
{
    return glm::radians(altitudeDeg());
}


void Point::_cacheAzimuthAltitude() const
{
    double _azimuthRad = 0;
    double _altitudeRad = 0;

    bool tiltXIsZero = ofIsFloatEqual(_tiltXDeg, 0.0f);
    bool tiltYIsZero = ofIsFloatEqual(_tiltYDeg, 0.0f);

    // Take care of edge cases where std::tan(...) is undefined.
    if (!tiltXIsZero && !tiltYIsZero)
    {
        double _tanTy = std::tan(tiltYRad());
        _azimuthRad = std::atan2(_tanTy, std::tan(tiltXRad()));
        _altitudeRad = std::atan(std::sin(_azimuthRad) / _tanTy);
    }
    else if (tiltXIsZero && tiltYIsZero)
    {
        _azimuthRad = 0;
        _altitudeRad = 0;
    }
    else if (tiltXIsZero)
    {
        _azimuthRad = tiltYRad() > 0 ? glm::half_pi<double>() : glm::three_over_two_pi<double>();
        _altitudeRad = tiltYRad();
    }
    else if (tiltYIsZero)
    {
        _azimuthRad = tiltXRad() > 0 ? 0 : glm::pi<double>();
        _altitudeRad = tiltXRad();
    }

    // Put into range 0 - 2PI.
    if (_azimuthRad < 0)
        _azimuthRad += glm::two_pi<double>();

    _azimuthDeg = glm::degrees(_azimuthRad);
    _altitudeDeg = glm::degrees(_altitudeRad);

    _azimuthAltitudeCached = true;
}


Point Point::lerp(const Point& p0, const Point& p1, float amount)
{
    return Point(glm::mix(p0.position(), p1.position(), amount),
                 glm::mix(p0.timestampSeconds(), p1.timestampSeconds(), double(amount)),
                 glm::mix(p0.pressure(), p1.pressure(), amount),
                 glm::mix(p0.tangentialPressure(), p1.tangentialPressure(), amount),
                 glm::mix(p0.twistDeg(), p1.twistDeg(), amount),
                 glm::mix(p0.tiltXDeg(), p1.tiltXDeg(), amount),
                 glm::mix(p0.tiltYDeg(), p1.tiltYDeg(), amount));
}


} } // namespace ofx::Pen
