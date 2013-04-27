target remote localhost:3333
symbol-file LPC2378HelloW.elf
monitor poll on

define syms
    symbol-file LPC2378HelloW.elf
end

define flash
    #monitor soft_reset_halt
    #monitor reset init
    #monitor halt
    monitor reset halt
    #monitor adapter_khz 333
    #monitor flash write_image LPC2378HelloW.elf
    monitor flash write_image erase unlock LPC2378HelloW.bin 0x0 bin
    #monitor flash write_image LPC2378HelloW.bin 0x0 bin
    #monitor verify_image LPC2378HelloW.bin 0x0 bin
    symbol-file LPC2378HelloW.elf
    monitor reset init
    #monitor adapter_khz 6000
end

define reboot
    monitor reset init
    continue
end

define flashboot
    #monitor at91sam7 gpnvm 2 set
end

document flash
flash: write LPC2378HelloW.elf and reset the processor
end
