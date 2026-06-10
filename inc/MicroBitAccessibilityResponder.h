#ifndef MICROBIT_ACCESSIBILITY_RESPONDER_H
#define MICROBIT_ACCESSIBILITY_RESPONDER_H

#include "CodalConfig.h"
#include "Event.h"
#include "ManagedBuffer.h"

#define ACCESSIBILITY_MAX_EVENT_SUBSCRIPTIONS 8

namespace codal
{
    struct EventSubscription
    {
        uint16_t source;
        uint16_t value;
    };
    
    struct SubscriptionList
    {
        EventSubscription subs[ACCESSIBILITY_MAX_EVENT_SUBSCRIPTIONS];
        int count;
    };
    
    class MicroBitAccessibilityResponder
    {
        public:
            virtual SubscriptionList getSubscriptions() const = 0;
            virtual ManagedBuffer onEvent(Event e) = 0;
            virtual ~MicroBitAccessibilityResponder() {};
    };
}

#endif