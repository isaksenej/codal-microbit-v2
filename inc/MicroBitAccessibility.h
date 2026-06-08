#ifndef MICROBIT_ACCESSIBILITY_H
#define MICROBIT_ACCESSIBILITY_H

#include "CodalComponent.h"
#include "NRF52Serial.h"
#include "Event.h"
#include "MicroBitDisplay.h"
#include "ManagedString.h"

namespace codal
{
    class MicroBitAccessibility : public CodalComponent
    {
        MicroBitDisplay& display;
        NRF52Serial& serial;

        void displayEvent(Event e);
        ManagedString buildDescription();

    public:
        MicroBitAccessibility(MicroBitDisplay& _display, NRF52Serial& _serial);
        virtual int init() override;
    };
}

#endif