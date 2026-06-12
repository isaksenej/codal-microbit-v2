#ifndef MICROBIT_DISPLAY_MONITOR_H
#define MICROBIT_DISPLAY_MONITOR_H

#include "CodalConfig.h"
#include "CodalComponent.h"
#include "MicroBitDisplay.h"

#define DEVICE_ID_DISPLAY_MONITOR 50 // Suggested range for device-specific IDs: 50-79

#define DISPLAY_MONITOR_EVT_UPDATED 1

#define DISPLAY_MONITOR_POLL_PERIOD 50   // minimum ms between display polls - could make this a constructor parameter?


namespace codal {
    class MicroBitDisplayMonitor : public CodalComponent {
        MicroBitDisplay& display;
        uint8_t lastFrame[5][5]; // main issue for moving to codal-core - can no longer hardcode this value
        uint16_t pollTick;

    public:
        MicroBitDisplayMonitor(MicroBitDisplay& display);
        virtual int init() override;
        virtual void periodicCallback() override;
    };
}

#endif