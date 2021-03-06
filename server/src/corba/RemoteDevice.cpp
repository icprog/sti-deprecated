/*! \file RemoteDevice.cpp
 *  \author Jason Michael Hogan
 *  \brief Source-file for the class RemoteDevice
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


#include "RemoteDevice.h"
#include "STI_Server.h"
#include <ORBManager.h>

#include <string>
using std::string;

#include <iostream>
using namespace std;

RemoteDevice::RemoteDevice(STI_Server* STI_server, 
						   STI::Types::TDevice& device, 
						   STI::Server_Device::DeviceBootstrap_ptr bootstrap) : 
sti_server(STI_server)
{
	deviceBootstrapRef = bootstrap;
	active = false;

	doneTransfering = false;
	eventsReady = false;
	attributesFresh = false;
	partnersFresh = false;
	gettingPartners = false;

	tDevice.deviceName    = CORBA::string_dup(device.deviceName);
	tDevice.address       = CORBA::string_dup(device.address);
	tDevice.moduleNum     = device.moduleNum;
	tDevice.deviceID      = CORBA::string_dup(device.deviceID);
	tDevice.deviceContext = CORBA::string_dup(device.deviceContext);

	numberOfMeasurements = 0;

	eventDependencyMutex = new omni_mutex();
	eventDependencyCondition = new omni_condition(eventDependencyMutex);
}

RemoteDevice::~RemoteDevice()
{
	bool bootstrapIsNil = true;
	try {
//		bootstrapIsNil = deviceBootstrapRef->_NP_is_nil();
//		bootstrapIsNil = deviceBootstrapRef->_is_nil();
	} catch(...) {
		std::cerr << "BootstrapIsNil" << std::endl;
	}
	if( !bootstrapIsNil )
	{
		CORBA::release(deviceBootstrapRef);
	}
	active = false;
	stopWaitingForDependencies();

	//_release() references?
}

bool RemoteDevice::servantsActive()
{	
	bool servantsAlive = false;

	try {
		configureRef->ping();
		commandLineRef->ping();
		dataTransferRef->ping();
		deviceControlRef->ping();
		servantsAlive = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::servantsActive()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::servantsActive()");
	}
	catch(CORBA::Exception&)
	{
	}

	return servantsAlive;
}

bool RemoteDevice::isActive()
{
	active = servantsActive();	//refresh status

	return active;
}
STI::Types::TLabeledData* RemoteDevice::getLabedData(std::string label)
{
	STI::Types::TLabeledData_var labeledData;

	bool success = false;

	try {
		//get all the recent measurements that have not been retrieved yet.  This
		//is done by passing an index to the device which indicates which measurement
		//to start with (i.e., which ones not so send again).  In this case, we already
		//have measurements.size() number of measurements, so we want all new measurements
		//passed this index.
		labeledData = dataTransferRef->getData(label.c_str());
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::measurements");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::measurements");
	}
	catch(CORBA::Exception&)
	{
	}

	if(!success) {
		labeledData = new STI::Types::TLabeledData();
		labeledData->label = CORBA::string_dup("");
	}

	return labeledData._retn();
}

long RemoteDevice::pingDevice() const
{
	Int64 ping = -1;

	Clock pingTime;

	try {
		pingTime.reset();
		if( deviceControlRef->ping() )
			ping = pingTime.getCurrentTime();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::pingDevice()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::pingDevice()");
	}
	catch(CORBA::Exception&)
	{
	}

	return static_cast<long>( ping / 1000000 );		//in milliseconds
}

bool RemoteDevice::activate()
{
	active = false;
	
	bool bootstrapFound = false;

	try {
		bootstrapFound = deviceBootstrapRef->ping();
	}
	catch(CORBA::TRANSIENT& ex) {
		bootstrapFound = false;
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}
	catch(CORBA::SystemException& ex) {
		bootstrapFound = false;
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}

	if( !bootstrapFound )
		return false;
	
	try {
		acquireObjectReferences();
	}
	catch(CORBA::TRANSIENT& ex) {
		bootstrapFound = false;
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}
	catch(CORBA::SystemException& ex) {
		bootstrapFound = false;
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}

	if( isActive() )
	{
		setupChannels();

		setupRequiredPartners();
		setupEventPartners();
	}

	return active;
}

void RemoteDevice::deactivate()
{
	// _release() references???
	active = false;
}

void RemoteDevice::killDevice()
{
	try {
		configureRef->kill();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setupCommandLine()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setupCommandLine()");
	}	
	catch(CORBA::Exception&)
	{
	}

}

void RemoteDevice::acquireObjectReferences()
{
	CORBA::Object_var obj;

	bool configureFound     = false;
	bool dataTransferFound  = false;
	bool commandLineFound   = false;
	bool deviceControlFound = false;
	bool allServantsFound   = false;

	int orbTimeout = 10;	// try 10 times

	while( !allServantsFound && (--orbTimeout > 0) )
	{
		if( !configureFound )
		{
			configureRef = deviceBootstrapRef->getDeviceConfigure();
			if( !CORBA::is_nil(configureRef) )
				configureFound = true;
		}
		if( !dataTransferFound )
		{
			dataTransferRef = deviceBootstrapRef->getDataTransfer();
			if( !CORBA::is_nil(dataTransferRef) )
				dataTransferFound = true;
		}
		if( !commandLineFound )
		{
			commandLineRef = deviceBootstrapRef->getCommandLine();
			if( !CORBA::is_nil(commandLineRef) )
				commandLineFound = true;
		}
		if( !deviceControlFound )
		{
			deviceControlRef = deviceBootstrapRef->getDeviceTimingSeqControl();
			if( !CORBA::is_nil(deviceControlRef) )
				deviceControlFound = true;
		}
		
		allServantsFound = configureFound && dataTransferFound && 
						   commandLineFound && deviceControlFound;
	}
}

void RemoteDevice::setupEventPartners()
{
	bool success = false;

	eventPartners.clear();

	STI::Types::TStringSeq_var eventPartnerSeq;
	
	try {
		eventPartnerSeq = commandLineRef->eventPartnerDevices();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::refreshEventPartners()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::refreshEventPartners()");
	}
	catch(CORBA::Exception&)
	{
	}

	if(success)
	{
		for(unsigned i = 0; i < eventPartnerSeq->length(); i++)
		{
			eventPartners.push_back( string(eventPartnerSeq[i]) );
		}
	}
}

void RemoteDevice::setupRequiredPartners()
{
	requiredPartners.clear();
	
	bool success = false;
	STI::Types::TStringSeq_var partnerSeq;

	try {
		partnerSeq = commandLineRef->requiredPartnerDevices();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setupRequiredPartners()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setupRequiredPartners()");
	}
	catch(CORBA::Exception&)
	{
	}

	if(success)
	{
		for(unsigned i = 0; i < partnerSeq->length(); i++)
		{
			requiredPartners.push_back( string(partnerSeq[i]) );
//			cerr << requiredPartners.back() << endl;
		}
	}
}

const vector<string>& RemoteDevice::getRequiredPartners() const
{
	return requiredPartners;
}


std::vector<std::string>& RemoteDevice::getEventPartners()
{
	return eventPartners;
}
const vector<string>& RemoteDevice::getRegisteredPartners() const
{
	return registeredPartners;
}

vector<string>& RemoteDevice::getRegisteredPartners()
{
	registeredPartners.clear();

	bool success = false;
	STI::Types::TStringSeq_var partnerSeq;

	try {
		partnerSeq = commandLineRef->registeredPartnerDevices();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getRegisteredPartners()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getRegisteredPartners()");
	}
	catch(CORBA::Exception&)
	{
	}

	if(success)
	{
		for(unsigned i = 0; i < partnerSeq->length(); i++)
		{
			registeredPartners.push_back( string(partnerSeq[i]) );
		}
	}

	return registeredPartners;
}



void RemoteDevice::addPartnerDependency(std::string deviceID)
{
	bool newPartner = true;
	for(unsigned i = 0; i < partnerDependencies.size(); i++)
	{
		if(deviceID.compare(partnerDependencies.at(i)) == 0)
		{
			newPartner = false;
		}
	}
	if(newPartner)
	{
		eventDependencyMutex->lock();
		{
			partnerDependencies.push_back(deviceID);
		}
		eventDependencyMutex->unlock();
	}
}

void RemoteDevice::removePartnerDependency(std::string deviceID)
{
	for(unsigned i = 0; i < partnerDependencies.size(); i++)
	{
		if(deviceID.compare(partnerDependencies.at(i)) == 0)
		{
			//found it; now erase it.
			eventDependencyMutex->lock();
			{
				partnerDependencies.erase( partnerDependencies.begin() + i );
				eventDependencyCondition->signal();	//wake up waitForDependencies()
			}
			eventDependencyMutex->unlock();
			break;
		}
	}
}
void RemoteDevice::checkDependencies()
{
	eventDependencyMutex->lock();
	{
		eventDependencyCondition->signal();	//wake up waitForDependencies()
	}
	eventDependencyMutex->unlock();

}

void RemoteDevice::waitForDependencies()
{
	bool dependenciesFinished;

	eventDependencyMutex->lock();
	{
		dependenciesFinished = (partnerDependencies.size() == 0);
	}	
	eventDependencyMutex->unlock();
	
	//wake up
	//are there still dependencies?
	//if so wait
	//if not, stop waiting
	while( !dependenciesFinished )
	{
		eventDependencyMutex->lock();
		{
			eventDependencyCondition->wait();
		}
		eventDependencyMutex->unlock();

		eventDependencyMutex->lock();
		{
			dependenciesFinished = (partnerDependencies.size() == 0);
		}
		eventDependencyMutex->unlock();
	}
}

void RemoteDevice::stopWaitingForDependencies()
{	
	//stop waitForDependencies()
	partnerDependencies.clear();
	
	eventDependencyMutex->lock();
	{
		eventDependencyCondition->broadcast();
	}
	eventDependencyMutex->unlock();
}

bool RemoteDevice::registerPartner(std::string deviceID, STI::Server_Device::CommandLine_ptr partner)
{
	bool success = false;

	try {
		success = commandLineRef->registerPartnerDevice(partner);
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::registerPartner");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::registerPartner");
	}
	catch(CORBA::Exception&)
	{
	}

	return success;
}

bool RemoteDevice::unregisterPartner(std::string deviceID)
{
	bool success = false;

	try {
		success = commandLineRef->unregisterPartnerDevice(deviceID.c_str());
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::unregisterPartner");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::unregisterPartner");
	}
	catch(CORBA::Exception&)
	{
	}

	return success;
}


bool RemoteDevice::addChannel(const STI::Types::TDeviceChannel& tChannel)
{
	if(isUnique(tChannel))
	{
		channels.push_back(tChannel);
		return true;
	}
	else
	{
		cerr << "Error: Duplicate channel in device '" 
			<< getDevice().deviceName << "'." << endl;
		return false;
	}
}


bool RemoteDevice::setAttribute(std::string key, std::string value)
{
	bool success = false;

	try {
		success = configureRef->setAttribute(key.c_str(), value.c_str());
		attributesFresh = false;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setAttribute");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setAttribute");
	}
	catch(CORBA::Exception&)
	{
	}

	return success;
}



bool RemoteDevice::setDeviceChannelName(short channel, std::string name)
{
	bool success = false;

	try {
		success = configureRef->setDeviceChannelName(channel, name.c_str());
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setDeviceChannelName");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::setDeviceChannelName");
	}
	catch(CORBA::Exception&)
	{
	}

	if(success)
	{
		setupChannels();
	}

	return success;
}

bool RemoteDevice::isUnique(const STI::Types::TDeviceChannel& tChannel)
{
	bool unique = true;
	unsigned i;
	for(i = 0; i < channels.size(); i++)
	{
		if(channels[i].channel == tChannel.channel)	//same channel not allowed
		{
			unique = false;
		}
	}
	return unique;
}


STI::Server_Device::CommandLine_var RemoteDevice::getCommandLineRef() const
{
	return commandLineRef;
}

const STI::Types::TDevice& RemoteDevice::getDevice() const
{
	return tDevice;
}
//
//std::string RemoteDevice::getDataTransferErrMsg() const
//{
//	string error = "";
//
//	try {
//		error = string( dataTransferRef->errMsg() );
//	}
//	catch(CORBA::TRANSIENT& ex) {
//		cerr << printExceptionMessage(ex, "RemoteDevice::getDataTransferErrMsg()");
//	}
//	catch(CORBA::SystemException& ex) {
//		cerr << printExceptionMessage(ex, "RemoteDevice::getDataTransferErrMsg()");
//	}
//
//	return error;
//}



bool RemoteDevice::setupChannels()
{
	channels.clear();

	bool success = false;
	STI::Types::TDeviceChannelSeq_var tChannels;
	
	try {
		tChannels = configureRef->channels();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::activate()");
	}
	catch(CORBA::Exception&)
	{
	}

	if( !success )
		return false;

	for(unsigned i = 0; i < tChannels->length(); i++)
	{
		success &= addChannel( tChannels[i] );
	}

	return success;
}


void RemoteDevice::printChannels()
{
	for(unsigned i=0; i < channels.size(); i++)
	{
		cerr << "Channel " << i << ": " << channels[i].channel << endl;
	}
}
//const AttributeMap& RemoteDevice::getAttributes() const
//{
//	return attributes;
//}

void RemoteDevice::handleDeviceRefreshEvent(const STI::Pusher::TDeviceRefreshEvent& event)
{
	if(!gettingPartners && event.type == STI::Pusher::RefreshPartners)
		partnersFresh = false;

	if(event.type == STI::Pusher::RefreshAttributes)
		attributesFresh = false;
}


const vector<STI::Types::TPartner>& RemoteDevice::getPartners()
{
	if(partnersFresh)
		return partners;

	partners.clear();

	unsigned i;
	bool success = false;

	STI::Types::TPartnerSeq_var partnerSeq;

	gettingPartners = true;
	try {
		partnerSeq = configureRef->partners();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getPartners()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getPartners()");
	}
	catch(CORBA::Exception&)
	{
	}
	gettingPartners = false;

	if(success)
	{
		for(i = 0; i < partnerSeq->length(); i++)
		{

			partners.push_back( partnerSeq[i] );
		}
		partnersFresh = true;
	}


	return partners;
}


const AttributeMap& RemoteDevice::getAttributes()
{
	if(attributesFresh)
		return attributes;

	attributes.clear();

	unsigned i,j;
	bool success = false;
	string allowedValues;

	STI::Types::TAttributeSeq_var attribSeq;

	try {
		attribSeq = configureRef->attributes();
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getAttributes()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getAttributes()");
	}
	catch(CORBA::Exception&)
	{
	}

	if(success)
	{
		for(i = 0; i < attribSeq->length(); i++)
		{
			for(j = 0; j < attribSeq[i].values.length(); j++)
			{
				if(j > 0)
				{
					allowedValues += ",";
				}

				allowedValues += attribSeq[i].values[j];
			}
			attributes[CORBA::string_dup(attribSeq[i].key)] = 
				Attribute(CORBA::string_dup(attribSeq[i].value), allowedValues);

			allowedValues = "";		//reset
		}
		attributesFresh = true;
	}

	return attributes;
}


const vector<STI::Types::TDeviceChannel>& RemoteDevice::getChannels() const
{
	return channels;
}


STI::Types::TChannel RemoteDevice::getChannel(unsigned short channel) const
{
	STI::Types::TChannel newChannel;

	newChannel.device = getDevice();
	newChannel.channel = channel;

	for(unsigned i = 0; i < channels.size(); i++)
	{
		if(channels.at(i).channel == channel)
		{
			newChannel.inputType = channels.at(i).inputType;
			newChannel.outputType = channels.at(i).outputType;
			newChannel.type = channels.at(i).type;
			newChannel.channelName = channels.at(i).channelName;
			break;
		}
	}

	return newChannel;
}


const DataMeasurementVector& RemoteDevice::getMeasurements() const
{
	return measurements;
}


STI::Types::TDeviceEventSeq* RemoteDevice::getPartnerEvents(std::string deviceID)
{
	bool success = false;
//	STI::Types::TDeviceEventSeq_var events(new STI::Types::TDeviceEventSeq);
	STI::Types::TDeviceEventSeq* events = 0;

	try {
		events = commandLineRef->getPartnerEvents( deviceID.c_str() );
		success = true;
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getPartnerEvents()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getPartnerEvents()");
	}
	catch(CORBA::Exception&)
	{
	}

	if( !success )
	{
		events = new STI::Types::TDeviceEventSeq();
		events->length( 0 );
	}

	return events;

}

//void RemoteDevice::transferEvents(std::vector<STI::Types::TDeviceEvent_var>& events)
void RemoteDevice::transferEvents(std::vector<CompositeEvent>& events)
{
	eventsReady = false;
	doneTransfering = false;
	numberOfMeasurements = 0;

	using STI::Types::TDeviceEventSeq;
	using STI::Types::TDeviceEventSeq_var;

	TDeviceEventSeq_var eventSeq( new TDeviceEventSeq );
	eventSeq->length( events.size() );

	for(unsigned i=0; i < eventSeq->length(); i++)
	{
		eventSeq[i] = events[i].getTDeviceEvent();	//deep copy?
		if( events[i].getTDeviceEvent().isMeasurementEvent )
		{
			numberOfMeasurements++;
		}
	}

	try {
		eventsReady = deviceControlRef->transferEvents(eventSeq, false);
		doneTransfering = true;
		getTransferErrLog();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::transferEvents");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::transferEvents");
	}
	catch(CORBA::Exception&)
	{
	}

	doneTransfering = true;
}

void RemoteDevice::loadEvents()
{	
	try {
		deviceControlRef->load();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::loadEvents()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::loadEvents()");
	}
	catch(CORBA::Exception&)
	{
	}

}

bool RemoteDevice::prepareToPlay()
{
	bool result = false;

	try {
		result = deviceControlRef->prepareToPlay();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::prepareToPlay()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::prepareToPlay()");
	}
	catch(CORBA::Exception&)
	{
	}

	return result;
}

void RemoteDevice::playEvents()
{	
	try {
		deviceControlRef->play();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::playEvents()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::playEvents()");
	}
	catch(CORBA::Exception&)
	{
	}

}


void RemoteDevice::reset()
{
	stopWaitingForDependencies();
	doneTransfering = false;

	try {
		deviceControlRef->reset();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::reset()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::reset()");
	}
	catch(CORBA::Exception&)
	{
	}

}


void RemoteDevice::pause()
{
	try {
		deviceControlRef->pause();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::pause()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::pause()");
	}
	catch(CORBA::Exception&)
	{
	}

}

void RemoteDevice::stop()
{
	stopWaitingForDependencies();

	try {
		deviceControlRef->stop();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::stop()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::stop()");
	}
	catch(CORBA::Exception&)
	{
	}

}


bool RemoteDevice::eventsParsed()
{	
	bool parsed = false;

	try {
		parsed = deviceControlRef->eventsParsed();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsParsed()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsParsed()");
	}
	catch(CORBA::Exception&)
	{
	}

	return parsed;
}

bool RemoteDevice::eventsLoaded()
{	
	bool loaded = false;

	try {
		loaded = deviceControlRef->eventsLoaded();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsLoaded()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsLoaded()");
	}
	catch(CORBA::Exception&)
	{
	}

	return loaded;
}

bool RemoteDevice::eventsPlayed()
{
	bool played = false;

	try {
		played = deviceControlRef->eventsPlayed();
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsPlayed()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::eventsPlayed()");
	}
	catch(CORBA::Exception&)
	{
	}

	return played;
}


bool RemoteDevice::finishedEventsTransferAttempt()
{
	return doneTransfering;
}

bool RemoteDevice::eventsTransferSuccessful()
{
	return eventsReady;
}


void RemoteDevice::resetMeasurements()
{
	measurements.clear();
}

bool RemoteDevice::hasMeasurementsRemaining()
{
	return (measurements.size() < numberOfMeasurements);
}

void RemoteDevice::getNewMeasurementsFromServer()
{
	STI::Types::TMeasurementSeq_var newMeasurements;

	try {
		//get all the recent measurements that have not been retrieved yet.  This
		//is done by passing an index to the device which indicates which measurement
		//to start with (i.e., which ones not so send again).  In this case, we already
		//have measurements.size() number of measurements, so we want all new measurements
		//passed this index.
		newMeasurements = dataTransferRef->getRecentMeasurements( measurements.size() );
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::measurements");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::measurements");
	}
	catch(CORBA::Exception&)
	{
	}

	bool isNull = (newMeasurements.operator -> ()) == 0;
	unsigned currentSize = measurements.size();

	for(unsigned i = 0; (!isNull) && i < newMeasurements->length(); i++)
	{
		measurements.push_back( new DataMeasurement(newMeasurements[i], currentSize + i) );
//		measurements.back()->setData( newMeasurements[i].data );
	}
}



std::string RemoteDevice::printDeviceIndentiy() const
{
	std::stringstream id;
	id << tDevice.deviceName << " <" << tDevice.address 
		<< ", Module_" << tDevice.moduleNum << ">";

	return id.str();
}


std::string RemoteDevice::getTransferErrLog() const
{	
	string error = "";

	try {
		error = string( deviceControlRef->transferErr() );
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getTransferErrLog()");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::getTransferErrLog()");
	}
	catch(CORBA::Exception&)
	{
	}

	return error;
}
bool RemoteDevice::write(unsigned short channel, const MixedValue& value)
{
	bool success = false;
	try {
		success = getCommandLineRef()->writeChannel(channel, value.getTValMixed());
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::Exception&) {
	}
	catch(...) {
	}
	return success;
}

bool RemoteDevice::read(unsigned short channel, const MixedValue& valueIn, MixedData& dataOut)
{
	bool success = false;

	STI::Types::TDataMixed_var tData;

	try {
		success = getCommandLineRef()->readChannel(channel, valueIn.getTValMixed(), tData.out());
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::Exception&) {
	}
	catch(...) {
	}

	if( success )
	{
		dataOut.setValue( tData.in() );
	}

	return success;
}

std::string RemoteDevice::execute(string args)
{
	string result = "";
	try {
		result = getCommandLineRef()->execute( args.c_str() );
	}
	catch(CORBA::TRANSIENT& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::SystemException& ex) {
		cerr << printExceptionMessage(ex, "RemoteDevice::execute(...)");
	}
	catch(CORBA::Exception&)
	{
	}

	return result;
}


std::string RemoteDevice::printExceptionMessage(
	CORBA::SystemException& ex, std::string location) const
{
	std::stringstream error;

	string device_name = getDevice().deviceName;

//--------------------------- Remote Device Exception ---------------------------
//>>> Caught CORBA::TRANSIENT when contacting device 'RAM_Controller'.
//>>> Device ID: (RAM_Controller, ep-timing1.stanford.edu, Module 0)
//-------------------------------------------------------------------------------

	error << "--------------------------- Remote Device Exception ---------------------------"
		<< endl
		<< ">>> Caught CORBA::" << ex._name() << " when contacting device '"
		<< device_name << "'." << endl
		<< ">>> Device ID: (" << device_name << ", " << getDevice().address << ", Module " 
		<< getDevice().moduleNum << ")" << endl
		<<   "-------------------------------------------------------------------------------"
		<< endl << endl;
	
	//error << "Caught CORBA::" << ex._name() 
	//	<< " when contacting device '"
	//	<< device_name << "' (" 
	//	<< getDevice().address << ", Module " 
	//	<< getDevice().moduleNum << ")" << endl;
	//error << "    Location: " << location << endl;
	return error.str();
}


