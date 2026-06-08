#include "MicroBitAccessibility.h"

using namespace codal;

MicroBitAccessibility::MicroBitAccessibility(MicroBitDisplay& _display, NRF52Serial& _serial)
    : display(_display), serial(_serial)
{
}

int MicroBitAccessibility::init()
{
    serial.send(ManagedString("Accessibility Initialised :)\r\n"));

    if (EventModel::defaultEventBus){
        EventModel::defaultEventBus->listen(DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_COMPLETE, this, &MicroBitAccessibility::displayEvent, MESSAGE_BUS_LISTENER_IMMEDIATE);
        EventModel::defaultEventBus->listen(DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_STARTED, this, &MicroBitAccessibility::displayEvent, MESSAGE_BUS_LISTENER_IMMEDIATE);
        EventModel::defaultEventBus->listen(DEVICE_ID_DISPLAY, DISPLAY_EVT_ANIMATION_STOPPED, this, &MicroBitAccessibility::displayEvent, MESSAGE_BUS_LISTENER_IMMEDIATE);
    }
    
    return DEVICE_OK;
}

void MicroBitAccessibility::displayEvent(Event e)
{
    switch (e.value)
    {
    case DISPLAY_EVT_ANIMATION_COMPLETE:
        serial.send(ManagedString("Animation completed.\r\n"), SYNC_SPINWAIT); //busy wait instead of ceding to the scheduler
        break;
    
    case DISPLAY_EVT_ANIMATION_STARTED:
        serial.send(buildDescription(), SYNC_SPINWAIT);
        break;
    
    case DISPLAY_EVT_ANIMATION_STOPPED:
        serial.send(ManagedString("Animation stopped.\r\n"), SYNC_SPINWAIT);
        break;
    
    default:
        // unrecognised event (that we've subscribed to)
        serial.send(ManagedString("ERR: unhandled event\r\n"), SYNC_SPINWAIT);
        break;
    }
}

ManagedString MicroBitAccessibility::buildDescription()
{
    AnimationMode mode = display.getAnimationMode();
    ManagedString message = display.getCurrentText(); // TODO: atm could put the +"\r\n" on here, let's see how it ends up. Could also move that outside of this function altogether. depends how you concieve of this function's purpose i guess. 

    if (mode == ANIMATION_MODE_NONE || mode == ANIMATION_MODE_STOPPED)
        return message+"\r\n"; // should basically never happen?

    if (mode == ANIMATION_MODE_SCROLL_TEXT || mode == ANIMATION_MODE_PRINT_TEXT || mode == ANIMATION_MODE_PRINT_CHARACTER)
        return "Text: "+message+"\r\n";
    
    if (mode == ANIMATION_MODE_SCROLL_IMAGE || mode == ANIMATION_MODE_ANIMATE_IMAGE || mode == ANIMATION_MODE_ANIMATE_IMAGE_WITH_CLEAR || mode == ANIMATION_MODE_PRINT_IMAGE)
        return "Image: "+message+"\r\n";

    return "ERR: "+message+"\r\n";
}