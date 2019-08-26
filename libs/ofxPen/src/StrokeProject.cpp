//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Pen/StrokeProject.h"


namespace ofx {
namespace Pen {


StrokeProject::StrokeProject()
{
}


StrokeProject::StrokeProject(const std::vector<Stroke>& strokes,
                             const std::vector<StrokeSet>& strokeSets):
    _strokes(strokes),
    _strokeSets(strokeSets),
    _isModified(false)
{
}


std::vector<Stroke>& StrokeProject::strokes()
{
    _isModified = true;
    return _strokes;
}


const std::vector<Stroke>& StrokeProject::strokes() const
{
    return _strokes;
}


std::vector<StrokeSet>& StrokeProject::strokeSets()
{
    _isModified = true;
    return _strokeSets;
}


const std::vector<StrokeSet>& StrokeProject::strokeSets() const
{
    return _strokeSets;
}


bool StrokeProject::isModified() const
{
    return _isModified;
}


void StrokeProject::setModified(bool modified)
{
    _isModified = modified;
}


bool StrokeProject::isEmpty() const
{
    return _strokes.empty() && _strokeSets.empty();
}


} } // namespace ofx::Pen
