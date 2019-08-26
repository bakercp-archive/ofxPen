//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <vector>
#include "ofx/Pen/Point.h"
#include "ofRectangle.h"


namespace ofx {
namespace Pen {


class Stroke
{
public:
    enum class NormalsMode
    {
        /// \brief The default normals mode.
        /// These normals point away from the center of radius.
        DEFAULT
    };

    Stroke();

    Stroke(const std::vector<Point>& points);

    ~Stroke();

    /// \brief Add a point.
    /// \param point The point to add.
    void add(const Point& point);

    /// \brief Add an array of points.
    /// \param points The points to add.
    void add(const std::vector<Point>& points);

    /// \brief Set an array of points.
    /// \param points The points to set.
    void set(const std::vector<Point>& points);

    /// \returns a reference to the points.
    const std::vector<Point>& points() const;

    /// \returns a reference to the points.
    std::vector<Point>& points();

    /// \brief Access a point with an index.
    ///
    /// The index will wrap according to the wrapIndex() function.
    ///
    /// \param index The index to access.
    /// \returns a reference to the point.
    const Point& operator[] (int64_t index) const;

    /// \brief Access a point with an index.
    ///
    /// The index will wrap according to the wrapIndex() function.
    ///
    /// \param index The index to access.
    /// \returns a reference to the point.
    Point& operator[] (int64_t index);

    /// \returns the number of points.
    std::size_t size() const;

    /// \returns true if size() == 0.
    bool empty() const;

    /// \brief Clear the contents of the stroke.
    void clear();

    typename std::vector<Point>::iterator begin();
    typename std::vector<Point>::const_iterator begin() const;
    typename std::vector<Point>::reverse_iterator rbegin();
    typename std::vector<Point>::const_reverse_iterator rbegin() const;
    typename std::vector<Point>::iterator end();
    typename std::vector<Point>::const_iterator end() const;
    typename std::vector<Point>::reverse_iterator rend();
    typename std::vector<Point>::const_reverse_iterator rend() const;

    /// \returns the cumulative lengths.
    const std::vector<float>& cumulativeLengths() const;

    /// \returns The tangents for all points.
    const std::vector<glm::vec3>& tangents() const;

    /// \retuns The normals for all points.
    const std::vector<glm::vec3>& normals() const;

    Point pointAtIndex(int64_t i) const;
    glm::vec3 positionAtIndex(int64_t i) const;
    glm::vec3 normalAtIndex(int64_t i) const;
    glm::vec3 tangentAtIndex(int64_t i) const;

    /// \brief Get the bounding cube of the stroke.
    /// \returns a the minimum and maximum extents of the stroke in 3-d.
    std::pair<glm::vec3, glm::vec3> minMax() const;

    /// \brief Get the center of the stroke.
    glm::vec3 centroid() const;

    /// \brief Get the bounding box of the stroke projected on the z-plane.
    ofRectangle boundingBox() const;

    /// \returns the total cumulative length of the stroke.
    float length() const;

    /// \brief Determine if two strokes intersect.
    /// \param stroke The stroke to check.
    /// \returns true if this stroke intersects with the given stroke.
    bool intersectsWith(const Stroke& stroke) const;

    /// \brief A type definition containing an index and a distance.
    typedef std::pair<std::size_t, float> NNSearchResult;

    /// \brief Find the nearest N points on the stroke to the given target.
    /// \param target The target to search for.
    /// \param n The number of neighbors to search for.
    std::vector<NNSearchResult> findNearestN(const glm::vec3& targetPosition,
                                             std::size_t n,
                                             float minimumDistance = std::numeric_limits<float>::lowest(),
                                             float maximumDistance = std::numeric_limits<float>::max()) const;

    /// \brief Get an index that has been wrapped or constrained.
    /// \param index The index to wrap.
    /// \returns an safe index [0, size()).
    std::size_t wrappedIndex(int64_t index) const;
    
private:
    void _updateCache() const;

    /// \brief The points.
    std::vector<Point> _points;

    /// \brief The cumulative lenth at each point.
    /// To find the length from i to i+1, _cumulativeLengths[i + 1] - _cumulativeLengths[i].
    mutable std::vector<float> _cumulativeLengths;

    /// \brief The tangents at the givern point.
    mutable std::vector<glm::vec3> _tangents;

    /// \brief The normal at the given point.
    mutable std::vector<glm::vec3> _normals;

    /// \brief The rotation axes between adjacent segments, stored per point (cross product).
    mutable std::vector<glm::vec3> _rotations;

    /// \brief The angle in radians between adjacent segments, stored per point (std::asin(cross product)).
    mutable std::vector<float> _angles;

    /// \brief The min/max values.
    mutable std::pair<glm::vec3, glm::vec3> _minMax;

    /// \brief The 3d centroid.
    mutable glm::vec3 _centroid;

    /// \brief True if the points have been modified.
    mutable bool _pointsModified = false;

    /// \brief The right vector;
    glm::vec3 _rightVector;
};


} } // namespace ofx::Pen
