#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic RandomSeq_rnbomatic
#define rnbomaticFactoryFunction randomSeqFactoryFunction
#define rnbomaticSetLogger randomSeqSetLogger
#include "../lib/RandomSeq/RandomSeq.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct RandomSeq : Module {
	enum ParamIds {
		LENGTH_PARAM,
		OFFSET_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		TRIG_RANDOM_INPUT,
		LENGTH_CV_INPUT,
		OFFSET_CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SEQ_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::RandomSeq_rnbomatic<> *randomSeqEngine = nullptr;
	bool rnboInitialized = false;
	double lastLength = 14.0;
	double lastOffset = 0.0;

	RandomSeq() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(LENGTH_PARAM, 0.f, 14.f, 14.f, "Length");
		configParam(OFFSET_PARAM, 0.f, 16.f, 0.f, "Offset");
		configInput(CLOCK_INPUT, "Clock");
		configInput(TRIG_RANDOM_INPUT, "Trigger Random");
		configInput(LENGTH_CV_INPUT, "Length CV");
		configInput(OFFSET_CV_INPUT, "Offset CV");
		configOutput(SEQ_OUTPUT, "Out");
		randomSeqEngine = new RNBO::RandomSeq_rnbomatic<>();
	}

	~RandomSeq() {
		if (randomSeqEngine) {
			delete randomSeqEngine;
			randomSeqEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && randomSeqEngine) {
			randomSeqEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!randomSeqEngine) return;

		if (!rnboInitialized) {
			randomSeqEngine->initialize();
			randomSeqEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		double length = (double)params[LENGTH_PARAM].getValue();
		double offset = (double)params[OFFSET_PARAM].getValue();

		if (inputs[LENGTH_CV_INPUT].isConnected()) {
			double lengthCV = (double)inputs[LENGTH_CV_INPUT].getVoltage() / 10.0;
			length = clampd(length + lengthCV * 14.0, 0.0, 14.0);
		}
		if (inputs[OFFSET_CV_INPUT].isConnected()) {
			double offsetCV = (double)inputs[OFFSET_CV_INPUT].getVoltage() / 10.0;
			offset = clampd(offset + offsetCV * 16.0, 0.0, 16.0);
		}

		if (length != lastLength) {
			randomSeqEngine->setParameterValue(0, length, 0);
			lastLength = length;
		}
		if (offset != lastOffset) {
			randomSeqEngine->setParameterValue(1, offset, 0);
			lastOffset = offset;
		}

		double inClock = inputs[CLOCK_INPUT].isConnected() ? (double)inputs[CLOCK_INPUT].getVoltage() / 5.0 : 0.0;
		double inTrigRandom = inputs[TRIG_RANDOM_INPUT].isConnected() ? (double)inputs[TRIG_RANDOM_INPUT].getVoltage() / 5.0 : 0.0;
		double outSeq = 0.0;
		double* rnboInputs[2] = {&inClock, &inTrigRandom};
		double* rnboOutputs[1] = {&outSeq};

		randomSeqEngine->process(rnboInputs, 2, rnboOutputs, 1, 1);

		float scaledOut = clamp((float)outSeq * 5.f, -10.f, 10.f);
		outputs[SEQ_OUTPUT].setVoltage(scaledOut);
		outputs[SEQ_OUTPUT].setChannels(1);
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

struct RandomSeqWidget : ModuleWidget {
	RandomSeqWidget(RandomSeq *module);
	~RandomSeqWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

RandomSeqWidget::RandomSeqWidget(RandomSeq *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 8, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/RandomSeq.svg"),
		asset::plugin(pluginInstance, "res/RandomSeq.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x-29, 365)));

	addParam(createParamCentered<RoundBlackKnob>(Vec(25.f, 100.f), module, RandomSeq::LENGTH_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(50.f, 100.f), module, RandomSeq::LENGTH_CV_INPUT));
	addParam(createParamCentered<RoundBlackKnob>(Vec(25.f, 170.f), module, RandomSeq::OFFSET_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(50.f, 170.f), module, RandomSeq::OFFSET_CV_INPUT));

	addInput(createInputCentered<PJ301MPort>(Vec(20.f, 290.f), module, RandomSeq::CLOCK_INPUT));
	addInput(createInputCentered<PJ301MPort>(Vec(60.f, 290.f), module, RandomSeq::TRIG_RANDOM_INPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(40.f, 330.f), module, RandomSeq::SEQ_OUTPUT));
}

void RandomSeqWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelRandomSeq = createModel<RandomSeq, RandomSeqWidget>("RandomSeq");
