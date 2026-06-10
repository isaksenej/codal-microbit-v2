#include "MicroBitAccessibilityDisplayDescriberResponder.h"

using namespace codal;

MicroBitAccessibilityDisplayDescriberResponder::MicroBitAccessibilityDisplayDescriberResponder(MicroBitDisplay& _display)
    : display(_display)
{
}

SubscriptionList MicroBitAccessibilityDisplayDescriberResponder::getSubscriptions() const
{
    SubscriptionList subs;
    subs.subs[0] = {DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_COMPLETE};
    subs.subs[1] = {DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_STARTED};
    subs.subs[2] = {DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_STOPPED};
    subs.count = 3;
    return subs;
}

ManagedBuffer MicroBitAccessibilityDisplayDescriberResponder::onEvent(Event e)
{
    ManagedString message;
    switch (e.value)
    {
    case DISPLAY_EVT_ANIMATION_COMPLETE:
        message = ManagedString("Animation completed.\r\n");
        break;
    
    case DISPLAY_EVT_ANIMATION_STARTED:
        message = buildDescription();
        break;
    
    case DISPLAY_EVT_ANIMATION_STOPPED:
        message = ManagedString("Animation stopped.\r\n");
        break;
    
    default:
        // unrecognised event (that we've subscribed to)
        message = ManagedString("ERR: unhandled event\r\n"); // If we'd prefer to fail silently: return ManagedBuffer();
        break;
    }
    return ManagedBuffer((uint8_t*)message.toCharArray(), message.length());
}

ManagedString MicroBitAccessibilityDisplayDescriberResponder::buildDescription()
{
    AnimationMode mode = display.getAnimationMode();
    ManagedString message = display.getCurrentText(); // TODO: atm could put the +"\r\n" on here, let's see how it ends up. Could also move that outside of this function altogether. depends how you concieve of this function's purpose i guess. 

    if (mode == ANIMATION_MODE_NONE || mode == ANIMATION_MODE_STOPPED)
        return message+"\r\n"; // should basically never happen?

    if (mode == ANIMATION_MODE_SCROLL_TEXT || mode == ANIMATION_MODE_PRINT_TEXT || mode == ANIMATION_MODE_PRINT_CHARACTER)
        return "Text: "+message+"\r\n";
    
    if (mode == ANIMATION_MODE_SCROLL_IMAGE || mode == ANIMATION_MODE_ANIMATE_IMAGE || mode == ANIMATION_MODE_ANIMATE_IMAGE_WITH_CLEAR || mode == ANIMATION_MODE_PRINT_IMAGE)
        return "Image: "+message+"\r\n";

    return "ERR: "+message+"\r\n"; // If we'd prefer to fail silently: return ManagedString();
}