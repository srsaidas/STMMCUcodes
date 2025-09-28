/* ITM (Instrumentation Trace Macrocell) Configuration Start */

/* Define memory-mapped registers for ITM and Debug MCU */
#define DBGMCU_CR           *((volatile uint32_t*)0xE0042004)  // Debug MCU Control Register
#define ITM_LOCK_ACCESS     *((volatile uint32_t*)0xE0000FB0U) // ITM Lock Access Register
#define ITM_TRACE_CONTROL   *((volatile uint32_t*)0xE0000E80U) // ITM Trace Control Register
#define ITM_TRACE_PRIVILEGE *((volatile uint32_t*)0xE0000E40U) // ITM Trace Privilege Register
#define ITM_TRACE_ENABLE    *((volatile uint32_t*)0xE0000E00U) // ITM Trace Enable Register
#define ITM_STIMULUS_PORT0  *((volatile uint32_t*)0xE0000000U) // ITM Stimulus Port 0 Register

/* Reference: STM32 Reference Manual RM0385, Page 1675 */

/**
 * @brief Enables the ITM (Instrumentation Trace Macrocell) for debugging.
 * This function configures the necessary registers to enable ITM functionality.
 * 
 * Steps:
 * 1. Enable Debug MCU tracing by setting the appropriate bit in DBGMCU_CR.
 * 2. Unlock ITM registers by writing the access key to ITM_LOCK_ACCESS.
 * 3. Configure ITM_TRACE_CONTROL to enable tracing and set the required configuration.
 * 4. Enable ITM tracing by setting ITM_TRACE_ENABLE.
 * 5. Enable ITM trace privilege by setting ITM_TRACE_PRIVILEGE.
 */
void ITM_enable(void)
{
    // Enable Debug MCU tracing
    DBGMCU_CR |= 1 << 5;

    // Unlock ITM registers by writing the access key
    ITM_LOCK_ACCESS = 0xC5ACCE55;

    // Configure ITM Trace Control Register
    ITM_TRACE_CONTROL = 0x00010005;

    // Enable ITM tracing
    ITM_TRACE_ENABLE = 0x1;

    // Enable ITM trace privilege
    ITM_TRACE_PRIVILEGE = 0x1;
}

/**
 * @brief Sends a character to the ITM Stimulus Port 0.
 * This function waits until the ITM is ready and then writes the character to the stimulus port.
 * 
 * @param ch The character to send (uint8_t).
 * 
 * Steps:
 * 1. Wait until the ITM is ready to accept data by checking the busy bit in ITM_TRACE_CONTROL.
 * 2. Write the character to ITM_STIMULUS_PORT0.
 */
void ITM_sendChar(uint8_t ch)
{
    // Wait until the ITM is ready to accept data
    while ((ITM_TRACE_CONTROL & (1 << 23)));

    // Write the character to the ITM Stimulus Port 0
    ITM_STIMULUS_PORT0 = ch;
}

/* ITM Configuration End */
