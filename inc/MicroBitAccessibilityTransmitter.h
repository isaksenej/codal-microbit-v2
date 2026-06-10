#ifndef MICROBIT_ACCESSIBILITY_TRANSMITTER_H
#define MICROBIT_ACCESSIBILITY_TRANSMITTER_H

#include "CodalConfig.h"
#include "ManagedBuffer.h"

namespace codal
{
    class MicroBitAccessibilityTransmitter
    {
        public:
            virtual void transmit(ManagedBuffer message) = 0;
            virtual ~MicroBitAccessibilityTransmitter() {};
    };
}

#endif