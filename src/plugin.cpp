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
	p->addModel(modelRnboHelpDelay);
	p->addModel(modelRnboNedKick);
	p->addModel(modelRnboRandom8);
	p->addModel(modelRnboNedLFO1);
	p->addModel(modelRnboNedRepeat);
}
