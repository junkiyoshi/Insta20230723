#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 60 < 30) {

		this->noise_param += ofMap(ofGetFrameNum() % 30, 0, 30, 0.2, 0.0001);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2);

	int R = 235;
	int r = 60;
	int v_span = 5;
	int u_span = 10;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor face_color = ofColor(255);
	ofColor line_color = ofColor(0);

	for (int v = 0; v < 360; v += v_span) {

		for (int u = 0; u < 360; u += u_span) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, 100, u, v) * 0.003, this->noise_param));
			auto param = noise_value > 0.45 ? noise_value < 0.55 ? ofMap(noise_value, 0.45, 0.55, 1, 0) : 0 : 1;
			auto v_size = v_span * param;
			auto u_size = u_span * param;

			face.addVertex(this->make_point(R, r, u - u_size * 0.5, v - v_size * 0.5));
			face.addVertex(this->make_point(R, r, u + u_size * 0.5, v - v_size * 0.5));
			face.addVertex(this->make_point(R, r, u + u_size * 0.5, v + v_size * 0.5));
			face.addVertex(this->make_point(R, r, u - u_size * 0.5, v + v_size * 0.5));

			line.addVertex(this->make_point(R, r, u - u_size * 0.5, v - v_size * 0.5));
			line.addVertex(this->make_point(R, r, u + u_size * 0.5, v - v_size * 0.5));
			line.addVertex(this->make_point(R, r, u + u_size * 0.5, v + v_size * 0.5));
			line.addVertex(this->make_point(R, r, u - u_size * 0.5, v + v_size * 0.5));

			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);

			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
			line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}