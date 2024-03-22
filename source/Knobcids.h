//------------------------------------------------------------------------
// Copyright(c) 2024 oxa.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace oxa {
//------------------------------------------------------------------------
static const Steinberg::FUID kKnobProcessorUID (0xA941DA31, 0x5023534E, 0x851BB723, 0x36DF16A2);
static const Steinberg::FUID kKnobControllerUID (0xCE285AF0, 0x231A5327, 0xAB4A5D6E, 0x997CD0FF);

#define KnobVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace oxa
