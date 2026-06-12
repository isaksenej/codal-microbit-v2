#include "MicroBitAccessibilityJacdacTransmitter.h"
#include "codal_target_hal.h"
#include "ErrorNo.h"

using namespace codal;

static volatile bool jd_tx_done = false;

static void jd_sws_irq(uint16_t errCode)
{
    if (errCode == SWS_EVT_DATA_SENT)
        jd_tx_done = true;
}

static uint16_t jd_crc16(const uint8_t *p, int len)
{
    uint16_t crc = 0xffff;
    for (int i = 0; i < len; ++i)
    {
        uint8_t x = (crc >> 8) ^ p[i];
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t)x << 12) ^ ((uint16_t)x << 5) ^ x;
    }
    return crc;
}

MicroBitAccessibilityJacdacTransmitter::MicroBitAccessibilityJacdacTransmitter(
    Pin& pin, uint32_t _serviceClass, uint16_t _reg)
    : sws(pin), serviceClass(_serviceClass), reg(_reg)
{
    sws.setBaud(1000000);
    sws.setIRQ(jd_sws_irq);
    sws.setMode(SingleWireDisconnected);
    sws.p.getDigitalValue(PullMode::Up);
}

void MicroBitAccessibilityJacdacTransmitter::transmit(ManagedBuffer payload)
{
    int plen = payload.length();
    if (plen <= 0 || plen > JD_MAX_PAYLOAD){
        // return DEVICE_INVALID_PARAMETER;
        return;
    }

    int flen = JD_FRAME_HEADER_SIZE + plen;

    frame[2]  = plen + 4;
    frame[3]  = JD_FRAME_FLAG_COMMAND | JD_FRAME_FLAG_IDENTIFIER_IS_SERVICE_CLASS;
    frame[4]  = serviceClass & 0xff;
    frame[5]  = (serviceClass >> 8) & 0xff;
    frame[6]  = (serviceClass >> 16) & 0xff;
    frame[7]  = (serviceClass >> 24) & 0xff;
    frame[8]  = 0xAA;
    frame[9]  = 0xAA;
    frame[10] = 0xAA;
    frame[11] = 0xAA;
    frame[12] = plen;
    frame[13] = JD_SERVICE_INDEX_BROADCAST;
    uint16_t cmd = JD_CMD_SET_REGISTER | reg;
    frame[14] = cmd & 0xff;
    frame[15] = (cmd >> 8) & 0xff;
    // memcpy(frame + 16, payload.getBytes(), plen);
    memcpy(frame + 16, &payload[0], plen);

    uint16_t c = jd_crc16(frame + 2, flen - 2);
    frame[0] = c & 0xff;
    frame[1] = (c >> 8) & 0xff;

    // Carrier sense: bus idles high; a low means someone else is transmitting.
    if (sws.p.getDigitalValue(PullMode::Up) == 0){
        // return DEVICE_BUSY; // possible route for interface adjustment? Probably quite reasonable. 
        return;
    }

    jd_tx_done = false;

    target_disable_irq();
    sws.p.setDigitalValue(0);   // start pulse: ~11µs low
    target_wait_us(11);
    sws.p.setDigitalValue(1);
    target_wait_us(50);         // pre-data window: 40-89µs per spec
    sws.sendDMA(frame, flen);
    target_enable_irq();

    int timeout = 5000;
    while (!jd_tx_done && timeout-- > 0)
        target_wait_us(1);

    // End pulse, then release pin back to idle input+pull-up.
    sws.setMode(SingleWireDisconnected);
    sws.p.getDigitalValue();
    sws.p.setDigitalValue(0);
    target_wait_us(11);
    sws.p.setDigitalValue(1);
    sws.setMode(SingleWireDisconnected);
    sws.p.getDigitalValue(PullMode::Up);

    // return jd_tx_done ? DEVICE_OK : DEVICE_CANCELLED;
    return;
}