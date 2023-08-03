#include "ofApp.h"
#include "ofGraphicsUtil.h"
using namespace glm;

//--------------------------------------------------------------
// Add a rectangle lying on the xy plane centered around the given position
static void addRect(ofMesh& m, glm::vec3 pos, float w = 2.f, float h = 2.f){
    float w_2 = w*0.5;
    float h_2 = h*0.5;
    int Nv = m.getVertices().size();
    m.setMode(OF_PRIMITIVE_TRIANGLES);
    m.addVertex(pos + vec3(- w_2 , -h_2 , 0.));
    m.addVertex(pos + vec3( w_2 , -h_2 , 0.));
    m.addVertex(pos + vec3( w_2 , h_2 , 0.));
    m.addVertex(pos + vec3(- w_2 , h_2 , 0.));
    m.addTexCoord(vec2(0, 0));
    m.addTexCoord(vec2(1, 0));
    m.addTexCoord(vec2(1, 1));
    m.addTexCoord(vec2(0, 1));
    m.addTriangle(Nv+0, Nv+1, Nv+2);
    m.addTriangle(Nv+0, Nv+2, Nv+3);
}

//--------------------------------------------------------------
void ofApp::setup(){
    // Setup camera
    cam.setPosition(vec3(0., 4., -16.));
    cam.setTarget(vec3(0., 5., 0.));
    cam.setNearClip(0.05);
    cam.setFarClip(100.);
    
    ofEnableNormalizedTexCoords();
    ofEnableDepthTest();
    ofDisableArbTex();
    
    //load the shader files in bin
    shader.load("shaders/shader");
    pointSpriteShader.load("shaders/pointSprite");
    
    //random point sprites
    for(int i =0; i<100; ++i){
        auto p = vec3(ofRandom(20.), ofRandom(20.), ofRandom (20.)) - 10.f;
        addRect(pointSprites, p, 0,0);
    }
    
    //load the image
    if (!image.load("greencrystal.jpg"))
        std :: cout << " Error loading image from file." << std :: endl;

    if (!imageSliverCrystal.load("pinkcrystal.jpeg"))
        std :: cout << " Error loading image from file." << std :: endl;

    //3D models
    sphereMesh = ofMesh :: sphere(0.8, 2);
    sphereMesh2 = ofMesh :: sphere(1, 2);
    
    modelMesh.load("bunny.ply");
    if(!modelMesh.hasVertices()) std::cout << "Error loading model file" << std::endl;
   
    envirMesh = ofMesh::sphere(cam.getFarClip()*0.5);
    if(!envirMap.load("sunset.jpg")) std::cout << "Error loading envir map" << std::endl;
    
    voice.load("irenehipass.wav");
  
}

//--------------------------------------------------------------
void ofApp::update(){
//    printf("frame:%u dt:%f\n", (unsigned)ofGetFrameNum(), ofGetLastFrameTime());
//    cout << "MousePos x:" << ofGetMouseX() << " y:" << ofGetMouseY() << endl;
    if(rotate == true){
        sphereRotation += (float) ofGetLastFrameTime()/2;
        sphereRotation2 += (float) ofGetLastFrameTime();
    }
    //    cout << sphereRotation << endl;
    //lightRotation += 0.1;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofDrawBitmapString("both strong and soft", ofGetMouseX(), ofGetMouseY());
    ofDrawBitmapString("both deep and naive", 540, 60);
    ofDrawBitmapString("both happy and sad", 20, 160);
    ofDrawBitmapString("both mature and young", 120, 300);
    ofDrawBitmapString("both sober and lost", 420, 360);
    ofDrawBitmapString("both charming and hazardous", 166, 430);
    ofDrawBitmapString("both masculine and feminine", 330, 550);
    ofDrawBitmapString("both romantic and pragmatic", 430, 20);
    ofDrawBitmapString("both confident and inferior", 530, 500);
    ofDrawBitmapString("if i had a choice, i don't want to know you", 460, 160);
   
    ofSetColor(255, 200, 200);
    ofDrawBitmapString("Press Space Bar to stop the crytals", 2, 566);
    ofDrawBitmapString("Move the mouse to play the voice", 2, 580);
    cam.begin();
    //draw the first shader
    shader.begin();
    shader.setUniform1f("appTime", ofGetFrameNum()/ofGetFrameRate());
    shader.setUniform3f("eye", cam.getPosition());
    //    shader.setUniformTexture("envirMap", envirMap, 0); //for the reflection
    float x = cos(sphereRotation) * sphereDistance;
    float y = sin(sphereRotation) * sphereDistance;
    shader.setUniform3f("lightPosition", vec3(x, 0, y));
   
    modelMesh.draw();
  
    //shader.setUniformTexture("tex", image, 0);
    shader.setUniform1f ("texturing", 1.);
    
    ofPushMatrix();
    ofTranslate(x, 0, y);
    image.bind();
    sphereMesh.draw();
    image.unbind();
    ofPopMatrix();
    
    ofPushMatrix();
    float a = cos(sphereRotation2) * sphereDistance2;
    float b = sin(sphereRotation2) * sphereDistance2;
    ofTranslate(a, b, 0);
    imageSliverCrystal.bind();
    sphereMesh2.draw();
    imageSliverCrystal.unbind();
    ofPopMatrix();
    
    shader.end();
    
    //draw the second shader
    glDepthMask(GL_FALSE);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    pointSpriteShader.begin();
    pointSpriteShader.setUniformMatrix4f("cameraMatrix", cam.getLocalTransformMatrix());
    pointSpriteShader.setUniform1f("spriteRadius", 0.5);
    pointSprites.draw();
    pointSpriteShader.end();
    
    ofDisableBlendMode();
    glDepthMask(GL_TRUE);
    
    envirMap.bind();
    envirMesh.draw();
    envirMap.unbind();

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //space bar to stop and rerun the crystal
    if(key == 32){
        rotate = !rotate;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    if(x > 0){
        voice.play();
        voice.setVolume(x*y/8000); //Sets volume at 10% of maximum
    }
    
    if(y < 100){
        voice.stop();
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
