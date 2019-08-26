//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#include "ofx/Pen/Renderer.h"
#include "ofGraphics.h"


namespace ofx {
namespace Pen {



Renderer::Settings::Settings(): pointColor(ofColor::blue)
{
}


Renderer::Renderer()
{
}


Renderer::Renderer(const Settings& settings)
{
    setup(settings);
}


Renderer::~Renderer()
{
}


bool Renderer::setup(const Settings& settings)
{
    _settings = settings;
    return true;
}


ofMesh Renderer::generateMesh(const Stroke& stroke, const ofColor& strokeColor) const
{
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    bool useZ = false;
    float R = _settings.maximumStrokeWidth;

    const auto& points = stroke.points();

    for (std::size_t i = 0; i < points.size(); ++i)
    {
        const auto& e = points[i];

        // Pen tip.
        glm::vec3 p0 = { e.position().x, e.position().y, 0 };
        glm::vec3 p1 = p0;

        float az = e.azimuthRad();
        float al = e.altitudeRad();

        if (!ofIsFloatEqual(az, 0.0f) || !ofIsFloatEqual(al, 0.0f))
        {
            float cosAl = std::cos(al);
            p1.x += R * std::cos(az) * cosAl;
            p1.y += R * std::sin(az) * cosAl;

            if (useZ)
                p1.z += R * std::sin(al);
        }
        else
        {
            // If no altitude / azimuth are available, use tangents to simulate.
            if (i > 0 && i < points.size() - 1)
            {
                std::size_t i1 = i - 1;
                std::size_t i2 = i;
                std::size_t i3 = i + 1;
                const auto& p_1 = points[i1].position();
                const auto& p_2 = points[i2].position();
                const auto& p_3 = points[i3].position();
                auto v1(p_1 - p_2); // vector to previous point
                auto v2(p_3 - p_2); // vector to next point
                v1 = glm::normalize(v1);
                v2 = glm::normalize(v2);
                glm::vec2 tangent = glm::length2(v2 - v1) > 0 ? glm::normalize(v2 - v1) : -v1;
                glm::vec3 normal = glm::cross(glm::vec3(tangent, 0), { 0, 0, 1 });
                auto pp0 = p_2 + normal * R / 2;
                auto pp1 = p_2 - normal * R / 2;
                p0 = { pp0.x, pp0.y, 0 };
                p1 = { pp1.x, pp1.y, 0 };
            }
        }

        // Here we combine the age of the line and the pressure to fade out
        // the line via an opacity change.
        float pressure = e.pressure();

        ofColor c0, c1;

        // Here we color the points based on the point type.
        c0 = c1 = ofColor(strokeColor, pressure * 255);

        mesh.addVertex(p0);
        mesh.addColor(c0);
        mesh.addVertex(p1);
        mesh.addColor(c1);
    }

    return mesh;
}


void Renderer::draw(const Stroke& stroke, ofPolyRenderMode renderType) const
{
    generateMesh(stroke, ofGetStyle().color).draw(renderType);
}


void Renderer::drawDebug(const Stroke& stroke,
                         float normalLength,
                         float tangenLength) const
{
    ofMesh line;
    ofMesh normals;
    ofMesh tangents;

    line.setMode(OF_PRIMITIVE_LINES);
    normals.setMode(OF_PRIMITIVE_LINES);
    tangents.setMode(OF_PRIMITIVE_LINES);

    for (std::size_t i = 0; i < stroke.size(); ++i)
    {
        auto n = stroke.normalAtIndex(i);
        auto t = stroke.tangentAtIndex(i);
        auto v = stroke.positionAtIndex(i);

        if (i != 0)
        {
            line.addVertex(v);
            line.addColor(ofColor::white);
        }

        line.addVertex(v);
        line.addColor(ofColor::white);

        normals.addVertex(v);
        normals.addColor(ofColor::white);
        normals.addVertex(v + n * normalLength);
        normals.addColor(ofColor::red);
        normals.addVertex(v);
        normals.addColor(ofColor::white);
        normals.addVertex(v - n * normalLength);
        normals.addColor(ofColor::green);


        tangents.addVertex(v);
        tangents.addColor(ofColor::white);
        tangents.addVertex(v + t * normalLength);
        tangents.addColor(ofColor::purple);
        tangents.addVertex(v);
        tangents.addColor(ofColor::white);
        tangents.addVertex(v - t * normalLength);
        tangents.addColor(ofColor::yellow);

    }

    line.draw();
    normals.draw();
    tangents.draw();
}


Renderer::Settings Renderer::settings() const
{
    return _settings;
}


} } // namespace ofx::Pen
