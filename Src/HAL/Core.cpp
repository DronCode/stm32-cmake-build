#include "Core.h"
#include "stm32f1xx_hal.h"

#include <cassert>

extern "C" {
    void HardFault_Handler()
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::HARD_FAULT);
    }
    void MemManage_Handler()
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::MEM_MANAGE);
    }
    void NMI_Handler()
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::NMI);
    }
    void BusFault_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::BUS_FAULT);
    }
    void UsageFault_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::USAGE_FAULT);
    }
    void SVC_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::SVC);
    }
    void DebugMon_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::DEBUG_MONITOR);
    }
    void PendSV_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::PEND_SV);
    }
    void SysTick_Handler(void)
    {
        hal::Core::GetInstance().On_Interrupt(hal::InterruptSource::SYSTEM_TICK);
    }
}

namespace hal {
    const uint32_t Core::RC_Calibration_Value = 16;
    const uint32_t Core::NVIC_Priority_Group  = NVIC_PRIORITYGROUP_4;

    Core::Core()
        : m_initCompleted(false)
    {
    }

    Core& Core::GetInstance()
    {
        static Core* instance = nullptr;

        if (!instance)
        {
            instance = new Core;
        }

        return *instance;
    }

    bool Core::Initialize()
    {
        if (m_initCompleted)
        {
            return true;
        }

        bool result = false;

        Flash_SetPrefetchBufferState(true);

        result = InitInterrupts();
        if (!result)
        {
            return false;
        }

        result = InitClock();
        if (!result)
        {
            return false;
        }

        m_initCompleted = true;

        AddInterruptHandler(std::bind(&Core::Handler_SystemClock, this, std::placeholders::_1),
                            InterruptSource::SYSTEM_TICK);

        return result;
    }

    void Core::On_Interrupt(InterruptSource source)
    {
        auto iter = m_interruptRouting.find(source);
        if (iter != m_interruptRouting.end())
        {
            for (auto& processor : (*iter).second)
            {
                processor.operator()((*iter).first);
            }
        }
    }

    void Core::AddInterruptHandler(const InterruptHandler &handler, InterruptSource source)
    {
        m_interruptRouting[source].push_back(handler);
    }

    void Core::Flash_SetPrefetchBufferState(bool state)
    {
        if (state)
        {
            FLASH->ACR |= FLASH_ACR_PRFTBE;
        }
        else
        {
            FLASH->ACR &= (~FLASH_ACR_PRFTBE);
        }
    }

    bool Core::InitInterrupts()
    {
        NVIC_SetPriorityGrouping(Core::NVIC_Priority_Group);

        return (HAL_InitTick(TICK_INT_PRIORITY) == HAL_OK);
    }

    void Core::Handler_SystemClock(InterruptSource/*callFrom*/)
    {
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
    }

    bool Core::InitClock()
    {
        SysTick_Config(SystemCoreClock / 1000U);

        const auto encodedPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), TICK_INT_PRIORITY, 0U);
        NVIC_SetPriority(SysTick_IRQn, encodedPriority);

        RCC_OscInitTypeDef rcc_oscInitStruct;
        RCC_ClkInitTypeDef rcc_clkInitStruct;

        rcc_oscInitStruct.OscillatorType        = RCC_OSCILLATORTYPE_HSI;
        rcc_oscInitStruct.HSIState              = RCC_HSI_ON;
        rcc_oscInitStruct.HSICalibrationValue   = Core::RC_Calibration_Value;
        rcc_oscInitStruct.PLL.PLLState          = RCC_PLL_NONE;

        if (HAL_RCC_OscConfig(&rcc_oscInitStruct) != HAL_OK)
        {
            //TODO: Send error message to SWO
            return false;
        }

        HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

        HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

        return true;
    }
}