#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void addQuad(ofMesh& m, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, ofFloatColor col = ofFloatColor(1));
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
 
		ofEasyCam cam;
		ofShader shader;
        ofShader pointSpriteShader;
		ofMesh mesh;
        ofVboMesh modelMesh;

        ofVboMesh envirMesh;
        ofImage envirMap;
    
        ofMesh pointSprites;
        ofMesh sphereMesh;
        ofMesh sphereMesh2;
   
        ofImage image;
        ofImage imageSliverCrystal;

        float sphereRotation = 0;
        float sphereDistance = 10;
    
        float sphereRotation2 = 0;
        float sphereDistance2 = 10;
    
        float lightRotation = 0;
        float lightDistance = 20;
    
        float camRotation = 0;
        float camDistance = 16;
    
        bool rotate = true;
       
        ofSoundPlayer voice;
    
};
