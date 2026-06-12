// if you need serial for debugging, you need to edit here, the header, and MicroBit.cpp
#include "MicroBitAccessibility.h"

using namespace codal;

// MicroBitAccessibility::MicroBitAccessibility(MicroBitAccessibilityResponder& _responder, MicroBitAccessibilityTransmitter& _transmitter)
//     : responder(&_responder), transmitter(&_transmitter)
// {
// }

// constructor with serial for debugging
MicroBitAccessibility::MicroBitAccessibility(MicroBitAccessibilityResponder& _responder, MicroBitAccessibilityTransmitter& _transmitter, NRF52Serial& _serial, uint16_t _id)
    : responder(&_responder), transmitter(&_transmitter), serial(&_serial)
{
    id = _id;
}

int MicroBitAccessibility::init()
{
    // serial->send(ManagedString("Accessibility Initialised :)\r\n"));
    applySubscriptions();
    
    return DEVICE_OK;
}

void MicroBitAccessibility::applySubscriptions()
{
    if (!EventModel::defaultEventBus)
        return;

    SubscriptionList subs = responder->getSubscriptions();

    for (int i = 0; i < subs.count; i++)
    {
        EventSubscription tempSub = subs.subs[i]; //for some reason, using subs.subs[i].source/value inside of the listen call causes a crash. So here we are. 
        // EventModel::defaultEventBus->listen(subs.subs[i].source, subs.subs[i].value, this, &MicroBitAccessibility::onEvent, MESSAGE_BUS_LISTENER_IMMEDIATE); //what caused the crash
        EventModel::defaultEventBus->listen(tempSub.source, tempSub.value, this, &MicroBitAccessibility::onEvent);
        activeSubs[i] = tempSub;
    }

    activeCount = subs.count;
}

void MicroBitAccessibility::removeSubscriptions()
{
    if (!EventModel::defaultEventBus)
        return;

    for (int i = 0; i < activeCount; i++)
    {
        EventSubscription tempSub = activeSubs[i]; //for some reason, using activeSubs[i].source/value inside of the ignore call causes a crash. So here we are. 
        EventModel::defaultEventBus->ignore(tempSub.source, tempSub.value, this, &MicroBitAccessibility::onEvent);
    }

    activeCount = 0;
}

void MicroBitAccessibility::setResponder(MicroBitAccessibilityResponder& r)
{
    // serial->send(ManagedString("setResp\r\n"),SYNC_SPINWAIT);
    removeSubscriptions();
    // serial->send(ManagedString("removed\r\n"));
    responder = &r;
    applySubscriptions();
    // serial->send(ManagedString("applied\r\n"));
}

void MicroBitAccessibility::setTransmitter(MicroBitAccessibilityTransmitter& t)
{
    transmitter = &t;
}

void MicroBitAccessibility::onEvent(Event e)
{
    ManagedBuffer message = responder->onEvent(e);
    // if there's nothing to send, don't send it
    if (message.length() > 0)
        transmitter->transmit(message);
}