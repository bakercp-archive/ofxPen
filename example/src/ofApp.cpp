//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    ofx::RegisterPointerEvents(this);

    ii = 0;

    std::string filenameWPI = ofToDataPath("test_sketch.wpi", true);

    ofEnableAlphaBlending();

    dpen::DPError error = dpen::DP_SUCCESS;

    dpen::DPDeserializer deserializer;

    error = deserializer.deserialize(filenameWPI, sketch);

    if (!error)
    {
        //std::cout << sketch.toString() << std::endl;
    }
    else
    {
        ofLogError("ofApp::setup()") << "Error loading : " << filenameWPI;
    }

}


void ofApp::update()
{
}


void ofApp::draw()
{

    ofBackground(0);

    ii+=1.9;

    ofPushMatrix();
    ofTranslate(mouseX, mouseY-250);
    ofScale(.5,.5);

    std::vector<dpen::DPTraceGroup>& layers = sketch.getLayersRef();
    std::vector<dpen::DPTraceGroup>::iterator layersIter = layers.begin();

//    ofSeedRandom(2939);

//    std::cout << "NUM LAYERS = " << layers.size() << std::endl;

    while (layersIter != layers.end())
    {
        std::vector<dpen::DPTrace>& traces = (*layersIter).getTracesRef();
        std::vector<dpen::DPTrace>::iterator tracesIter = traces.begin();

//        std::cout << "\tNUM TRACES = " << traces.size() << std::endl;

        ofColor color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));

        while (tracesIter != traces.end())
        {
            std::vector<dpen::DPTracePoint>& points = (*tracesIter).getPointsRef();
            std::vector<dpen::DPTracePoint>::iterator pointsIter = points.begin();

//            cout << "\t\tNUM PTS = " << points.size() << endl;


//            ofMesh line;
//            ofMesh pts;
//
//            line.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
////            pts.setMode(OF_PRIMITIVE_POINTS);
//            ofSetColor(color);
//


            ofPolyline poly;

            std::vector<ofx::Point> pts;

            while (pointsIter != points.end())
            {
                dpen::DPTracePoint& point = (*pointsIter);

                ofVec2f position(point.getX(), point.getY());

                poly.addVertex(position);

                ofx::Point sp(position,
                              point.getPressure(),
                              point.getTiltX(),
                              point.getTiltY());

                pts.push_back(sp);

//                ofColor thisColor = color;
//
//                float map = ofMap(point.getPressure(), 0, 1023, 0, 1);
//
////                color.lerp(ofColor(255,0,0),map);
//
//                color.a = map * 255;

//                line.addColor(color);
//                line.addVertex(ofVec2f(point.getX(),point.getY()));
//                line.addNormal(ofVec2f(point.getTiltX(),point.getTiltY()));

//                pts.addColor(ofColor::yellow);;
//                pts.addVertex(ofVec2f(point.getX(),point.getY()));

//                if(pointsIter == points.begin())
//                {
//                    ofNoFill();
////                ofCircle(point.getX(),point.getY(),10);
//                }

               ++pointsIter;
            }

            poly.draw();

            std::vector<ofVec2f> p;
            std::vector<ofVec2f> t;

            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);


//            mesh.drawWireframe();
            mesh.draw();



//            line.draw();
//            pts.draw();
//            line.getN
//            line.add
           ++tracesIter;
        }

        ++layersIter;
    }

    ofPopMatrix();
}


void ofApp::keyPressed(int key)
{
}


void ofApp::onPointerDown(PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerDown") << evt.toString();
}


void ofApp::onPointerUp(PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerUp") << evt.toString();
}


void ofApp::onPointerMove(PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerMove") << evt.toString();
}


void ofApp::onPointerCancel(PointerEventArgs& evt)
{
    ofLogVerbose("ofApp::onPointerCancel") << evt.toString();
}
