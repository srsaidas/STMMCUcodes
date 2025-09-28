# STMMCUcodes
<!-- Main title of the repository -->

A collection of C code snippets and example programs for STM microcontrollers.  
<!-- Short description of what this repo is about -->

## Contents
<!-- Explains what kind of files are inside -->
- [ITM Enabling and Usage](/ITM_sendChar.c)  

## Purpose
<!-- Why this repo exists -->
This repository is intended as a quick reference and reusable set of building blocks for embedded development on STM MCUs.  
Each file is minimal and focused, making it easy to integrate into larger projects.  

## How to Use
<!-- Instructions for developers -->
1. Browse the `C` files inside the folder.  
2. Copy and paste the relevant snippet into your STM32 project.  
3. Adjust pin mappings, clock settings, and configuration as needed.  

- ITM Enabling and Usage
    1. Open syscalls.c.
    2. Copy the contents of ITM_sendChar.c into syscalls.c just after the includes:
      ```c
   
      #include <signal.h>
      #include <time.h>
      #include <sys/time.h>
      #include <sys/times.h>
      #include <sys/times.h>

      /* ITM (Instrumentation Trace Macrocell) Configuration Start */

      /* Define memory-mapped registers for ITM and Debug MCU */
      #define DBGMCU_CR           *((volatile uint32_t*)0xE0042004)  // Debug MCU Control Register
      #define ITM_LOCK_ACCESS     *((volatile uint32_t*)0xE0000FB0U) // ITM Lock Access Register
  
  3. Modify the _write function as follows: 
  ```c
  
  __attribute__((weak)) int _write(int file, char *ptr, int len)
  {
  (void)file;
  int DataIdx;
  ITM_enable(); /*1. Added ITM enable*/
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ///__io_putchar(*ptr++); /*2. Comment __io_putchar functioon call*/
	  ITM_sendChar(*ptr++);    /*3. Call ITM_sendChar function */
  }
  return len;
  }
  

## Notes
<!-- Extra guidance -->
- Code is tested on STM32 family MCUs but may require modifications for different series.  
- Organized for learning and quick prototyping, not full production projects.  

## License
<!-- Optional: you can add one if you want -->
MIT License (or your preferred license).  
