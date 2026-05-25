#include "plugin.hpp"
#include <cmath>

// Include the RNBO generated code
#define RNBO_LIB_PREFIX rnbo/common
#define RNBO_NO_PATCHERFACTORY
#define rnbomatic ClockPort_rnbomatic
#define rnbomaticFactoryFunction clockPortFactoryFunction
#define rnbomaticSetLogger clockPortSetLogger
#include "../lib/ClockPort/ClockPort.cpp"
#undef rnbomaticSetLogger
#undef rnbomaticFactoryFunction
#undef rnbomatic
#undef RNBO_NO_PATCHERFACTORY
#undef RNBO_LIB_PREFIX

struct ClockPort : Module {
	enum ParamIds {
		STARTSTOP_PARAM,
		DIV1_PARAM,
		DIV2_PARAM,
		TEMPO_PARAM,
		DIV3_PARAM,
		DIV4_PARAM,
		DIV5_PARAM,
		DIV6_PARAM,
		DIV7_PARAM,
		DIV8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		RESET_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		OUT5_OUTPUT,
		OUT6_OUTPUT,
		OUT7_OUTPUT,
		OUT8_OUTPUT,
		OUT9_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	RNBO::ClockPort_rnbomatic<> *clockPortEngine = nullptr;
	bool rnboInitialized = false;
	double lastStartStop = 0.0;
	double lastDiv1 = 15.0;
	double lastDiv2 = 15.0;
	double lastTempo = 120.0;
	double lastDiv3 = 15.0;
	double lastDiv4 = 15.0;
	double lastDiv5 = 15.0;
	double lastDiv6 = 15.0;
	double lastDiv7 = 15.0;
	double lastDiv8 = 15.0;

	ClockPort() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(STARTSTOP_PARAM, 0.f, 1.f, 0.f, "Start/Stop");
		configParam(DIV1_PARAM, 0.f, 15.f, 15.f, "Div 1");
		configParam(DIV2_PARAM, 0.f, 15.f, 15.f, "Div 2");
		configParam(TEMPO_PARAM, 1.f, 999.f, 120.f, "Tempo");
		configParam(DIV3_PARAM, 0.f, 15.f, 15.f, "Div 3");
		configParam(DIV4_PARAM, 0.f, 15.f, 15.f, "Div 4");
		configParam(DIV5_PARAM, 0.f, 15.f, 15.f, "Div 5");
		configParam(DIV6_PARAM, 0.f, 15.f, 15.f, "Div 6");
		configParam(DIV7_PARAM, 0.f, 15.f, 15.f, "Div 7");
		configParam(DIV8_PARAM, 0.f, 15.f, 15.f, "Div 8");
		configOutput(RESET_OUTPUT, "Reset");
		for (int i = 1; i < 9; i++) {
			configOutput(OUT2_OUTPUT + (i - 1), "Out " + std::to_string(i + 1));
		}
		clockPortEngine = new RNBO::ClockPort_rnbomatic<>();
	}

	~ClockPort() {
		if (clockPortEngine) {
			delete clockPortEngine;
			clockPortEngine = nullptr;
		}
	}

	void onSampleRateChange() override {
		if (rnboInitialized && clockPortEngine) {
			clockPortEngine->prepareToProcess(APP->engine->getSampleRate(), 64, true);
		}
	}

