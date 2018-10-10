//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxPen.h"
#include "ofxPointer.h"


using namespace ofx;


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);

    void onPointerUp(PointerEventArgs& evt);
    void onPointerDown(PointerEventArgs& evt);
    void onPointerMove(PointerEventArgs& evt);
    void onPointerCancel(PointerEventArgs& evt);

    float ii;

    dpen::DPSketch sketch;

    ofMesh mesh;

};
