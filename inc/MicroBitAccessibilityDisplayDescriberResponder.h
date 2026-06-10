// TODO: this name is awful
#ifndef MICROBIT_ACCESSIBILITY_DISPLAY_DESCRIBER_RESPONDER_H
#define MICROBIT_ACCESSIBILITY_DISPLAY_DESCRIBER_RESPONDER_H

#include "MicroBitAccessibilityResponder.h"
#include "MicroBitDisplay.h" // TODO: if moving to codal-core, need to switch this to #include "AnimatedDisplay.h"
#include "ManagedString.h"

namespace codal
{
    class MicroBitAccessibilityDisplayDescriberResponder : public MicroBitAccessibilityResponder
    {
        MicroBitDisplay& display;

        ManagedString buildDescription();

    public:
        MicroBitAccessibilityDisplayDescriberResponder(MicroBitDisplay& display);

        virtual SubscriptionList getSubscriptions() const override;
        virtual ManagedBuffer onEvent(Event e) override;
    };
}

#endif