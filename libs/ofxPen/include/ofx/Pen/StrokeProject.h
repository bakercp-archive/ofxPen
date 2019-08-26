//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofx/Pen/StrokeSet.h"
#include "ofRectangle.h"


namespace ofx {
namespace Pen {


class StrokeProject
{
public:
    StrokeProject();
    StrokeProject(const std::vector<Stroke>& strokes,
                  const std::vector<StrokeSet>& strokeSets);
    std::vector<Stroke>& strokes();
    const std::vector<Stroke>& strokes() const;
    std::vector<StrokeSet>& strokeSets();
    const std::vector<StrokeSet>& strokeSets() const;
    bool isModified() const;
    void setModified(bool modified);
    bool isEmpty() const;
private:
    /// \brief A collection of strokes that are not part of a set.
    std::vector<Stroke> _strokes;

    /// \brief A collection of stroke sets.
    std::vector<StrokeSet> _strokeSets;

    /// \brief Set to true when a stroke or stroke set is accessed.
    bool _isModified = false;

};


} } // namespace ofx::Pen
