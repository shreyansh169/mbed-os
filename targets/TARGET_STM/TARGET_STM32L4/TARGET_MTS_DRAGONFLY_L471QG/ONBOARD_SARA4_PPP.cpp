/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ONBOARD_SARA4_PPP.h"
#include "cellular/onboard_modem_api.h"
#include "UARTSerial.h"
#include "CellularLog.h"

using namespace mbed;

ONBOARD_SARA4_PPP::ONBOARD_SARA4_PPP(FileHandle *fh) : SARA4_PPP(fh)
{
}

ONBOARD_SARA4_PPP::~ONBOARD_SARA4_PPP()
{
}

nsapi_error_t ONBOARD_SARA4_PPP::power_on()
{
    ::onboard_modem_init();
    ::onboard_modem_power_up();
    return NSAPI_ERROR_OK;
}

nsapi_error_t ONBOARD_SARA4_PPP::power_off()
{
    ::onboard_modem_power_down();
    ::onboard_modem_deinit();
    return NSAPI_ERROR_OK;
}

CellularDevice *CellularDevice::get_target_default_instance()
{
    static UARTSerial serial(MDMTXD, MDMRXD, MBED_CONF_SARA4_PPP_BAUDRATE);
#if DEVICE_SERIAL_FC
    if (MDMRTS != NC && MDMCTS != NC) {
        tr_info("Modem flow control: RTS %d CTS %d", MDMRTS, MDMCTS);
        serial.set_flow_control(SerialBase::RTSCTS, MDMRTS, MDMCTS);
    }
#endif
    static ONBOARD_SARA4_PPP device(&serial);
    return &device;
}