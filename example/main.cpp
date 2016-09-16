#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"
#include "../src/actor.hpp"
#include "../src/action.hpp"
#include "../src/scorer.hpp"
#include "../src/action_data.hpp"


struct vector{
	float x;
	float y;

	vector(float x=0,float y=0):x(x),y(y){}

	vector& operator+=(const vector& rhs){
		x+=rhs.x;
		y+=rhs.y;
		return *this;
	}
	friend vector operator+(vector lhs,const vector& rhs){
		lhs+=rhs;
		return lhs;
	}

	vector& operator-=(const vector& rhs){
		x-=rhs.x;
		y-=rhs.y;
		return *this;
	}
	friend vector operator-(vector lhs,const vector& rhs){
		lhs-=rhs;
		return lhs;
	}

	vector& operator*=(const float& rhs){
		x*=rhs;
		y*=rhs;
		return *this;
	}
	friend vector operator*(vector lhs,const float& rhs){
		lhs*=rhs;
		return lhs;
	}
};

inline bool operator==(const vector& lhs,const vector& rhs){return lhs.x==rhs.x && lhs.y==rhs.y;}
inline bool operator!=(const vector& lhs, const vector& rhs){return !(lhs == rhs); }


struct unit:public utility_ai::actor{
	vector position;
	vector velocity;

	unit(const std::shared_ptr<utility_ai::decider> &actor_ai) : actor(actor_ai) {}

	virtual void update(float dt){
		utility_ai::actor::update();
		position += velocity*dt;
	}

	void render(NVGcontext* vg){
		nvgBeginPath(vg);
		nvgRect(vg,position.x-50,position.y-50,100,100);
		nvgFillColor(vg,NVGcolor{1,1,1,1});
		nvgFill(vg);
	}

};

static float dist(const vector& a, const vector& b){
	return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
static float length(const vector& a){
	return std::sqrt((a.x*a.x)+(a.y*a.y));
}
static vector nomalize(const vector& a){
	return a*(1.0f/length(a));
}

class patrole : public utility_ai::action{
private:
	vector p1;
	vector p2;
	bool to1;
public:
	patrole(const vector& p1, const vector& p2):p1(p1),p2(p2),to1(true){

	}
	virtual bool execute(utility_ai::actor &a) override {
		auto& u = static_cast<unit&>(a);
		if(to1) {
			auto velo = nomalize(p1-u.position);
			u.velocity = velo*30.f;
			if(dist(u.position,p1)<40.f){
				to1 = false;
				u.velocity = nomalize(p2-u.position)*30.f;
			}
		} else{
			u.velocity = nomalize(p2-u.position)*30.f;
			if(dist(u.position,p2)<40.f){
				to1 = true;
				u.velocity = nomalize(p1-u.position)*30.f;
			}
		}
		return true;
	}

	virtual bool start(utility_ai::actor &a) override {
		return true;
	}
};

class chase_mouse : public utility_ai::action{
private:
	GLFWwindow* window;
public:
	chase_mouse(GLFWwindow* window):window(window){

	}
	virtual bool execute(utility_ai::actor &a) override {
		auto& u = static_cast<unit&>(a);
		double x;
		double y;

		glfwGetCursorPos(window,&x,&y);
		vector mouse_pos(x,y);
		auto velo = nomalize(mouse_pos-u.position);
		u.velocity = velo*30.f;
		return true;
	}

	virtual bool start(utility_ai::actor &a) override {
		return true;
	}
};
class mouse_distance : public utility_ai::scorer {
private:
	GLFWwindow* window;
	float distance;
public:
	mouse_distance(GLFWwindow* window,float distance):window(window),distance(distance){

	}
	virtual int score(const utility_ai::actor &a) const override {
		auto& u = static_cast<const unit&>(a);
		double x;
		double y;

		glfwGetCursorPos(window,&x,&y);
		vector mouse_pos(x,y);
		if(distance > dist(mouse_pos,u.position)){
			return 100;
		}
		return 0;
	}
};



int main()
{
	GLFWwindow* window;
	NVGcontext* vg = NULL;
	double prevt = 0, cpuTime = 0;

	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	//glfwSetErrorCallback(errorcb);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	window = glfwCreateWindow(1000, 600, "NanoVG", NULL, NULL);
//	window = glfwCreateWindow(1000, 600, "NanoVG", glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		printf("Could not init glew.\n");
		return -1;
	}
	// GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
	glGetError();


	vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}


	glfwSwapInterval(0);

	glfwSetTime(0);
	prevt = glfwGetTime();

	auto patrole_action = std::make_unique<patrole>(vector{200.f,200.f},vector{500.f,200.f});
	std::shared_ptr<utility_ai::decider> default_ai = std::make_shared<utility_ai::decider>(std::move(patrole_action));
	default_ai->add_action<chase_mouse>(window)->add_scorer<mouse_distance>(window,100);
	unit test_unit(default_ai);
	test_unit.position.y = 200.f;

	while (!glfwWindowShouldClose(window))
	{
		double mx, my, t, dt;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;
		float gpuTimes[3];
		int i, n;

		t = glfwGetTime();
		dt = t - prevt;
		prevt = t;


		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

		test_unit.update(dt);
		test_unit.render(vg);

		nvgEndFrame(vg);

		// Measure the CPU time taken excluding swap buffers (as the swap may wait for GPU)
		cpuTime = glfwGetTime() - t;


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	nvgDeleteGL3(vg);
	glfwTerminate();
	return 0;
}