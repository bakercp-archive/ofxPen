//
//  StrokePoint.h
//  example
//
//  Created by Christopher P. Baker on 10/25/13.
//
//

#pragma


#include "ofVec2f.h"


class StrokePoint
{
public:
    float   pressure;
    ofVec2f tilt;
    ofVec2f position;
    ofVec2f tangent;
    ofVec2f normal;
    ofVec2f velocity;

};