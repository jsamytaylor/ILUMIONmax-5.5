/*
 *   ColorOrder definitions for Falcon Player (FPP)
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

#include "ColorOrder.h"

FPPColorOrder ColorOrderFromString(const std::string& colorOrderStr) {
    if (colorOrderStr == "RGB")
        return kColorOrderRGB;

    if (colorOrderStr == "RBG")
        return kColorOrderRBG;

    if (colorOrderStr == "GRB")
        return kColorOrderGRB;

    if (colorOrderStr == "GBR")
        return kColorOrderGBR;

    if (colorOrderStr == "BRG")
        return kColorOrderBRG;

    if (colorOrderStr == "BGR")
        return kColorOrderBGR;

    if (colorOrderStr == "W")
        return kColorOrderONE;

    return kColorOrderRGB;
}

const std::string ColorOrderToString(FPPColorOrder colorOrder) {
    switch (colorOrder) {
    case kColorOrderRGB:
        return std::string("RGB");
    case kColorOrderRBG:
        return std::string("RBG");
    case kColorOrderGBR:
        return std::string("GBR");
    case kColorOrderGRB:
        return std::string("GRB");
    case kColorOrderBGR:
        return std::string("BGR");
    case kColorOrderBRG:
        return std::string("BRG");
    case kColorOrderONE:
        return std::string("W");
    }

    return std::string("UNKNOWN");
}
