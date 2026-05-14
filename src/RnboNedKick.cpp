#include "JWModules.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic NedKick_rnbomatic
#define rnbomaticFactoryFunction nedKickFactoryFunction
#define rnbomaticSetLogger nedKickSetLogger
#include "../lib/NedKick/NedKick.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct RnboNedKick : Module {
	enum ParamIds {
		FREQUENCY_PARAM,
		SWEEPAMT_PARAM,
		FILTER_PARAM,
		DRIVE_PARAM,
		SWEEPDECAY_PARAM,
		DECAY_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		TRIGGER_INPUT,
		FREQUENCY_CV_INPUT,
		SWEEPAMT_CV_INPUT,
		FILTER_CV_INPUT,
		DRIVE_CV_INPUT,
		SWEEPDECAY_CV_INPUT,
		DECAY_CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		AUDIO_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::NedKick_rnbomatic<> *nedKickEngine = nullptr;
	bool rnboInitialized = false;
	double lastFrequency = 50.0;
	double lastSweepamt = 50.0;
	double lastFilter = 100.0;
	double lastDrive = 1.0;
	double lastSweepdecay = 50.0;
	double lastDecay = 50.0;

	RnboNedKick() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(FREQUENCY_PARAM, 30.f, 200.f, 50.f, "Frequency");
		configParam(SWEEPAMT_PARAM, 10.f, 500.f, 50.f, "Sweep Amount");
		configParam(FILTER_PARAM, 30.f, 10000.f, 100.f, "Filter");
		configParam(DRIVE_PARAM, 1.f, 11.f, 1.f, "Drive");
		configParam(SWEEPDECAY_PARAM, 10.f, 500.f, 50.f, "Sweep Decay");
		configParam(DECAY_PARAM, 10.f, 1000.f, 50.f, "Decay");
		configInput(TRIGGER_INPUT, "Trigger");
		configInput(FREQUENCY_CV_INPUT, "Frequency CV");
		configInput(SWEEPAMT_CV_INPUT, "Sweep Amount CV");
		configInput(FILTER_CV_INPUT, "Filter CV");
		configInput(DRIVE_CV_INPUT, "Drive CV");
		configInput(SWEEPDECAY_CV_INPUT, "Sweep Decay CV");
		configInput(DECAY_CV_INPUT, "Decay CV");
		configOutput(AUDIO_OUTPUT, "Audio Out");
		nedKickEngine = new RNBO::NedKick_rnbomatic<>();
	}

	~RnboNedKick() {
		if (nedKickEngine) {
			delete nedKickEngine;
			nedKickEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && nedKickEngine) {
			nedKickEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!nedKickEngine) return;

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		// Initialize RNBO engine on first process
		if (!rnboInitialized) {
			nedKickEngine->initialize();
			nedKickEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		// Get parameters from Rack and update RNBO if changed
		double frequency = (double)params[FREQUENCY_PARAM].getValue();
		double sweepamt = (double)params[SWEEPAMT_PARAM].getValue();
		double filter = (double)params[FILTER_PARAM].getValue();
		double drive = (double)params[DRIVE_PARAM].getValue();
		double sweepdecay = (double)params[SWEEPDECAY_PARAM].getValue();
		double decay = (double)params[DECAY_PARAM].getValue();

		// Apply CV modulation
		if (inputs[FREQUENCY_CV_INPUT].isConnected()) {
			double cv = (double)inputs[FREQUENCY_CV_INPUT].getVoltage() / 10.0; // 0-10V to 0-1
			frequency = clampd(frequency + cv * 170.0, 30.0, 200.0);
		}
		if (inputs[SWEEPAMT_CV_INPUT].isConnected()) {
			double cv = (double)inputs[SWEEPAMT_CV_INPUT].getVoltage() / 10.0;
			sweepamt = clampd(sweepamt + cv * 490.0, 10.0, 500.0);
		}
		if (inputs[FILTER_CV_INPUT].isConnected()) {
			double cv = (double)inputs[FILTER_CV_INPUT].getVoltage() / 10.0;
			filter = clampd(filter + cv * 9970.0, 30.0, 10000.0);
		}
		if (inputs[DRIVE_CV_INPUT].isConnected()) {
			double cv = (double)inputs[DRIVE_CV_INPUT].getVoltage() / 10.0;
			drive = clampd(drive + cv * 10.0, 1.0, 11.0);
		}
		if (inputs[SWEEPDECAY_CV_INPUT].isConnected()) {
			double cv = (double)inputs[SWEEPDECAY_CV_INPUT].getVoltage() / 10.0;
			sweepdecay = clampd(sweepdecay + cv * 490.0, 10.0, 500.0);
		}
		if (inputs[DECAY_CV_INPUT].isConnected()) {
			double cv = (double)inputs[DECAY_CV_INPUT].getVoltage() / 10.0;
			decay = clampd(decay + cv * 990.0, 10.0, 1000.0);
		}

		if (frequency != lastFrequency) {
			nedKickEngine->setParameterValue(0, frequency, 0);
			lastFrequency = frequency;
		}
		if (sweepamt != lastSweepamt) {
			nedKickEngine->setParameterValue(1, sweepamt, 0);
			lastSweepamt = sweepamt;
		}
		if (filter != lastFilter) {
			nedKickEngine->setParameterValue(2, filter, 0);
			lastFilter = filter;
		}
		if (drive != lastDrive) {
			nedKickEngine->setParameterValue(3, drive, 0);
			lastDrive = drive;
		}
		if (sweepdecay != lastSweepdecay) {
			nedKickEngine->setParameterValue(4, sweepdecay, 0);
			lastSweepdecay = sweepdecay;
		}
		if (decay != lastDecay) {
			nedKickEngine->setParameterValue(5, decay, 0);
			lastDecay = decay;
		}

		// Get trigger input and prepare output
		double in0 = inputs[TRIGGER_INPUT].isConnected() ? (double)inputs[TRIGGER_INPUT].getVoltage() / 5.0 : 0.0;
		double out0 = 0.0;
		double* rnboInputs[1] = {&in0};
		double* rnboOutputs[1] = {&out0};

		// Process one sample per Rack frame.
		nedKickEngine->process(rnboInputs, 1, rnboOutputs, 1, 1);

		// RNBO audio is generally normalized around +/-1. Rack audio is typically +/-5V.
		float scaledOut = clamp((float)out0 * 5.f, -10.f, 10.f);

		outputs[AUDIO_OUTPUT].setVoltage(scaledOut);
		outputs[AUDIO_OUTPUT].setChannels(1);
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

struct RnboNedKickWidget : ModuleWidget {
	RnboNedKickWidget(RnboNedKick *module);
	~RnboNedKickWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

RnboNedKickWidget::RnboNedKickWidget(RnboNedKick *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 8, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/RnboNedKick.svg"),
		asset::plugin(pluginInstance, "res/RnboNedKick.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 365)));

	// Trigger input
	addInput(createInputCentered<PJ301MPort>(Vec(25, 300.f), module, RnboNedKick::TRIGGER_INPUT));

	// Parameters and CV inputs
	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 60.f), module, RnboNedKick::FREQUENCY_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 60.f), module, RnboNedKick::FREQUENCY_CV_INPUT));

	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 100.f), module, RnboNedKick::SWEEPAMT_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 100.f), module, RnboNedKick::SWEEPAMT_CV_INPUT));

	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 140.f), module, RnboNedKick::FILTER_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 140.f), module, RnboNedKick::FILTER_CV_INPUT));

	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 180.f), module, RnboNedKick::DRIVE_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 180.f), module, RnboNedKick::DRIVE_CV_INPUT));

	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 220.f), module, RnboNedKick::SWEEPDECAY_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 220.f), module, RnboNedKick::SWEEPDECAY_CV_INPUT));

	addParam(createParamCentered<RoundBlackKnob>(Vec(35.f, 260.f), module, RnboNedKick::DECAY_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 260.f), module, RnboNedKick::DECAY_CV_INPUT));

	// Audio output
	addOutput(createOutputCentered<PJ301MPort>(Vec(box.size.x - 25, 300.f), module, RnboNedKick::AUDIO_OUTPUT));
}

void RnboNedKickWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelRnboNedKick = createModel<RnboNedKick, RnboNedKickWidget>("RnboNedKick");
