
#include "LocalMasterTrigger.h"
#include "EventEngineManager.h"
#include "EngineID.h"

using STI::TimingEngine::LocalMasterTrigger;
using STI::TimingEngine::EventEngineManagerVector_ptr;
using STI::TimingEngine::EngineInstance;
using STI::TimingEngine::EngineID;
using STI::TimingEngine::EventEngineState;


LocalMasterTrigger::LocalMasterTrigger(const EventEngineManagerVector_ptr& managers, const EngineInstance& engineInstance)
: managers_l(managers), engineInstance_l(engineInstance)
{
}

bool LocalMasterTrigger::waitForAll(EventEngineState state)
{
	//Waits for all engines to reach the same state. Aborts if none of the engines are in that state.
	//For example, if one the local engine is WaitingForTrigger, this loop will wait for all the
	//other engines to reach WaitingForTrigger as long as at least one (the local, for example)
	//is still in this state.
	bool keepWaiting = true;
	unsigned numberInState = 0;

	 while(keepWaiting) {
		numberInState = 0;
		for(unsigned i = 0; i < managers_l->size(); i++) {
			if(managers_l->at(i)->inState(engineInstance_l.id, state)) {
				numberInState++;
			}
		}
		keepWaiting = (numberInState > 0) && (numberInState < managers_l->size());

		if(keepWaiting) {
			//timed sleep?
		}
	 }
	 return (numberInState == managers_l->size());
}


void LocalMasterTrigger::triggerAll()
{
	for(unsigned i = 0; i < managers_l->size(); i++) {
		managers_l->at(i)->trigger(engineInstance_l);
	}
}


void LocalMasterTrigger::stopAll()
{
	for(unsigned i = 0; i < managers_l->size(); i++) {
		managers_l->at(i)->stop(engineInstance_l.id);
	}
}

