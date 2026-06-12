#include "MicroBitDisplayMonitor.h"

using namespace codal;

MicroBitDisplayMonitor::MicroBitDisplayMonitor(MicroBitDisplay& _display) : display(_display) {
    memset(lastFrame, 0, sizeof(lastFrame));
    pollTick = 0;
    status |= DEVICE_COMPONENT_STATUS_SYSTEM_TICK;
}

int MicroBitDisplayMonitor::init() {
    memcpy(lastFrame, display.image.getBitmap(), 25);
    status |= DEVICE_COMPONENT_RUNNING;
    return DEVICE_OK;
}

void MicroBitDisplayMonitor::periodicCallback() {
    if (!(status & DEVICE_COMPONENT_RUNNING)) return;

    // Rate-limit polling so event firing can't outpace the serial drain rate.
    pollTick += (SCHEDULER_TICK_PERIOD_US / 1000);
    if (pollTick < DISPLAY_MONITOR_POLL_PERIOD)
        return;
    pollTick = 0;

    uint8_t* bitmap = display.image.getBitmap();
    if (memcmp(lastFrame, bitmap, 25) == 0) return;
    memcpy(lastFrame, bitmap, 25);
    Event(DEVICE_ID_DISPLAY_MONITOR, DISPLAY_MONITOR_EVT_UPDATED);
}