	void process(const ProcessArgs &args) override {
		if (!clockPortEngine) return;

		if (!rnboInitialized) {
			clockPortEngine->initialize();
			clockPortEngine->prepareToProcess(args.sampleRate, 64, true);
			rnboInitialized = true;
		}

		double startStop = (double)params[STARTSTOP_PARAM].getValue();
		double div1 = (double)params[DIV1_PARAM].getValue();
		double div2 = (double)params[DIV2_PARAM].getValue();
		double tempo = (double)params[TEMPO_PARAM].getValue();
		double div3 = (double)params[DIV3_PARAM].getValue();
		double div4 = (double)params[DIV4_PARAM].getValue();
		double div5 = (double)params[DIV5_PARAM].getValue();
		double div6 = (double)params[DIV6_PARAM].getValue();
		double div7 = (double)params[DIV7_PARAM].getValue();
		double div8 = (double)params[DIV8_PARAM].getValue();

		if (startStop != lastStartStop) { clockPortEngine->setParameterValue(0, startStop, 0); lastStartStop = startStop; }
		if (div1 != lastDiv1) { clockPortEngine->setParameterValue(1, div1, 0); lastDiv1 = div1; }
		if (div2 != lastDiv2) { clockPortEngine->setParameterValue(2, div2, 0); lastDiv2 = div2; }
		if (tempo != lastTempo) { clockPortEngine->setParameterValue(3, tempo, 0); lastTempo = tempo; }
		if (div3 != lastDiv3) { clockPortEngine->setParameterValue(4, div3, 0); lastDiv3 = div3; }
		if (div4 != lastDiv4) { clockPortEngine->setParameterValue(5, div4, 0); lastDiv4 = div4; }
		if (div5 != lastDiv5) { clockPortEngine->setParameterValue(6, div5, 0); lastDiv5 = div5; }
		if (div6 != lastDiv6) { clockPortEngine->setParameterValue(7, div6, 0); lastDiv6 = div6; }
		if (div7 != lastDiv7) { clockPortEngine->setParameterValue(8, div7, 0); lastDiv7 = div7; }
		if (div8 != lastDiv8) { clockPortEngine->setParameterValue(9, div8, 0); lastDiv8 = div8; }

		double outValues[9] = {};
		double *rnboInputs[1] = {nullptr};
		double *rnboOutputs[9] = {&outValues[0], &outValues[1], &outValues[2], &outValues[3], &outValues[4], &outValues[5], &outValues[6], &outValues[7], &outValues[8]};
		clockPortEngine->process(rnboInputs, 0, rnboOutputs, 9, 1);

		for (int i = 0; i < 9; i++) {
			outputs[RESET_OUTPUT + i].setVoltage(clamp((float)outValues[i] * 5.f, -10.f, 10.f));
			outputs[RESET_OUTPUT + i].setChannels(1);
		}
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

struct ClockPortWidget : ModuleWidget {
	ClockPortWidget(ClockPort *module);
	~ClockPortWidget(){
	}
	void appendContextMenu(Menu *menu) override;
};

ClockPortWidget::ClockPortWidget(ClockPort *module) {
	setModule(module);
	box.size = Vec(RACK_GRID_WIDTH * 12, RACK_GRID_HEIGHT);

	setPanel(createPanel(
		asset::plugin(pluginInstance, "res/ClockPort.svg"),
		asset::plugin(pluginInstance, "res/ClockPort.svg")
	));

	addChild(createWidget<Screw_J>(Vec(16, 2)));
	addChild(createWidget<Screw_J>(Vec(16, 365)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 2)));
	addChild(createWidget<Screw_W>(Vec(box.size.x - 29, 365)));

	addParam(createParamCentered<CKSS>(Vec(60.f, 70.f), module, ClockPort::STARTSTOP_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 122.f), module, ClockPort::DIV1_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(60.f, 122.f), module, ClockPort::DIV2_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(90.f, 122.f), module, ClockPort::TEMPO_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 182.f), module, ClockPort::DIV3_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(60.f, 182.f), module, ClockPort::DIV4_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(90.f, 182.f), module, ClockPort::DIV5_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(30.f, 242.f), module, ClockPort::DIV6_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(60.f, 242.f), module, ClockPort::DIV7_PARAM));
	addParam(createParamCentered<RoundBlackKnob>(Vec(90.f, 242.f), module, ClockPort::DIV8_PARAM));

	addOutput(createOutputCentered<PJ301MPort>(Vec(20.f, 324.f), module, ClockPort::RESET_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(40.f, 324.f), module, ClockPort::OUT2_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(60.f, 324.f), module, ClockPort::OUT3_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(80.f, 324.f), module, ClockPort::OUT4_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(100.f, 324.f), module, ClockPort::OUT5_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(20.f, 352.f), module, ClockPort::OUT6_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(40.f, 352.f), module, ClockPort::OUT7_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(60.f, 352.f), module, ClockPort::OUT8_OUTPUT));
	addOutput(createOutputCentered<PJ301MPort>(Vec(80.f, 352.f), module, ClockPort::OUT9_OUTPUT));
}

void ClockPortWidget::appendContextMenu(Menu *menu) {
	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);
}

Model *modelClockPort = createModel<ClockPort, ClockPortWidget>("ClockPort");
