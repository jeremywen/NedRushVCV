#include "plugin.hpp"

#if defined(METAMODULE_BUILTIN)
extern Plugin *pluginInstance;
#else
Plugin *pluginInstance;
#endif

#if defined(METAMODULE_BUILTIN)
void init_JWModules(rack::Plugin *p) {
#else 
void init(rack::Plugin *p) {
#endif

	pluginInstance = p;
	p->addModel(modelHelpDelay);
	p->addModel(modelNedKick);
	p->addModel(modelRandom8);
	p->addModel(modelNedLFO1);
	p->addModel(modelNedRepeat);
	p->addModel(modelRandomSeq);
	p->addModel(modelCosmoDelay);
	p->addModel(modelGraiNed);
	p->addModel(modelClockPort);
	p->addModel(modelLuckyTriggers);
	p->addModel(modelLuckyGate);
	p->addModel(modelWuggle);
}
