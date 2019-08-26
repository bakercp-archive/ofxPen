//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Player/BasePlayerTypes.h"
#include "ofx/Pen/Stroke.h"


namespace ofx {
namespace Pen {


class PlayableStroke: public Player::BaseTimeIndexed
{
public:
    /// \brief Create a PlayableStroke.
    /// \param stroke The stroke to play.
    PlayableStroke(const Stroke& stroke);

    const Stroke& stroke() const;

    double timeForIndex(std::size_t index) const override;
    std::size_t size() const override;

private:
    /// \brief A copy of the playable stroke.
    Stroke _stroke;

};


/// \brief A stroke player.
class StrokePlayer: public Player::BasePlayer
{
public:
    StrokePlayer();

    /// \brief Destroy the StrokePlayer.
    virtual ~StrokePlayer() override;

    /// \brief Load a stroke to play.
    /// \param stroke The stroke to load.
    /// \returns true if the stroke was successfully loaded.
    bool load(const Stroke& stroke);

    void close() override;
    const Player::BaseTimeIndexed* indexedData() const override;

    /// \returns the interpolated stroke point.
    Point point() const;

protected:
    /// \brief The stroke wrapped in a playable wrapper.
    std::shared_ptr<PlayableStroke> _playableStroke = nullptr;

};


} } // namespace ofx::Handwriting
