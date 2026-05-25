#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic LuckyGate_rnbomatic
#define rnbomaticFactoryFunction luckyGateFactoryFunction
#define rnbomaticSetLogger luckyGateSetLogger
#include "../lib/LuckyGate/LuckyGate.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct LuckyGate : Module {
	enum ParamIds {
		CHANCE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		TRIGGER_INPUT,
		CHANCE_CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::LuckyGate_rnbomatic<> *luckyGateEngine = nullptr;
	bool rnboInitialized = false;
	double lastChance = 0.5;

	LuckyGate() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CHANCE_PARAM, 0.f, 1.f, 0.5f, "Chance");
		configInput(TRIGGER_INPUT, "Trigger/Clock");
		configInput(CHANCE_CV_INPUT, "Chance CV");
		configOutput(OUT_OUTPUT, "Out");
		luckyGateEngine = new RNBO::LuckyGate_rnbomatic<>();
	}

	~LuckyGate() {
		if (luckyGateEngine) {
			delete luckyGateEngine;
			luckyGateEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && luckyGateEngine) {
			luckyGateEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!luckyGateEngine) return;

		if (!rnboInitialized) {
			luckyGateEngine->initialize();
			luckyGateEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		double chance = (double)params[CHANCE_PARAM].getValue();
		if (inputs[CHANCE_CV_INPUT].isConnected()) {
			double chanceCV = (double)inputs[CHANCE_CV_INPUT].getVoltage() / 10.0;
			chance = clampd(chance + chanceCV, 0.0, 1.0);
		}
		if (chance != lastChance) {
			luckyGateEngine->setParameterValue(0, chance, 0);
			lastChance = chance;
		}

		double inTrigger = inputs[TRIGGER_INPUT].isConnected() ? (double)inputs[TRIGGER_INPUT].getVoltage() / 5.0 : 0.0;
		double outValue = 0.0;
		double *rnboInputs[1] = {&inTrigger};
		double *rnboOutputs[1] = {&outValue};

		luckyGateEngine->process(rnboInputs, 1, rnboOutputs, 1, 1);

		outputs[OUT_OUTPUT].setVoltage(clamp((float)outValue * 5.f, -10.f, 10.f));
		outputs[OUT_OUTPUT].setChannels(1);
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

struct LuckyGateWidget : ModuleWidget {
	LuckyGateWidget(LuckyGate *module);
	~LuckyGateWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

LuckyGateWidget::LuckyGateWidget(LuckyGate *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 6, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/LuckyGate.svg"),
		asset::plugin(pluginInstance, "res/LuckyGate.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 365)));

	addParam(createParamCentered<RoundBlackKnob>(Vec(20.f, 92.f), module, LuckyGate::CHANCE_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(40.f, 92.f), module, LuckyGate::CHANCE_CV_INPUT));
	addInput(createInputCentered<PJ301MPort>(Vec(30.f, 238.f), module, LuckyGate::TRIGGER_INPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(30.f, 308.f), module, LuckyGate::OUT_OUTPUT));
}

void LuckyGateWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelLuckyGate = createModel<LuckyGate, LuckyGateWidget>("LuckyGate");
