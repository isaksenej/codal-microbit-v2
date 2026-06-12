#ifndef MICROBIT_ACCESSIBILITY_H
#define MICROBIT_ACCESSIBILITY_H

#include "CodalComponent.h"
#include "CodalConfig.h" //idk if i need this
#include "NRF52Serial.h" //serial for debuggging
#include "Event.h"
#include "MicroBitDisplay.h"
// #include "ManagedString.h"

#include "MicroBitAccessibilityResponder.h"
#include "MicroBitAccessibilityTransmitter.h"

#define DEVICE_ID_ACCESSIBILITY       51

namespace codal
{
    class MicroBitAccessibility : public CodalComponent
    {
        MicroBitAccessibilityResponder* responder;
        MicroBitAccessibilityTransmitter* transmitter;
        NRF52Serial* serial; //serial for debugging

        EventSubscription activeSubs[ACCESSIBILITY_MAX_EVENT_SUBSCRIPTIONS];
        int activeCount;

        void onEvent(Event e);
        void applySubscriptions();
        void removeSubscriptions();

        public:

        // MicroBitAccessibility(MicroBitAccessibilityResponder& responder, MicroBitAccessibilityTransmitter& transmitter, uint16_t id = DEVICE_ID_ACCESSIBILITY);
        //constructor with serial for debugging:
        MicroBitAccessibility(MicroBitAccessibilityResponder& responder, MicroBitAccessibilityTransmitter& transmitter, NRF52Serial& serial, uint16_t id = DEVICE_ID_ACCESSIBILITY);

        void setResponder(MicroBitAccessibilityResponder& r);
        void setTransmitter(MicroBitAccessibilityTransmitter& t);

        virtual int init() override;
    };
}

#endif