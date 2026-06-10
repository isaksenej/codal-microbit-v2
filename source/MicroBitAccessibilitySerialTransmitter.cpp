#include "MicroBitAccessibilitySerialTransmitter.h"

using namespace codal;

MicroBitAccessibilitySerialTransmitter::MicroBitAccessibilitySerialTransmitter(Serial& _serial) : serial(_serial)
{
}

void MicroBitAccessibilitySerialTransmitter::transmit(ManagedBuffer message)
{
    serial.send(message.getBytes(), message.length(), SYNC_SPINWAIT); //busy wait instead of ceding to the scheduler
}