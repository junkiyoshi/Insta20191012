#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->base_mesh = ico_sphere.getMesh();
	for (auto& point : this->base_mesh.getVertices()) {

		base_mesh.addColor(ofColor(0, 0, 0));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh = this->base_mesh;
	for (int i = 0; i < this->draw_mesh.getVertices().size(); i++) {

		auto point = this->draw_mesh.getVertices()[i];
		int noise_value = (int)ofMap(ofNoise(point.x * 0.005, point.y * 0.005, point.z * 0.005, ofGetFrameNum() * 0.005), 0, 1, 5, 10);
		this->draw_mesh.getVertices()[i] = glm::normalize(point) * 300 * noise_value * 0.1;

		switch (noise_value) {
		case 5:
			this->draw_mesh.setColor(i, ofColor(0, 0, 128));
			break;
		case 6:
			this->draw_mesh.setColor(i, ofColor(90, 144, 255));
			break;
		case 7:
			this->draw_mesh.setColor(i, ofColor(80, 0, 0));
			break;
		case 8:
			this->draw_mesh.setColor(i, ofColor(0, 100, 0));
			break;
		case 9:
			this->draw_mesh.setColor(i, ofColor(128, 128, 128));
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.35);

	this->draw_mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}