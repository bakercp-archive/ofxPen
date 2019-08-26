//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Pen/StrokePlayer.h"


namespace ofx {
namespace Pen {


PlayableStroke::PlayableStroke(const Stroke& stroke):
    _stroke(stroke)
{
}


const Stroke& PlayableStroke::stroke() const
{
    return _stroke;
}


double PlayableStroke::timeForIndex(std::size_t index) const
{
    return _stroke.points()[index].timestampSeconds() * 1000000.0;
}


std::size_t PlayableStroke::size() const
{
    return _stroke.points().size();
}


StrokePlayer::StrokePlayer()
{
}


StrokePlayer::~StrokePlayer()
{
}


bool StrokePlayer::load(const Stroke& stroke)
{
    close();
    _playableStroke = std::make_shared<PlayableStroke>(stroke);
    return true;
}


void StrokePlayer::close()
{
    Player::BasePlayer::close();
    _playableStroke = nullptr;
}


const Player::BaseTimeIndexed* StrokePlayer::indexedData() const
{
    return _playableStroke.get();
}


Point StrokePlayer::point() const
{
    if (_playableStroke)
    {
        Point thisPoint = _playableStroke->stroke().points()[getFrameIndex()];
        Point nextPoint = _playableStroke->stroke().points()[nextFrameIndex()];
        // The fraction between two points.
        float amount = std::abs(interpolatedFrameIndex() - getFrameIndex());
        return Point::lerp(thisPoint, nextPoint, amount);
    }

    return Point();
}


} } // namespace ofx::Handwriting
