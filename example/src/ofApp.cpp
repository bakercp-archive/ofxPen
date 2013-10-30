// =============================================================================
//
// Copyright (c) 2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"
#include <Cocoa/Cocoa.h>


//------------------------------------------------------------------------------
void ofApp::setup()
{

    ii = 0;

    void* window = ofGetWindowPtr()->getCocoaWindow();

    NSWindow * appWindow = (NSWindow *)ofGetCocoaWindow();
	if(appWindow)
    {
//		[appWindow makeKeyAndOrderFront:nil];
	}

    std::string filenameWPI = ofToDataPath("test_sketch.wac",true);

    ofEnableAlphaBlending();

    DPError error = DP_SUCCESS;

    DPDeserializer deserializer;

    error = deserializer.deserialize(filenameWPI, sketch);

    if(!error)
    {
        //std::cout << sketch.toString() << std::endl;
    }
    else
    {
        ofLogError("ofApp::setup()") << "Error loading : " << filenameWPI;
    }

//    ofExit();
}

//------------------------------------------------------------------------------
void ofApp::update()
{
}

//------------------------------------------------------------------------------
void ofApp::draw()
{

    ofBackground(0);

    ii+=1.9;

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,-50);
    ofScale(1.5,1.5);

    std::vector<DPTraceGroup>& layers = sketch.getLayersRef();
    std::vector<DPTraceGroup>::iterator layersIter = layers.begin();

//    ofSeedRandom(2939);

//    std::cout << "NUM LAYERS = " << layers.size() << std::endl;

    while(layersIter != layers.end())
    {
        std::vector<DPTrace>& traces = (*layersIter).getTracesRef();
        std::vector<DPTrace>::iterator tracesIter = traces.begin();

//        std::cout << "\tNUM TRACES = " << traces.size() << std::endl;

        ofColor color = ofColor::white;//ofColor(ofRandom(255),ofRandom(255),ofRandom(255));

        while(tracesIter != traces.end())
        {
            std::vector<DPTracePoint>& points = (*tracesIter).getPointsRef();
            std::vector<DPTracePoint>::iterator pointsIter = points.begin();

//            cout << "\t\tNUM PTS = " << points.size() << endl;


//            ofMesh line;
//            ofMesh pts;
//
//            line.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
////            pts.setMode(OF_PRIMITIVE_POINTS);
//            ofSetColor(color);
//


            ofPolyline poly;

            std::vector<StrokePoint> pts;

            while(pointsIter != points.end())
            {
                DPTracePoint& point = (*pointsIter);

                float pressure = point.getPressure();
                ofVec2f position(point.getX(),point.getY());
                ofVec2f tilt(ofVec2f(point.getTiltX(),point.getTiltY()));

                poly.addVertex(position);

                 StrokePoint sp;

                sp.position = position;
                sp.tilt = tilt;
                sp.pressure = pressure;

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

//            poly.draw();

            std::vector<ofVec2f> p;
            std::vector<ofVec2f> t;

            ofMesh mesh;
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);


            for(std::size_t i = 0; i < poly.size(); ++i)
            {
                ofVec3f pp = poly[i];
                ofVec3f nn = poly.getNormalAtIndex(i);
                ofVec3f tt = poly.getTangentAtIndex(i);

                pts[i].tangent = tt;
                pts[i].normal = nn;

//                cout <<pts[i].tilt.length() << endl;


                ofColor thisColor = color;
                //
                float map = ofMap(pts[i].tilt.length(), 0, 69, .1, 7);
//                color.lerp(ofColor(255,255,0,127),map);

//                color.a = map * 255;

//                if(i % 2 == 0)
//                {
//                    mesh.addVertex(pp-(nn*map*ofNoise(ii+i)));
//                }
//                else
//                {
//                    mesh.addVertex(pp+(nn*map*ofNoise(ii+i)));
//                }

                mesh.addColor(color);

            }

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

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//------------------------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//------------------------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//------------------------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
