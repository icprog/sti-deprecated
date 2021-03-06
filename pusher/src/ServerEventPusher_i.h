/*! \file ServerEventPusher_i.h
 *  \author Jason Michael Hogan
 *  \brief Include-file for the class ServerEventPusher_i
 *  \section license License
 *
 *  Copyright (C) 2010 Jason Hogan <hogan@stanford.edu>\n
 *  This file is part of the Stanford Timing Interface (STI).
 *
 *  The STI is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The STI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the STI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SERVEREVENTPUSHER_I_H
#define SERVEREVENTPUSHER_I_H

#include "pusher.h"
#include "ClientUpdater.h"

#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

typedef boost::ptr_vector<ClientUpdater> ClientUpdaterVector;

#include <ORBManager.h>

class ServerEventPusher_i : public POA_STI::Pusher::ServerEventPusher
{
public:

	ServerEventPusher_i(ORBManager* orb_manager);
	~ServerEventPusher_i();

	void addNewClient(STI::Pusher::ServerEventHandler_ptr handler, 
		const STI::Pusher::TStatusEvent& initialState);

	void pushPingEvent(const STI::Pusher::TPingEvent& event);
	void pushStatusEvent(const STI::Pusher::TStatusEvent& event);
	void pushSequenceEvent(const STI::Pusher::TSequenceEvent& event);
	void pushMessageEvent(const STI::Pusher::TMessageEvent& event);
	void pushParseEvent(const STI::Pusher::TParseEvent& event);
	void pushFileEvent(const STI::Pusher::TFileEvent& event);
	void pushControllerEvent(const STI::Pusher::TControllerEvent& event);
	void pushDeviceRefreshEvent(const STI::Pusher::TDeviceRefreshEvent& event);
	void pushDeviceDataEvent(const STI::Pusher::TDeviceDataEvent& event);

	void pushEvent(const STI::Pusher::TPingEvent& event) { pushPingEvent(event); }
	void pushEvent(const STI::Pusher::TStatusEvent& event) { pushStatusEvent(event); }
	void pushEvent(const STI::Pusher::TSequenceEvent& event) { pushSequenceEvent(event); }
	void pushEvent(const STI::Pusher::TMessageEvent& event) { pushMessageEvent(event); }
	void pushEvent(const STI::Pusher::TParseEvent& event) { pushParseEvent(event); }
	void pushEvent(const STI::Pusher::TFileEvent& event) { pushFileEvent(event); }
	void pushEvent(const STI::Pusher::TControllerEvent& event) { pushControllerEvent(event); }
	void pushEvent(const STI::Pusher::TDeviceRefreshEvent& event) { pushDeviceRefreshEvent(event); }
	void pushEvent(const STI::Pusher::TDeviceDataEvent& event) { pushDeviceDataEvent(event); }


private:
	void pushEvent(const ServerEvent& event);

	ClientUpdaterVector clientUpdaters;
	
	//std::vector<STI::Pusher::ServerEventPusher_var> pusherReferences;  //can have children pushers in principle...

	omni_mutex* updatersMutex;

	ORBManager* orbManager;




};

#endif