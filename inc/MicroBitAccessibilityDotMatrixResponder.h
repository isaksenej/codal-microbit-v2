#ifndef MICROBIT_ACCESSIBILITY_DOT_MATRIX_RESPONDER_H
#define MICROBIT_ACCESSIBILITY_DOT_MATRIX_RESPONDER_H

#include "MicroBitAccessibilityResponder.h"
#include "MicroBitDisplay.h"
#include "MicroBitDisplayMonitor.h"

namespace codal
{
    class MicroBitAccessibilityDotMatrixResponder : public MicroBitAccessibilityResponder
    {
        MicroBitDisplay& display;

    public:
        MicroBitAccessibilityDotMatrixResponder(MicroBitDisplay& display);
        virtual SubscriptionList getSubscriptions() const override;
        virtual ManagedBuffer onEvent(Event e) override;
    };
}

#endif