//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/PointerEvents.h"


namespace ofx {
namespace Pen {


/// \brief A class representing a 3D point with pressure, tilt, etc.
class Point
{
public:
    /// \brief Construct a Point.
    Point();

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param timestampSeconds The timestamp in seconds.
    Point(const glm::vec2& position, double timestampSeconds);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param timestampSeconds The timestamp in seconds.
    Point(const glm::vec3& position, double timestampSeconds);

    /// \brief Construct a Point
    /// \param position The position in screen coordinates.
    /// \param timestampSeconds The timestamp in seconds.
    /// \param pressure The normalized pressure.
    /// \param tiltXDeg The tilt X angle in degrees.
    /// \param tiltYDeg The tilt Y angle in degrees.
    Point(const glm::vec3& position,
           double timestampSeconds,
           float pressure,
           float tiltXDeg,
           float tiltYDeg);

    /// \brief Construct a Point
    /// \param timestampSeconds The timestamp in seconds.
    /// \param position The position in screen coordinates.
    /// \param pressure The normalized pressure.
    Point(const glm::vec3& position,
          double timestampSeconds,
          float pressure);

    /// \brief Construct a Point
    /// \param timestampSeconds The timestamp in seconds.
    /// \param position The position in screen coordinates.
    /// \param pressure The normalized pressure.
    /// \param tangentialPressure The tangential pressure (aka barrel pressure).
    /// \param twistDeg The twist angle in degrees.
    /// \param tiltXDeg The tilt X angle in degrees.
    /// \param tiltYDeg The tilt Y angle in degrees.
    Point(const glm::vec3& position,
          double timestampSeconds,
          float pressure,
          float tangentialPressure,
          float twistDeg,
          float tiltXDeg,
          float tiltYDeg);

    /// \brief Create a Point from PointerEventArgs.
    Point(const PointerEventArgs& evt);

    /// \brief Destroy the Point.
    virtual ~Point();

    /// \returns the position in screen coordinates.
    glm::vec3 position() const;

    /// \returns the timestamp of this event in seconds.
    double timestampSeconds() const;

    /// \brief Get the normalized point pressure.
    ///
    /// The normalized pressure is in the range [0, 1].  For devices that do not
    /// support pressure, the value is 0.5 when a button is active or 0
    /// otherwise.
    ///
    /// \returns the normalized point pressure [0, 1].
    float pressure() const;

    /// \brief Get the Point's normalized tangential pressure.
    ///
    /// The normalized tangential pressure (aka the barrel pressure) is in the
    /// range [0, 1].  For devices that do not support tangential pressure, the
    /// value is 0.
    ///
    /// \returns the normalized tangential pressure [0, 1].
    float tangentialPressure() const;

    /// \brief Get the Point's twist in degrees.
    ///
    /// The clockwise rotation (in degrees, in the range of [0,359]) of a
    /// transducer (e.g. pen stylus) around its own major axis. For hardware and
    /// platforms that do not report twist, the value MUST be 0.
    ///
    /// \returns the twist in degrees.
    float twistDeg() const;

    /// \brief Get the Point's twist in radians.
    ///
    /// The clockwise rotation (in degrees, in the range of [0,2*PI]) of a
    /// transducer (e.g. pen stylus) around its own major axis. For hardware and
    /// platforms that do not report twist, the value MUST be 0.
    ///
    /// \returns the twist in radians.
    float twistRad() const;

    /// \brief Get the Tilt X angle in degrees.
    ///
    /// Tilt X is given in degrees [-90, 90] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    ///
    /// \returns the Tilt X angle in degrees.
    float tiltXDeg() const;

    /// \brief Get the Tilt X angle in radians.
    ///
    /// Tilt X is given in degrees [-PI/2, PI/2] between the Y-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the Y axis.  A
    /// positive tilt X is to the right.  The value is 0 if the tilt X is
    /// undefined.
    ///
    /// \returns the Tilt X angle in radians.
    float tiltXRad() const;

    /// \brief Get the Tilt Y angle in degrees.
    ///
    /// Tilt Y is given in degrees [-90, 90] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    ///
    /// \returns the Tilt Y angle in degrees.
    float tiltYDeg() const;

    /// \brief Get the Tilt Y angle in radians.
    ///
    /// Tilt Y is given in degrees [-PI/2, PI/2] between the X-Z plane and the plane
    /// containing both the transducer (e.g. pen stylus) axis and the X axis.  A
    /// positive tilt Y is toward the user.  The value is 0 if the tilt Y is
    /// undefined.
    ///
    /// \returns the Tilt Y angle in radians.
    float tiltYRad() const;

    /// \brief Get the azimuth angle in degress.
    ///
    /// The azimuth angle, in the range 0 to 360 degrees. 0 represents a stylus
    /// whose cap is pointing in the direction of increasing screen X values.
    /// 180 degrees represents a stylus whose cap is pointing in the direction
    /// of increasing screen Y values. The value is 0 if undefined.
    ///
    /// \returns the azimuth in degress.
    float azimuthDeg() const;

    /// \brief Get the azimuth angle in radians.
    ///
    /// The azimuth angle, in the range 0 to 2π radians. 0 represents a stylus
    /// whose cap is pointing in the direction of increasing screen X values.
    /// π/2 radians represents a stylus whose cap is pointing in the direction
    /// of increasing screen Y values. The value is 0 if undefined.
    ///
    /// \returns the azimuth in degress.
    float azimuthRad() const;

    /// \brief Get the altitude angle in degrees.
    ///
    /// The altitude angle, in the range 0 degrees (parallel to the surface) to
    /// 90 degrees (perpendicular to the surface). The value is 0 if undefined.
    ///
    /// \returns the altitude in degrees.
    float altitudeDeg() const;

    /// \brief Get the altitude angle in degrees.
    ///
    /// The altitude angle, in the range 0 radians (parallel to the surface) to
    /// π/2 radians (perpendicular to the surface). The value is 0 if undefined.
    ///
    /// \returns the altitude in radians.
    float altitudeRad() const;

    /// \brief Linearly interpolate between the values in two points.
    ///
    /// PointShape not interpolated, but copied from p0.
    ///
    /// Cached values are not interpolated, but will be recalculated.
    ///
    /// \param p0 The point associated with amount = 0.
    /// \param p1 The point associated with amount = 1.
    /// \param amount the value between [0, 1] that indicates the lerp amount.
    /// \returns the interpolated Point.
    static Point lerp(const Point& p0, const Point& p1, float amount);

private:
    /// \brief The position in screen coordinates.
    glm::vec3 _position;

    /// \brief The timestamp of this event in seconds.
    double _timestampSeconds = 0;

    /// \brief The Point's normalized pressure.
    float _pressure = 0;

    /// \brief The Point's tangential pressure (aka barrel pressure).
    float _tangentialPressure = 0;

    /// \brief The Point's twist in degrees.
    float _twistDeg = 0;

    /// \brief The Point tilt X angle in degrees.
    float _tiltXDeg = 0;

    /// \brief The Point tilt Y angle in degrees.
    float _tiltYDeg = 0;

    /// \brief A utility function for caching the azimuth and altitude.
    void _cacheAzimuthAltitude() const;

    /// \brief True if the azimuth and altitude are cached.
    mutable bool _azimuthAltitudeCached = false;

    /// \brief The cached azimuth in degrees.
    mutable float _azimuthDeg = 0;

    /// \brief The cached altitude in degrees.
    mutable float _altitudeDeg = 0;

};


} } // namespace ofx::Pen
