//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Pen/Stroke.h"
#include <queue>
#include "ofLog.h"
#include "ofMath.h"
#include "ofVectorMath.h"


namespace ofx {
namespace Pen {


Stroke::Stroke(): Stroke(std::vector<Point>())
{
}


Stroke::Stroke(const std::vector<Point>& points):
    _points(points),
    _rightVector(0.0f, 0.0f, -1.0f),
    _pointsModified(true)
{
}


Stroke::~Stroke()
{
}


void Stroke::add(const Point& point)
{
    _points.push_back(point);
    _pointsModified = true;
}


void Stroke::add(const std::vector<Point>& points)
{
    _points.insert(_points.end(), points.begin(), points.end());
    _pointsModified = true;
}


void Stroke::set(const std::vector<Point>& points)
{
    _points = points;
    _pointsModified = true;
}


const std::vector<Point>& Stroke::points() const
{
    return _points;
}


std::vector<Point>& Stroke::points()
{
    _pointsModified = true;
    return _points;
}


const Point& Stroke::operator[] (int64_t index) const
{
    return _points[wrappedIndex(index)];
}


Point& Stroke::operator[] (int64_t index)
{
    _pointsModified = true;
    return _points[wrappedIndex(index)];
}


std::size_t Stroke::size() const
{
    return _points.size();
}


bool Stroke::empty() const
{
    return _points.empty();
}


void Stroke::clear()
{
    _pointsModified = true;
    return _points.clear();
}


std::vector<Point>::iterator Stroke::begin()
{
    _pointsModified = true;
    return _points.begin();
}


std::vector<Point>::const_iterator Stroke::begin() const
{
    return _points.begin();
}


std::vector<Point>::reverse_iterator Stroke::rbegin()
{
    _pointsModified = true;
    return _points.rbegin();
}


std::vector<Point>::const_reverse_iterator Stroke::rbegin() const
{
    return _points.rbegin();
}


std::vector<Point>::iterator Stroke::end()
{
    _pointsModified = true;
    return _points.end();
}


std::vector<Point>::const_iterator Stroke::end() const
{
    return _points.end();
}


std::vector<Point>::reverse_iterator Stroke::rend()
{
    _pointsModified = true;
    return _points.rend();
}


std::vector<Point>::const_reverse_iterator Stroke::rend() const
{
    return _points.rend();
}


const std::vector<float>& Stroke::cumulativeLengths() const
{
    _updateCache();
    return _cumulativeLengths;
}


const std::vector<glm::vec3>& Stroke::tangents() const
{
    _updateCache();
    return _tangents;
}


const std::vector<glm::vec3>& Stroke::normals() const
{
    _updateCache();
    return _normals;
}


Point Stroke::pointAtIndex(int64_t i) const
{
    return _points[wrappedIndex(i)];
}


glm::vec3 Stroke::positionAtIndex(int64_t i) const
{
    return _points[wrappedIndex(i)].position();
}


glm::vec3 Stroke::normalAtIndex(int64_t i) const
{
    _updateCache();
    return _normals[wrappedIndex(i)];
}


glm::vec3 Stroke::tangentAtIndex(int64_t i) const
{
    _updateCache();
    return _tangents[wrappedIndex(i)];
}


std::pair<glm::vec3, glm::vec3> Stroke::minMax() const
{
    _updateCache();
    return _minMax;
}


glm::vec3 Stroke::centroid() const
{
    _updateCache();
    return _centroid;
}


ofRectangle Stroke::boundingBox() const
{
    _updateCache();
    return ofRectangle(_minMax.first, _minMax.second);
}


float Stroke::length() const
{
    _updateCache();

    if (!_cumulativeLengths.empty())
        return _cumulativeLengths.back();

    return 0.0f;
}


bool Stroke::intersectsWith(const Stroke& stroke) const
{
    for (std::size_t i = 0; i < stroke.size(); ++i)
    {
        for (std::size_t j = 0; j < size(); ++j)
        {
            const auto& thisPoint = _points[i].position();
            const auto& thatPoint = stroke._points[i].position();

            // Check point equality.
            if (glm::all(glm::equal(thisPoint, thatPoint)))
                return false;

            if (j == 0 || i == 0)
            {
                continue;
            }

            const auto& thisPointLast = _points[i - 1].position();
            const auto& thatPointLast = stroke._points[i - 1].position();

            // Check point equality.
            if (glm::all(glm::equal(thisPointLast, thatPointLast)))
                return false;

            glm::vec3 intersection;

            bool didIntersect = ofLineSegmentIntersection(thisPoint,
                                                          thisPointLast,
                                                          thatPoint,
                                                          thatPointLast,
                                                          intersection);

            if (didIntersect)
                return true;
        }
    }

    return false;
}


std::vector<Stroke::NNSearchResult> Stroke::findNearestN(const glm::vec3& targetPosition,
                                                           std::size_t n,
                                                           float minimumDistance,
                                                           float maximumDistance) const
{
    // Using lambda to compare elements.
    auto cmp = [&](const NNSearchResult& left, const NNSearchResult& right) {
        return left.second < right.second;
    };

    std::priority_queue<NNSearchResult, std::vector<NNSearchResult>, decltype(cmp)> q3(cmp);

    std::vector<NNSearchResult> results;



    return results;
}


std::size_t Stroke::wrappedIndex(int64_t i) const
{
    bool isClosed = false;

    if (_points.size() > std::size_t(std::numeric_limits<int64_t>::max()))
        ofLogError("Stroke::wrappedIndex") << "Signed integer maximum is smaller than size of stroke.";

    int64_t size = int64_t(_points.size());

    if (size == 0)
        return 0;

    if (i < 0)
        return isClosed ? (i + size) % size : 0;

    if (i > size - 1)
        return isClosed ? i % size : size - 1;

    return std::size_t(i);
}


void Stroke::_updateCache() const
{
    static const glm::vec3 LOWEST_VEC3(std::numeric_limits<float>::lowest());
    static const glm::vec3 MAX_VEC3(std::numeric_limits<float>::max());

    if (_pointsModified)
    {
        _pointsModified = false;

        if (_points.empty())
            return;

        _tangents.resize(_points.size());
        _normals.resize(_points.size());
        _angles.resize(_points.size());
        _rotations.resize(_points.size());
        _cumulativeLengths.resize(_points.size());
        _cumulativeLengths[0] = 0.0f;

        _minMax = { MAX_VEC3, LOWEST_VEC3 };

        _centroid = glm::vec3(0.0f);

        int64_t size = int64_t(_points.size());

        for (int64_t index = 0; index < size; ++index)
        {
            std::size_t i_prev = wrappedIndex(index - 1);
            std::size_t i      = wrappedIndex(index    );
            std::size_t i_next = wrappedIndex(index + 1);

            const auto& p_prev = _points[i_prev];
            const auto& p      = _points[i     ];
            const auto& p_next = _points[i_next];

            const auto& v_prev = p_prev.position();
            const auto& v      = p.position();
            const auto& v_next = p_next.position();

            auto v_to_prev = glm::normalize(v_prev - v); // vector to previous point
            auto v_to_next = glm::normalize(v_next - v); // vector to next point

            // If just one of p1, p2, or p3 was identical, further calculations
            // are (almost literally) pointless, as v1 or v2 will then contain
            // NaN values instead of floats.

            bool noSegmentHasZeroLength = (v_to_prev == v_to_prev && v_to_next == v_to_next);

            if (noSegmentHasZeroLength)
            {
                _tangents[i]  = glm::length2(v_to_next - v_to_prev) > 0 ? glm::normalize(v_to_next - v_to_prev) : -v_to_prev;
                _normals[i]   = glm::normalize(glm::cross(_rightVector, _tangents[i]));
                _rotations[i] = glm::cross(v_to_prev, v_to_next);
                _angles[i]    = glm::pi<float>() - std::acosf(glm::clamp(glm::dot(v_to_prev, v_to_next), -1.f, 1.f));
            }
            else
            {
                _tangents[i]  = glm::vec3(0.0f);
                _normals[i]   = glm::vec3(0.0f);
                _rotations[i] = glm::vec3(0.0f);
                _angles[i]    = 0.0f;
            }

            _minMax = { {
                glm::min(_minMax.first.x, v.x),
                glm::min(_minMax.first.y, v.y),
                glm::min(_minMax.first.z, v.z)
            }, {
                glm::max(_minMax.second.x, v.x),
                glm::max(_minMax.second.y, v.y),
                glm::max(_minMax.second.z, v.z)
            } };

            _centroid += v;

            _cumulativeLengths[i] = (i == 0) ? 0.0f : _cumulativeLengths[i_prev] + glm::distance(v_prev, v);
        }

        _centroid /= float(size);

    }
}



} } // namespace ofx::Pen
