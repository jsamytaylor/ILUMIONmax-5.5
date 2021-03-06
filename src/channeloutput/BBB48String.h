#pragma once
/*
 *   BeagleBone Black PRU 48-string handler for Falcon Player (FPP)
 *
 *   Copyright (C) 2013-2018 the Falcon Player Developers
 *      Initial development by:
 *      - David Pitts (dpitts)
 *      - Tony Mace (MyKroFt)
 *      - Mathew Mrosko (Materdaddy)
 *      - Chris Pinkham (CaptainMurdoch)
 *      For additional credits and developers, see credits.php.
 *
 *   The Falcon Player (FPP) is free software; you can redistribute it
 *   and/or modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <vector>

#include "ChannelOutputBase.h"
#include "PixelString.h"
#include "util/BBBPruUtils.h"

#define MAX_WS2811_TIMINGS 128

// structure of the data at the start of the PRU ram
// that the pru program expects to see
typedef struct {
    // in the DDR shared with the PRU
    uintptr_t address_dma;

    // write 1 to start, 0xFF to abort. will be cleared when started
    volatile unsigned command;
    volatile unsigned response;

    uintptr_t address_dma_gpio0;

    uint16_t timings[MAX_WS2811_TIMINGS];
} __attribute__((__packed__)) BBB48StringData;

class BBB48StringOutput : public ChannelOutputBase {
public:
    BBB48StringOutput(unsigned int startChannel, unsigned int channelCount);
    virtual ~BBB48StringOutput();

    virtual int Init(Json::Value config) override;
    virtual int Close(void) override;

    virtual int SendData(unsigned char* channelData) override;
    virtual void PrepData(unsigned char* channelData) override;
    virtual void DumpConfig(void) override;

    virtual void GetRequiredChannelRanges(const std::function<void(int, int)>& addRange) override;

private:
    void StopPRU(bool wait = true);
    int StartPRU(bool both);

    std::string m_subType;

    class FrameData {
    public:
        std::vector<int> gpioStringMap;
        uint8_t* lastData = nullptr;
        uint8_t* curData = nullptr;
        uint32_t frameSize = 0;
        int maxStringLen = 0;
        bool copyToPru = true;
    } m_gpio0Data, m_gpioData;
    std::vector<PixelString*> m_strings;

    uint32_t m_curFrame;
    int m_stallCount;

    BBBPru* m_pru;
    BBB48StringData* m_pruData;

    BBBPru* m_pru0;
    BBB48StringData* m_pru0Data;

    void prepData(FrameData& d, unsigned char* channelData);
    void sendData(FrameData& d, uintptr_t* dptr);
    void createOutputLengths(FrameData& d, const std::string& pfx, std::vector<std::string>& args);
};
