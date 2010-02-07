/*! \file STI_Server.h
 *  \author Jason Michael Hogan
 *  \brief Include-file for the class STI_Server
 *  \section license License
 *
 *  Copyright (C) 2008 Jason Hogan <hogan@stanford.edu>\n
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


// Interface for server communication with STI_Device objects using CORBA

#ifndef STI_SERVER_H
#define STI_SERVER_H

#include "device.h"
#include "client.h"

#include <Attribute.h>
#include "RemoteDevice.h"
#include <CompositeEvent.h>
#include <ServerEventPusher_i.h>

#include <string>
#include <sstream>
#include <map>
#include <boost/ptr_container/ptr_map.hpp>

class Attribute;
class ORBManager;
class ServerConfigure_i;
class ServerTimingSeqControl_i;
class ExpSequence_i;
class ModeHandler_i;
class Parser_i;
class ServerConfigure_i;
class RegisteredDevices_i;
class StreamingDataTransfer_i;
class ServerCommandLine_i;
class RemoteDevice;
class ClientBootstrap_i;

class DeviceEventHandler_i;

typedef std::map<std::string, Attribute> AttributeMap;
typedef boost::ptr_map<std::string, RemoteDevice> RemoteDeviceMap;
//typedef std::map<std::string, std::vector<STI::Types::TDeviceEvent_var> > EventMap;
typedef std::map<std::string, std::vector<CompositeEvent> > EventMap;

using STI::Pusher::EventsEmpty;
using STI::Pusher::PreparingEvents;
using STI::Pusher::EventsReady;
using STI::Pusher::RequestingPlay;
using STI::Pusher::PlayingEvents;
using STI::Pusher::Paused;
using STI::Pusher::Waiting;

class STI_Server
{
public:

	STI_Server(ORBManager* orb_manager);
	STI_Server(std::string serverName, ORBManager* orb_manager);
	virtual ~STI_Server();

	virtual bool serverMain();
	virtual void defineAttributes();

	bool sendMessageToClient(STI::Pusher::MessageType type, std::string message);

	template<class T> void sendEvent(const T& event) {
		localServerEventPusher->pushEvent(event);
	}

	//enum ServerStatus { EventsEmpty, PreparingEvents, EventsReady, RequestingPlay, PlayingEvents, Paused, Waiting };

	STI::Pusher::ServerState serverStatus;

	void updateState();
	bool changeStatus(STI::Pusher::ServerState newStatus);

	bool setupEventsOnDevices();
	void resetDeviceEvents();
	void transferEvents();
	void loadEvents();
	bool requestPlay();
	void playEvents();
	void stopAllDevices();
	void pauseAllDevices();
	void playAllDevices();
	void stopServer();
	void pauseServer(bool pausedByDevice);
	void unpauseServer(bool unpausedByDevice);
	bool eventsParsed();
	bool checkChannelAvailability(std::stringstream& message);
	bool calculatePartnerDependencies(std::stringstream& message);
	void divideEventList();
	bool hasEvents(std::string deviceID);
	void waitForEventsToFinish();

	void playEventsOnDevice(std::string deviceID);
	void pauseAllDevicesExcept(std::string deviceID);	//pauses all devices except device deviceID
	std::string unpausedDeviceID;
	bool isPausedByDevice() {return (PausedByDevice && serverPaused);}
	// Client control handling (ModeHandler)

	// STI_Device communication
	bool activateDevice(std::string deviceID);
	bool registerDevice(STI::Types::TDevice& device, STI::Server_Device::DeviceBootstrap_ptr bootstrap);
	bool setChannels(std::string deviceID, const STI::Types::TDeviceChannelSeq& channels);
	bool removeDevice(std::string deviceID);
	bool getDeviceStatus(std::string deviceID);
	std::string generateDeviceID(const STI::Types::TDevice& device) const;
	void refreshDevices();
	void refreshPartnersDevices();

	// Server attributes
//	bool setAttribute(std::string key, std::string value);
	void setSeverName(std::string serverName);
	
	ORBManager* getORBManager() const;
	const AttributeMap& getAttributes() const;
	std::string getServerName() const;
	std::string getErrorMsg()const;
	std::string getTransferErrLog(std::string deviceID) const;

	std::string executeArgs(const char* deviceID, const char* args);
	const std::vector<std::string>& getRequiredPartners(std::string deviceID);
	const std::vector<std::string>& getRegisteredPartners(std::string deviceID);

	RemoteDeviceMap registeredDevices;	// DeviceID => RemoteDevice
	std::vector<std::string> devicesWithEvents;	// DeviceID's of devices with events

	STI::Client_Server::ModeHandler_ptr getModeHandler();
	STI::Client_Server::Parser_ptr getParser();
    STI::Client_Server::ExpSequence_ptr getExpSequence();
    STI::Client_Server::ServerTimingSeqControl_ptr getServerTimingSeqControl();
    STI::Client_Server::RegisteredDevices_ptr getRegisteredDevices();
    STI::Client_Server::ServerCommandLine_ptr getServerCommandLine();
	STI::Pusher::DeviceEventHandler_ptr getDeviceEventHandler();

	bool addNewClient(STI::Pusher::ServerEventHandler_ptr eventHandler);

protected:

	// Servants
	ServerTimingSeqControl_i* controlServant;
	ExpSequence_i* expSequenceServant;
	ModeHandler_i* modeHandlerServant;
	Parser_i* parserServant;
	ServerConfigure_i* serverConfigureServant;
	RegisteredDevices_i* deviceConfigureServant;
	StreamingDataTransfer_i* streamingDataTransferServant;
	ServerCommandLine_i* serverCommandLineServant;
	ClientBootstrap_i* clientBootstrapServant;

	ServerEventPusher_i* localServerEventPusher;
	DeviceEventHandler_i* deviceEventHandlerServant;

	// Containers
	EventMap events;
	AttributeMap attributes;			//server attributes
	
	bool isUnique(std::string deviceID);

//	std::vector<STI_Server::CompositeEvent> compositeEvents;

private:

	bool isUniqueString(std::string value, std::vector<std::string>& list);

	std::vector<std::string> emptyPartnerList;

	void push_backEvent(std::string deviceID, double time, unsigned short channel, STI::Types::TValMixed value, const STI::Types::TEvent& originalTEvent);

	void init();
	
	std::string removeForbiddenChars(std::string input) const;

	static void serverMainWrapper(void* object);
	static void transferEventsWrapper(void* object);

	ORBManager* orbManager;

	static bool eventTransferLock;
	std::string currentDevice;

	std::stringstream errStream;
	std::string serverName_;

	omni_mutex* refreshMutex;
	
	omni_mutex* serverStateMutex;

	omni_mutex* serverPauseMutex;
	omni_condition* serverPauseCondition;


	bool serverStopped;
	bool serverPaused;
	bool PausedByDevice;
};

#endif
