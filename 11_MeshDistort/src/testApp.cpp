#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	glEnable(GL_DEPTH_TEST);

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(66,66,66);

	//initialize the video grabber
	vidGrabber.initGrabber(320,240);

	//this determines how much we push the meshes out
	extrusionAmount = 300.0;

	//store the width and height for convenience
	int width = vidGrabber.getWidth();
	int height = vidGrabber.getHeight();

	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
			// this replicates the pixel array within the camera bitmap...
			mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
		}
	}
	
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){
			mainMesh.addIndex(x+y*width);				// 0
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex(x+(y+1)*width);			// 10
			
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex((x+1)+(y+1)*width);		// 11
			mainMesh.addIndex(x+(y+1)*width);			// 10
		}
	}

}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.update();
	if (vidGrabber.isFrameNew()){
		//this determines how far we extrude the mesh
		for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){
			
			ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
									 vidGrabber.getPixels()[i*3+1]/255.f,			// g
									 vidGrabber.getPixels()[i*3+2]/255.f);			// b
			//now we get the vertex aat this position
			//we extrude the mesh based on it's brightness
			ofVec3f& vert = mainMesh.getVertices()[i];
			vert.z = sampleColor.getBrightness() * extrusionAmount;
//			mainMesh.setVertex(i, tmpVec);
			
			mainMesh.setColor(i, sampleColor);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//You can either draw the mesh or the wireframe
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2- vidGrabber.getWidth()/2, ofGetHeight()/2-vidGrabber.getHeight()/2);
	ofRotate(ofGetMouseY(), 1, 0, 0);
	mainMesh.drawFaces();
	ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}