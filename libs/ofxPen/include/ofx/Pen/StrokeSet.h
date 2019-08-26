//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <map>
#include <vector>
#include "ofx/Pen/Point.h"
#include "ofx/Pen/Stroke.h"
#include "ofRectangle.h"


namespace ofx {
namespace Pen {


/// \brief A set of strokes that form a set.
struct StrokeSet
{
    /// \brief The strokes.
    std::vector<Stroke> strokes;

    /// \brief Optional attributes for the stroke set.
    std::map<std::string, std::string> attributes;

    /// \btief The attribute holding the text transcription.
    static const std::string ATTRIBUTE_TRANSCRIPTION;

    /// \returns the bounding box for this PointerStroke.
    ofRectangle boundingBox() const
    {
        ofRectangle boundingBox;

        for (std::size_t i = 0; i < strokes.size(); ++i)
        {
            if (i == 0)
                boundingBox.set(strokes[i].boundingBox());
            else
                boundingBox.growToInclude(strokes[i].boundingBox());
        }

        return boundingBox;
    }

};


} } // namespace ofx::Pen
