#pragma once

#include "InterruptSource.h"
#include <functional>
#include <cstdint>
#include <list>
#include <map>

namespace hal {
    class Core final
    {
    private:
        using InterruptHandler = std::function<void(hal::InterruptSource)>;
        using InterruptHandlersList = std::list<InterruptHandler>;

        Core();
    public:
        Core(const Core&)            = delete;
        Core(const Core&&)           = delete;
        Core& operator=(const Core&) = delete;
        Core& operator=(Core&&)      = delete;
        ~Core() noexcept             = default;

        static Core& GetInstance();

        bool Initialize();
        /**
         * Interrupt Handlers
         */
        void On_Interrupt(InterruptSource source);

        void AddInterruptHandler(const InterruptHandler& handler, InterruptSource source);
    private:
        void Flash_SetPrefetchBufferState(bool state);
        bool InitInterrupts();
        bool InitClock();

        void Handler_SystemClock(InterruptSource callFrom);

        static const uint32_t RC_Calibration_Value;
        static const uint32_t NVIC_Priority_Group;

        bool m_initCompleted;
        std::map<InterruptSource, InterruptHandlersList> m_interruptRouting;
    };
}