//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier: MIT
//


#pragma once


#include "ofMain.h"
#include "ofxPen.h"
#include "ofxPointer.h"


class ofApp: public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;

    void pointerUp(ofx::PointerEventArgs& evt);
    void pointerDown(ofx::PointerEventArgs& evt);
    void pointerMove(ofx::PointerEventArgs& evt);
    void pointerCancel(ofx::PointerEventArgs& evt);

    float ii;

    dpen::DPSketch sketch;

    ofMesh mesh;

};
