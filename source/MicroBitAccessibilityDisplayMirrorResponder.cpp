#include "MicroBitAccessibilityDisplayMirrorResponder.h"

using namespace codal;

MicroBitAccessibilityDisplayMirrorResponder::MicroBitAccessibilityDisplayMirrorResponder(MicroBitDisplay& _display)
    : display(_display)
{
}

SubscriptionList MicroBitAccessibilityDisplayMirrorResponder::getSubscriptions() const
{
    SubscriptionList subs;
    subs.subs[0] = {DEVICE_ID_DISPLAY_MONITOR, DISPLAY_MONITOR_EVT_UPDATED};
    subs.count = 1;
    return subs;
}

// ManagedBuffer MicroBitAccessibilityDisplayMirrorResponder::onEvent(Event e)
// {
//     if(e.value==DISPLAY_MONITOR_EVT_UPDATED){
//         return ManagedBuffer(display.image.getBitmap(), 25); //simplest first, just raw bytes. 
//     }
//     return ManagedBuffer();
// }

ManagedBuffer MicroBitAccessibilityDisplayMirrorResponder::onEvent(Event e)
{
    uint8_t* bitmap = display.image.getBitmap();
    uint8_t out[37];   // 5 rows x ("#.#.#" + \r\n) + blank separator line
    int k = 0;
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
            out[k++] = bitmap[y * 5 + x] ? '#' : '.';
        out[k++] = '\r';
        out[k++] = '\n';
    }
    out[k++] = '\r';
    out[k++] = '\n';
    return ManagedBuffer(out, k);
}