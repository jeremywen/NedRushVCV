#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic CosmoDelay_rnbomatic
#define rnbomaticFactoryFunction cosmoDelayFactoryFunction
#define rnbomaticSetLogger cosmoDelaySetLogger
#include "../lib/CosmoDelay/CosmoDelay.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct CosmoDelay : Module {
	enum ParamIds {
		FILTERTYPE_PARAM,
		FEEDBACK_PARAM,
		FEEDRES_PARAM,
		FEEDFREQ_PARAM,
		TIME_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		LEFT_INPUT,
		RIGHT_INPUT,
		FILTERTYPE_CV_INPUT,
		FEEDBACK_CV_INPUT,
		FEEDRES_CV_INPUT,
		FEEDFREQ_CV_INPUT,
		TIME_CV_INPUT,
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

	RNBO::CosmoDelay_rnbomatic<> *cosmoDelayEngine = nullptr;
	bool rnboInitialized = false;
	double lastFiltertype = 0.0;
	double lastFeedback = 0.5;
	double lastFeedres = 0.0;
	double lastFeedfreq = 10000.0;
	double lastTime = 500.0;

	CosmoDelay() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(FILTERTYPE_PARAM, 0.f, 3.f, 0.f, "Filter Type");
		configParam(FEEDBACK_PARAM, 0.f, 0.999f, 0.5f, "Feedback");
		configParam(FEEDRES_PARAM, 0.f, 0.9f, 0.f, "Feed Resonance");
		configParam(FEEDFREQ_PARAM, 10.f, 10000.f, 10000.f, "Feed Frequency");
		configParam(TIME_PARAM, 1.f, 1000.f, 500.f, "Time (ms)");
		configInput(LEFT_INPUT, "Left In");
		configInput(RIGHT_INPUT, "Right In");
		configInput(FILTERTYPE_CV_INPUT, "Filter Type CV");
		configInput(FEEDBACK_CV_INPUT, "Feedback CV");
		configInput(FEEDRES_CV_INPUT, "Feed Resonance CV");
		configInput(FEEDFREQ_CV_INPUT, "Feed Frequency CV");
		configInput(TIME_CV_INPUT, "Time CV");
		configOutput(LEFT_OUTPUT, "Left Out");
		configOutput(RIGHT_OUTPUT, "Right Out");
		cosmoDelayEngine = new RNBO::CosmoDelay_rnbomatic<>();
	}

	~CosmoDelay() {
		if (cosmoDelayEngine) {
			delete cosmoDelayEngine;
			cosmoDelayEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && cosmoDelayEngine) {
			cosmoDelayEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!cosmoDelayEngine) return;

		if (!rnboInitialized) {
			cosmoDelayEngine->initialize();
			cosmoDelayEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		double filtertype = std::round((double)params[FILTERTYPE_PARAM].getValue());
		double feedback = (double)params[FEEDBACK_PARAM].getValue();
		double feedres = (double)params[FEEDRES_PARAM].getValue();
		double feedfreq = (double)params[FEEDFREQ_PARAM].getValue();
		double time = (double)params[TIME_PARAM].getValue();

		if (inputs[FILTERTYPE_CV_INPUT].isConnected()) {
			double filtertypeCV = std::round((double)inputs[FILTERTYPE_CV_INPUT].getVoltage() / 2.5);
			filtertype = clampd(filtertype + filtertypeCV, 0.0, 3.0);
		}
		if (inputs[FEEDBACK_CV_INPUT].isConnected()) {
			double feedbackCV = (double)inputs[FEEDBACK_CV_INPUT].getVoltage() / 10.0;
			feedback = clampd(feedback + feedbackCV * 0.999, 0.0, 0.999);
		}
		if (inputs[FEEDRES_CV_INPUT].isConnected()) {
			double feedresCV = (double)inputs[FEEDRES_CV_INPUT].getVoltage() / 10.0;
			feedres = clampd(feedres + feedresCV * 0.9, 0.0, 0.9);
		}
		if (inputs[FEEDFREQ_CV_INPUT].isConnected()) {
			double feedfreqCV = (double)inputs[FEEDFREQ_CV_INPUT].getVoltage() / 10.0;
			feedfreq = clampd(feedfreq + feedfreqCV * 9990.0, 10.0, 10000.0);
		}
		if (inputs[TIME_CV_INPUT].isConnected()) {
			double timeCV = (double)inputs[TIME_CV_INPUT].getVoltage() / 10.0;
			time = clampd(time + timeCV * 999.0, 1.0, 1000.0);
		}

		if (filtertype != lastFiltertype) {
			cosmoDelayEngine->setParameterValue(0, filtertype, 0);
			lastFiltertype = filtertype;
		}
		if (feedback != lastFeedback) {
			cosmoDelayEngine->setParameterValue(1, feedback, 0);
			lastFeedback = feedback;
		}
		if (feedres != lastFeedres) {
			cosmoDelayEngine->setParameterValue(2, feedres, 0);
			lastFeedres = feedres;
		}
		if (feedfreq != lastFeedfreq) {
			cosmoDelayEngine->setParameterValue(3, feedfreq, 0);
			lastFeedfreq = feedfreq;
		}
		if (time != lastTime) {
			cosmoDelayEngine->setParameterValue(4, time, 0);
			lastTime = time;
		}

		double inLeft = inputs[LEFT_INPUT].isConnected() ? (double)inputs[LEFT_INPUT].getVoltage() / 5.0 : 0.0;
		double inRight = inputs[RIGHT_INPUT].isConnected() ? (double)inputs[RIGHT_INPUT].getVoltage() / 5.0 : 0.0;
		double outLeft = 0.0;
		double outRight = 0.0;
		double *rnboInputs[2] = {&inLeft, &inRight};
		double *rnboOutputs[2] = {&outLeft, &outRight};

		cosmoDelayEngine->process(rnboInputs, 2, rnboOutputs, 2, 1);

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

struct CosmoDelayWidget : ModuleWidget {
	CosmoDelayWidget(CosmoDelay *module);
	~CosmoDelayWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

CosmoDelayWidget::CosmoDelayWidget(CosmoDelay *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 8, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/CosmoDelay.svg"),
		asset::plugin(pluginInstance, "res/CosmoDelay.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 365)));

	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 67.f), module, CosmoDelay::FILTERTYPE_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 67.f), module, CosmoDelay::FILTERTYPE_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 107.f), module, CosmoDelay::FEEDBACK_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 107.f), module, CosmoDelay::FEEDBACK_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 147.f), module, CosmoDelay::FEEDRES_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 147.f), module, CosmoDelay::FEEDRES_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 187.f), module, CosmoDelay::FEEDFREQ_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 187.f), module, CosmoDelay::FEEDFREQ_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 227.f), module, CosmoDelay::TIME_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 227.f), module, CosmoDelay::TIME_CV_INPUT));

	addInput(createInputCentered<PJ301MPort>(Vec(25.f, 326.f), module, CosmoDelay::LEFT_INPUT));
	addInput(createInputCentered<PJ301MPort>(Vec(65.f, 326.f), module, CosmoDelay::RIGHT_INPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(25.f, 354.f), module, CosmoDelay::LEFT_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(65.f, 354.f), module, CosmoDelay::RIGHT_OUTPUT));
}

void CosmoDelayWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelCosmoDelay = createModel<CosmoDelay, CosmoDelayWidget>("CosmoDelay");
