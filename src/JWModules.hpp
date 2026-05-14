#pragma once
#include "rack.hpp"
#include <functional>
#include <algorithm>

using namespace rack;
extern Plugin *pluginInstance;

inline int clampijw(int x, int minimum, int maximum) {
	return clamp(x, minimum, maximum);
}
inline float clampfjw(float x, float minimum, float maximum) {
	return fminf(fmaxf(x, minimum), maximum);
}
inline float rescalefjw(float x, float xMin, float xMax, float yMin, float yMax) {
	return yMin + (x - xMin) / (xMax - xMin) * (yMax - yMin);
}

struct Screw_J : SVGScrew {
	Screw_J() {
		sw->setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Screw_J.svg")));
		box.size = sw->box.size;
	}
};

struct Screw_W : SVGScrew {
	Screw_W() {
		sw->setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Screw_W.svg")));
		box.size = sw->box.size;
	}
};

extern Model *modelRnboHelpDelay;
extern Model *modelRnboNedKick;
extern Model *modelRnboRandom8;
extern Model *modelRnboNedLFO1;
extern Model *modelRnboNedRepeat;

