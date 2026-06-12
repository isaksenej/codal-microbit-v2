#include "MicroBitAccessibilityDotMatrixResponder.h"

using namespace codal;

MicroBitAccessibilityDotMatrixResponder::MicroBitAccessibilityDotMatrixResponder(
    MicroBitDisplay& _display)
    : display(_display)
{
}

SubscriptionList MicroBitAccessibilityDotMatrixResponder::getSubscriptions() const
{
    SubscriptionList list;
    list.count = 1;
    list.subs[0].source = DEVICE_ID_DISPLAY_MONITOR;
    list.subs[0].value  = DISPLAY_MONITOR_EVT_UPDATED;
    return list;
}

ManagedBuffer MicroBitAccessibilityDotMatrixResponder::onEvent(Event e)
{
    uint8_t dots[5] = {0, 0, 0, 0, 0};

    // Jacdac dot-matrix dots register is column-major, LSB = top row.
    // codal display image is row-major — transpose here.
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            if (display.image.getPixelValue(x, y) > 0)
                dots[x] |= (1 << y);

    return ManagedBuffer(dots, 5);
}