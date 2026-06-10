#ifndef MICROBIT_ACCESSIBILITY_SERIAL_TRANSMITTER_H
#define MICROBIT_ACCESSIBILITY_SERIAL_TRANSMITTER_H

#include "MicroBitAccessibilityTransmitter.h"
#include "Serial.h"

namespace codal
{
    class MicroBitAccessibilitySerialTransmitter : public MicroBitAccessibilityTransmitter
    {
        Serial& serial;

    public:
        MicroBitAccessibilitySerialTransmitter(Serial& serial);
        virtual void transmit(ManagedBuffer message) override;
    };
}

#endif