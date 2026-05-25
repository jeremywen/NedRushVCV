#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic Wuggle_rnbomatic
#define rnbomaticFactoryFunction wuggleFactoryFunction
#define rnbomaticSetLogger wuggleSetLogger
#include "../lib/Wuggle/Wuggle.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct Wuggle : Module {
	enum ParamIds {
		WUGGLE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		TRIGGER_INPUT,
		WUGGLE_CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::Wuggle_rnbomatic<> *wuggleEngine = nullptr;
	bool rnboInitialized = false;
	double lastWuggle = 10.0;

	Wuggle() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(WUGGLE_PARAM, 0.01f, 50.f, 10.f, "Wuggle");
		configInput(TRIGGER_INPUT, "Trigger/Clock");
		configInput(WUGGLE_CV_INPUT, "Wuggle CV");
		configOutput(OUT_OUTPUT, "Out");
		wuggleEngine = new RNBO::Wuggle_rnbomatic<>();
	}

	~Wuggle() {
		if (wuggleEngine) {
			delete wuggleEngine;
			wuggleEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && wuggleEngine) {
			wuggleEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!wuggleEngine) return;

		if (!rnboInitialized) {
			wuggleEngine->initialize();
			wuggleEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		auto clampd = [](double x, double lo, double hi) {
			return (x < lo) ? lo : (x > hi ? hi : x);
		};

		double wuggle = (double)params[WUGGLE_PARAM].getValue();
		if (inputs[WUGGLE_CV_INPUT].isConnected()) {
			double wuggleCV = (double)inputs[WUGGLE_CV_INPUT].getVoltage() / 10.0;
			wuggle = clampd(wuggle + wuggleCV * 49.99, 0.01, 50.0);
		}
		if (wuggle != lastWuggle) {
			wuggleEngine->setParameterValue(0, wuggle, 0);
			lastWuggle = wuggle;
		}

		double inTrigger = inputs[TRIGGER_INPUT].isConnected() ? (double)inputs[TRIGGER_INPUT].getVoltage() / 5.0 : 0.0;
		double outValue = 0.0;
		double *rnboInputs[1] = {&inTrigger};
		double *rnboOutputs[1] = {&outValue};

		wuggleEngine->process(rnboInputs, 1, rnboOutputs, 1, 1);

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

struct WuggleWidget : ModuleWidget {
	WuggleWidget(Wuggle *module);
	~WuggleWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

WuggleWidget::WuggleWidget(Wuggle *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 6, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/Wuggle.svg"),
		asset::plugin(pluginInstance, "res/Wuggle.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 365)));

	addParam(createParamCentered<RoundBlackKnob>(Vec(20.f, 92.f), module, Wuggle::WUGGLE_PARAM));
	addInput(createInputCentered<PJ301MPort>(Vec(40.f, 92.f), module, Wuggle::WUGGLE_CV_INPUT));
	addInput(createInputCentered<PJ301MPort>(Vec(30.f, 238.f), module, Wuggle::TRIGGER_INPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(30.f, 308.f), module, Wuggle::OUT_OUTPUT));
}

void WuggleWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelWuggle = createModel<Wuggle, WuggleWidget>("Wuggle");
