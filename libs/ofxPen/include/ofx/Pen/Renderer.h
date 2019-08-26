//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include <vector>
#include "ofx/Pen/Stroke.h"
#include "ofMesh.h"
#include "ofVboMesh.h"


namespace ofx {
namespace Pen {


/// \brief A utility class for visualizing strokes.
class Renderer
{
public:
    struct Settings;

    /// \brief Create a default Renderer.
    Renderer();

    /// \brief Create a default Renderer with the given settings.
    /// \param settings The settings values to set.
    Renderer(const Settings& settings);

    /// \brief Destroy the Renderer.
    ~Renderer();

    /// \brief Configure the Renderer with the given settings.
    /// \param settings The settings values to set.
    /// \returns true if the setup was successful.
    bool setup(const Settings& settings);

    /// \brief Get the rendered mesh for the given stroke.
    /// \param stroke The stroke to render.
    /// \param strokeColor The color of the stroke.
    /// \returns the generated mesh.
    ofMesh generateMesh(const Stroke& stroke, const ofColor& strokeColor) const;

    /// \brief Draw a pointer stroke.
    /// \param stroke The stroke to render.
    void draw(const Stroke& stroke, ofPolyRenderMode renderType = OF_MESH_FILL) const;

    /// \brief Draw a pointer stroke with additional visuals.
    /// \param stroke The stroke to render.
    void drawDebug(const Stroke& stroke,
                   float normalLength = 0,
                   float tangenLength = 0) const;

    /// \returns the Settings.
    Settings settings() const;

    struct Settings
    {
        Settings();

        /// \brief The minimum width of the stroke in pixels.
        float minimumStrokeWidth = 5;

        /// \brief The maximum width of the stroke in pixels.
        float maximumStrokeWidth = 10;

        /// \brief The color of normal points.
        ofColor pointColor;

    };

private:
    /// \brief The Settings.
    Settings _settings;

};




} } // namespace ofx::Pen
