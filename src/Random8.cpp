#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic Random8_rnbomatic
#define rnbomaticFactoryFunction random8FactoryFunction
#define rnbomaticSetLogger random8SetLogger
#include "../lib/Random8/Random8.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct Random8 : Module {
	enum ParamIds {
		ATTEN1_PARAM,
		ATTEN5_PARAM,
		OFFSET1_PARAM,
		OFFSET5_PARAM,
		ATTEN2_PARAM,
		ATTEN6_PARAM,
		OFFSET2_PARAM,
		OFFSET6_PARAM,
		ATTEN3_PARAM,
		ATTEN7_PARAM,
		OFFSET3_PARAM,
		OFFSET7_PARAM,
		ATTEN4_PARAM,
		ATTEN8_PARAM,
		OFFSET4_PARAM,
		OFFSET8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		TRIGGER_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		OUT5_OUTPUT,
		OUT6_OUTPUT,
		OUT7_OUTPUT,
		OUT8_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::Random8_rnbomatic<> *random8Engine = nullptr;
	bool rnboInitialized = false;
	double lastParams[16] = {1,1,0,0, 1,1,0,0, 1,1,0,0, 1,1,0,0};

	Random8() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(ATTEN1_PARAM, 0.f, 1.f, 1.f, "Ch 1 Attenuate");
		configParam(ATTEN5_PARAM, 0.f, 1.f, 1.f, "Ch 5 Attenuate");
		configParam(OFFSET1_PARAM, -1.f, 1.f, 0.f, "Ch 1 Offset");
		configParam(OFFSET5_PARAM, -1.f, 1.f, 0.f, "Ch 5 Offset");
		configParam(ATTEN2_PARAM, 0.f, 1.f, 1.f, "Ch 2 Attenuate");
		configParam(ATTEN6_PARAM, 0.f, 1.f, 1.f, "Ch 6 Attenuate");
		configParam(OFFSET2_PARAM, -1.f, 1.f, 0.f, "Ch 2 Offset");
		configParam(OFFSET6_PARAM, -1.f, 1.f, 0.f, "Ch 6 Offset");
		configParam(ATTEN3_PARAM, 0.f, 1.f, 1.f, "Ch 3 Attenuate");
		configParam(ATTEN7_PARAM, 0.f, 1.f, 1.f, "Ch 7 Attenuate");
		configParam(OFFSET3_PARAM, -1.f, 1.f, 0.f, "Ch 3 Offset");
		configParam(OFFSET7_PARAM, -1.f, 1.f, 0.f, "Ch 7 Offset");
		configParam(ATTEN4_PARAM, 0.f, 1.f, 1.f, "Ch 4 Attenuate");
		configParam(ATTEN8_PARAM, 0.f, 1.f, 1.f, "Ch 8 Attenuate");
		configParam(OFFSET4_PARAM, -1.f, 1.f, 0.f, "Ch 4 Offset");
		configParam(OFFSET8_PARAM, -1.f, 1.f, 0.f, "Ch 8 Offset");
		configInput(TRIGGER_INPUT, "Trigger/Clock");
		for (int i = 0; i < 8; i++) {
			configOutput(OUT1_OUTPUT + i, "Out " + std::to_string(i + 1));
		}
		random8Engine = new RNBO::Random8_rnbomatic<>();
	}

	~Random8() {
		if (random8Engine) {
			delete random8Engine;
			random8Engine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && random8Engine) {
			random8Engine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!random8Engine) return;

		// Initialize RNBO engine on first process
		if (!rnboInitialized) {
			random8Engine->initialize();
			random8Engine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		// Update RNBO parameters if changed (indices match description.json order)
		// 0:1atten, 1:5atten, 2:1offset, 3:5offset, 4:2atten, 5:6atten, 6:2offset, 7:6offset
		// 8:3atten, 9:7atten, 10:3offset, 11:7offset, 12:4atten, 13:8atten, 14:4offset, 15:8offset
		for (int i = 0; i < NUM_PARAMS; i++) {
			double val = (double)params[i].getValue();
			if (val != lastParams[i]) {
				random8Engine->setParameterValue(i, val, 0);
				lastParams[i] = val;
			}
		}

		// Get trigger input
		double in0 = inputs[TRIGGER_INPUT].isConnected() ? (double)inputs[TRIGGER_INPUT].getVoltage() / 5.0 : 0.0;
		double out0 = 0.0, out1 = 0.0, out2 = 0.0, out3 = 0.0;
		double out4 = 0.0, out5 = 0.0, out6 = 0.0, out7 = 0.0;
		double* rnboInputs[1] = {&in0};
		double* rnboOutputs[8] = {&out0, &out1, &out2, &out3, &out4, &out5, &out6, &out7};

		// Process one sample per Rack frame.
		random8Engine->process(rnboInputs, 1, rnboOutputs, 8, 1);

		// RNBO outputs normalized around +/-1. Scale to Rack +/-5V.
		outputs[OUT1_OUTPUT].setVoltage(clamp((float)out0 * 5.f, -10.f, 10.f));
		outputs[OUT2_OUTPUT].setVoltage(clamp((float)out1 * 5.f, -10.f, 10.f));
		outputs[OUT3_OUTPUT].setVoltage(clamp((float)out2 * 5.f, -10.f, 10.f));
		outputs[OUT4_OUTPUT].setVoltage(clamp((float)out3 * 5.f, -10.f, 10.f));
		outputs[OUT5_OUTPUT].setVoltage(clamp((float)out4 * 5.f, -10.f, 10.f));
		outputs[OUT6_OUTPUT].setVoltage(clamp((float)out5 * 5.f, -10.f, 10.f));
		outputs[OUT7_OUTPUT].setVoltage(clamp((float)out6 * 5.f, -10.f, 10.f));
		outputs[OUT8_OUTPUT].setVoltage(clamp((float)out7 * 5.f, -10.f, 10.f));
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

struct Random8Widget : ModuleWidget {
	Random8Widget(Random8 *module);
	~Random8Widget(){
	}
	void appendContextMenu(Menu *menu) override;
};

Random8Widget::Random8Widget(Random8 *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 10, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/Random8.svg"),
		asset::plugin(pluginInstance, "res/Random8.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 365)));

	// Trigger input
	addInput(createInputCentered<PJ301MPort>(Vec(box.size.x / 2, 310.f), module, Random8::TRIGGER_INPUT));

	// Improved layout: more spacing between columns
	float leftX = 25.f;
	float leftAttenX = 45.f;
	float leftOffsetX = 65.f;
	float rightAttenX = 85.f;
	float rightOffsetX = 105.f;
	float rightX = 125.f;

	const int leftAttenIdx[4]  = {Random8::ATTEN1_PARAM, Random8::ATTEN2_PARAM, Random8::ATTEN3_PARAM, Random8::ATTEN4_PARAM};
	const int leftOffsetIdx[4] = {Random8::OFFSET1_PARAM, Random8::OFFSET2_PARAM, Random8::OFFSET3_PARAM, Random8::OFFSET4_PARAM};
	const int rightAttenIdx[4]  = {Random8::ATTEN5_PARAM, Random8::ATTEN6_PARAM, Random8::ATTEN7_PARAM, Random8::ATTEN8_PARAM};
	const int rightOffsetIdx[4] = {Random8::OFFSET5_PARAM, Random8::OFFSET6_PARAM, Random8::OFFSET7_PARAM, Random8::OFFSET8_PARAM};

	for (int i = 0; i < 4; i++) {
		float y = 68.f + i * 55.f;

		// Channels 1-4 (left side): atten + offset knobs, output port
		addParam(createParamCentered<Trimpot>(Vec(leftAttenX, y), module, leftAttenIdx[i]));
		addParam(createParamCentered<Trimpot>(Vec(leftOffsetX, y), module, leftOffsetIdx[i]));
		addOutput(createOutputCentered<PJ301MPort>(Vec(leftX, y), module, Random8::OUT1_OUTPUT + i));

		// Channels 5-8 (right side): atten + offset knobs, output port
		addParam(createParamCentered<Trimpot>(Vec(rightAttenX, y), module, rightAttenIdx[i]));
		addParam(createParamCentered<Trimpot>(Vec(rightOffsetX, y), module, rightOffsetIdx[i]));
		addOutput(createOutputCentered<PJ301MPort>(Vec(rightX, y), module, Random8::OUT5_OUTPUT + i));
	}
}

void Random8Widget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelRandom8 = createModel<Random8, Random8Widget>("Random8");
