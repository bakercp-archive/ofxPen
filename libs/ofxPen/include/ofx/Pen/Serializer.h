//
// Copyright (c) 2019 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofMath.h"
#include "ofx/Pen/Point.h"
#include "ofx/Pen/Stroke.h"
#include "ofx/Pen/StrokeProject.h"
#include "ofx/Pen/StrokeSet.h"
#include "ofxSerializer.h"
#include "json.hpp"
#include "pugixml.hpp"


namespace ofx {
namespace Pen {


inline void to_json(nlohmann::json& j, const Point& v)
{
    // We only serialize if the value is non-zero.
    if (!ofIsFloatEqual(v.position().x, 0.0f))
        j["x"] = v.position().x;

    if (!ofIsFloatEqual(v.position().y, 0.0f))
        j["y"] = v.position().y;

    if (!ofIsFloatEqual(v.position().z, 0.0f))
        j["z"] = v.position().z;

    if (!ofIsFloatEqual(v.timestampSeconds(), 0.0))
        j["timestamp"] = v.timestampSeconds();

    if (!ofIsFloatEqual(v.pressure(), 0.5f))
        j["pressure"] = v.pressure();

    if (!ofIsFloatEqual(v.tangentialPressure(), 0.0f))
        j["tangential_pressure"] = v.tangentialPressure();

    if (!ofIsFloatEqual(v.twistDeg(), 0.0f))
        j["twist_deg"] = v.twistDeg();

    if (!ofIsFloatEqual(v.tiltXDeg(), 0.0f))
        j["tilt_x_deg"] = v.tiltXDeg();

    if (!ofIsFloatEqual(v.tiltYDeg(), 0.0f))
        j["tilt_y_deg"] = v.tiltYDeg();
}


inline void from_json(const nlohmann::json& j, Point& v)
{
    v = Point(glm::vec3(j.value("x", 0.0f),
                        j.value("y", 0.0f),
                        j.value("z", 0.0f)),
               j.value("timestamp", 0.0),
               j.value("pressure", 0.5f),
               j.value("tangential_pressure", 0.0f),
               j.value("twist_deg", 0.0f),
               j.value("tilt_x_deg", 0.0f),
               j.value("tilt_y_deg", 0.0f));
}


inline void to_xml_attributes(pugi::xml_node& n, const Point& v)
{
    if (!ofIsFloatEqual(v.position().z, 0.0f))
        n.append_attribute("x") = v.position().x;

    if (!ofIsFloatEqual(v.position().y, 0.0f))
        n.append_attribute("y") = v.position().y;

    if (!ofIsFloatEqual(v.position().z, 0.0f))
        n.append_attribute("z") = v.position().z;

    if (!ofIsFloatEqual(v.timestampSeconds(), 0.0))
        n.append_attribute("timestamp") = v.timestampSeconds();

    if (!ofIsFloatEqual(v.pressure(), 0.0f))
        n.append_attribute("pressure") = v.pressure();

    if (!ofIsFloatEqual(v.tangentialPressure(), 0.0f))
        n.append_attribute("tangential_pressure") = v.tangentialPressure();

    if (!ofIsFloatEqual(v.twistDeg(), 0.0f))
        n.append_attribute("twist_deg") = v.twistDeg();

    if (!ofIsFloatEqual(v.tiltXDeg(), 0.0f))
        n.append_attribute("tilt_x_deg") = v.tiltXDeg();

    if (!ofIsFloatEqual(v.tiltYDeg(), 0.0f))
        n.append_attribute("tilt_y_deg") = v.tiltYDeg();
}


inline void from_xml_attributes(const pugi::xml_node& j, Point& v)
{
    v = Point(glm::vec3(j.attribute("x").as_float(0.0f),
                        j.attribute("y").as_float(0.0f),
                        j.attribute("z").as_float(0.0f)),
              j.attribute("timestamp").as_double(0.0),
              j.attribute("pressure").as_float(0.0f),
              j.attribute("tangential_pressure").as_float(0.0f),
              j.attribute("twist_deg").as_float(0.0f),
              j.attribute("tilt_x_deg").as_float(0.0f),
              j.attribute("tilt_x_deg").as_float(0.0f));
}


inline void to_json(nlohmann::json& j, const Stroke& v)
{
    j["points"] = v.points();
}


inline void from_json(const nlohmann::json& j, Stroke& v)
{
    v = Stroke(j.value("points", std::vector<Point>()));
}


inline void to_json(nlohmann::json& j, const StrokeSet& v)
{
    j["strokes"] = v.strokes;
    j["attributes"] = v.attributes;
}


inline void from_json(const nlohmann::json& j, StrokeSet& v)
{
    v.strokes = j.value("strokes", std::vector<Stroke>());
    v.attributes = j.value("attributes", std::map<std::string, std::string>());
}


inline void to_json(nlohmann::json& j, const StrokeProject& v)
{
    j["strokes"] = v.strokes();
    j["stroke_sets"] = v.strokeSets();
}


inline void from_json(const nlohmann::json& j, StrokeProject& v)
{
    v = StrokeProject(j.value("strokes", std::vector<Stroke>()),
                      j.value("stroke_sets", std::vector<StrokeSet>()));
}


inline void to_json(nlohmann::json& j, const Renderer::Settings& v)
{
    j["minimum_stroke_width"] = v.minimumStrokeWidth;
    j["maximum_stroke_width"] = v.maximumStrokeWidth;
    j["point_color"] = v.pointColor;
}


inline void from_json(const nlohmann::json& j, Renderer::Settings& v)
{
    v.minimumStrokeWidth = j.value("minimum_stroke_width", 5.0f);
    v.maximumStrokeWidth = j.value("maximum_stroke_width", 10.0f);
    v.pointColor = j.value("point_color", ofColor(255));
}


} } // namespace ofx::Pen
