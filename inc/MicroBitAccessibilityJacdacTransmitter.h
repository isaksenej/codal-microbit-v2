#ifndef MICROBIT_ACCESSIBILITY_JACDAC_TRANSMITTER_H
#define MICROBIT_ACCESSIBILITY_JACDAC_TRANSMITTER_H

#include "MicroBitAccessibilityTransmitter.h"
#include "ZSingleWireSerial.h"
#include "Pin.h"

#define JD_SERVICE_CLASS_DOT_MATRIX               0x110d154b
#define JD_REG_DOT_MATRIX_DOTS                    0x02
#define JD_CMD_SET_REGISTER                       0x2000
#define JD_FRAME_FLAG_COMMAND                     0x01
#define JD_FRAME_FLAG_IDENTIFIER_IS_SERVICE_CLASS 0x04
#define JD_SERVICE_INDEX_BROADCAST                0x3d

#define JD_FRAME_HEADER_SIZE                      16
#define JD_MAX_PAYLOAD                            32

namespace codal
{
    class MicroBitAccessibilityJacdacTransmitter : public MicroBitAccessibilityTransmitter
    {
        ZSingleWireSerial sws;
        uint32_t serviceClass;
        uint16_t reg;

        // Member (not stack local): UARTE DMA reads this buffer asynchronously
        // after sendDMA() returns; a stack local would be paged out on fiber switch.
        uint8_t frame[JD_FRAME_HEADER_SIZE + JD_MAX_PAYLOAD];

    public:
        MicroBitAccessibilityJacdacTransmitter(Pin& pin,
            uint32_t serviceClass = JD_SERVICE_CLASS_DOT_MATRIX,
            uint16_t reg = JD_REG_DOT_MATRIX_DOTS);

        virtual void transmit(ManagedBuffer payload) override;
    };
}

#endif