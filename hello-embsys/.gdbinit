target remote localhost:3333
symbol-file build/app.elf
monitor poll on

define syms
    symbol-file build/app.elf
end

define flash
    #monitor soft_reset_halt
    #monitor reset init
    #monitor halt
    monitor reset halt
    #monitor adapter_khz 333
    #monitor flash write_image build/app.elf
    monitor flash write_image erase unlock build/app.bin 0x0 bin
    #monitor flash write_image build/app.bin 0x0 bin
    #monitor verify_image build/app.bin 0x0 bin
    symbol-file build/app.elf
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
flash: write build/app.elf and reset the processor
end
