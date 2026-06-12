#ifndef MICROBIT_ACCESSIBILITY_DISPLAY_MIRROR_RESPONDER_H
#define MICROBIT_ACCESSIBILITY_DISPLAY_MIRROR_RESPONDER_H

#include "MicroBitAccessibilityResponder.h"
#include "MicroBitDisplay.h" // TODO: if moving to codal-core, need to switch this to #include "AnimatedDisplay.h"
#include "MicroBitDisplayMonitor.h"

namespace codal
{
    class MicroBitAccessibilityDisplayMirrorResponder : public MicroBitAccessibilityResponder
    {
        MicroBitDisplay& display;

    public:
        MicroBitAccessibilityDisplayMirrorResponder(MicroBitDisplay& display);

        virtual SubscriptionList getSubscriptions() const override;
        virtual ManagedBuffer onEvent(Event e) override;
    };
}

#endif