#pragma once

namespace hal {
    enum class InterruptSource {
        HARD_FAULT,
        MEM_MANAGE,
        NMI,
        BUS_FAULT,
        USAGE_FAULT,
        SVC,
        DEBUG_MONITOR,
        PEND_SV,
        SYSTEM_TICK
    };
}