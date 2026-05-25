#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic GraiNed_rnbomatic
#define rnbomaticFactoryFunction graiNedFactoryFunction
#define rnbomaticSetLogger graiNedSetLogger
#include "../lib/GraiNed/GraiNed.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct GraiNed : Module {
	enum ParamIds {
		PITCH_PARAM,
		GO_PARAM,
		START_PARAM,
		LENGTH_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		LEFT_INPUT,
		RIGHT_INPUT,
		PITCH_CV_INPUT,
		GO_CV_INPUT,
		START_CV_INPUT,
		LENGTH_CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		LEFT_OUTPUT,
		RIGHT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::GraiNed_rnbomatic<> *graiNedEngine = nullptr;
	bool rnboInitialized = false;
	double lastPitch = 1.0;
	double lastGo = 0.0;
	double lastStart = 0.0;
	double lastLength = 100.0;

	GraiNed() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(PITCH_PARAM, -4.f, 4.f, 1.f, "Pitch");
		configParam(GO_PARAM, 0.f, 1.f, 0.f, "Go");
		configParam(START_PARAM, 0.f, 1500.f, 0.f, "Start");
		configParam(LENGTH_PARAM, 1.f, 500.f, 100.f, "Length");
		configInput(LEFT_INPUT, "Left In");
		configInput(RIGHT_INPUT, "Right In");
		configInput(PITCH_CV_INPUT, "Pitch CV");
		configInput(GO_CV_INPUT, "Go CV");
		configInput(START_CV_INPUT, "Start CV");
		configInput(LENGTH_CV_INPUT, "Length CV");
		configOutput(LEFT_OUTPUT, "Left Out");
		configOutput(RIGHT_OUTPUT, "Right Out");
		graiNedEngine = new RNBO::GraiNed_rnbomatic<>();
	}

	~GraiNed() {
		if (graiNedEngine) {
			delete graiNedEngine;
			graiNedEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && graiNedEngine) {
			graiNedEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!graiNedEngine) return;

		if (!rnboInitialized) {
			graiNedEngine->initialize();
			graiNedEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		double pitch = (double)params[PITCH_PARAM].getValue();
		double go = (double)params[GO_PARAM].getValue();
		double start = (double)params[START_PARAM].getValue();
		double length = (double)params[LENGTH_PARAM].getValue();

		if (inputs[PITCH_CV_INPUT].isConnected()) {
			double pitchCV = (double)inputs[PITCH_CV_INPUT].getVoltage() / 2.0;
			pitch = clampd(pitch + pitchCV, -4.0, 4.0);
		}
		if (inputs[GO_CV_INPUT].isConnected()) {
			double goCV = (double)inputs[GO_CV_INPUT].getVoltage() / 10.0;
			go = clampd(go + goCV, 0.0, 1.0);
		}
		if (inputs[START_CV_INPUT].isConnected()) {
			double startCV = (double)inputs[START_CV_INPUT].getVoltage() / 10.0;
			start = clampd(start + startCV * 1500.0, 0.0, 1500.0);
		}
		if (inputs[LENGTH_CV_INPUT].isConnected()) {
			double lengthCV = (double)inputs[LENGTH_CV_INPUT].getVoltage() / 10.0;
			length = clampd(length + lengthCV * 499.0, 1.0, 500.0);
		}

		if (pitch != lastPitch) {
			graiNedEngine->setParameterValue(0, pitch, 0);
			lastPitch = pitch;
		}
		if (go != lastGo) {
			graiNedEngine->setParameterValue(1, go, 0);
			lastGo = go;
		}
		if (start != lastStart) {
			graiNedEngine->setParameterValue(2, start, 0);
			lastStart = start;
		}
		if (length != lastLength) {
			graiNedEngine->setParameterValue(3, length, 0);
			lastLength = length;
		}

		double inLeft = inputs[LEFT_INPUT].isConnected() ? (double)inputs[LEFT_INPUT].getVoltage() / 5.0 : 0.0;
		double inRight = inputs[RIGHT_INPUT].isConnected() ? (double)inputs[RIGHT_INPUT].getVoltage() / 5.0 : 0.0;
		double outLeft = 0.0;
		double outRight = 0.0;
		double *rnboInputs[2] = {&inLeft, &inRight};
		double *rnboOutputs[2] = {&outLeft, &outRight};

		graiNedEngine->process(rnboInputs, 2, rnboOutputs, 2, 1);

		outputs[LEFT_OUTPUT].setVoltage(clamp((float)outLeft * 5.f, -10.f, 10.f));
		outputs[RIGHT_OUTPUT].setVoltage(clamp((float)outRight * 5.f, -10.f, 10.f));
		outputs[LEFT_OUTPUT].setChannels(1);
		outputs[RIGHT_OUTPUT].setChannels(1);
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
	}

	void onReset() override {
		rnboInitialized = false;
	}

	void onRandomize() override {
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// WIDGET
///////////////////////////////////////////////////////////////////////////////////////////////////

struct GraiNedWidget : ModuleWidget {
	GraiNedWidget(GraiNed *module);
	~GraiNedWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

GraiNedWidget::GraiNedWidget(GraiNed *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 8, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/GraiNed.svg"),
		asset::plugin(pluginInstance, "res/GraiNed.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 365)));

	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 67.f), module, GraiNed::PITCH_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 67.f), module, GraiNed::PITCH_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 107.f), module, GraiNed::GO_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 107.f), module, GraiNed::GO_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 147.f), module, GraiNed::START_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 147.f), module, GraiNed::START_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 187.f), module, GraiNed::LENGTH_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 187.f), module, GraiNed::LENGTH_CV_INPUT));

	addInput(createInputCentered<PJ301MPort>(Vec(25.f, 304.f), module, GraiNed::LEFT_INPUT));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 304.f), module, GraiNed::RIGHT_INPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(25.f, 346.f), module, GraiNed::LEFT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(65.f, 346.f), module, GraiNed::RIGHT_OUTPUT));
}

void GraiNedWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelGraiNed = createModel<GraiNed, GraiNedWidget>("GraiNed");
