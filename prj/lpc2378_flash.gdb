target remote localhost:3333
show remotetimeout
set remotetimeout 180
monitor reset run_and_halt
monitor sleep 500
monitor poll
monitor flash probe 0
monitor flash erase_sector 0 0 26
monitor reset run_and_halt
monitor sleep 500
monitor poll
monitor flash write_image erase C:\UWScratch\HelloWorld\LPC2378HelloW.hex 0 ihex
monitor soft_reset_halt
monitor arm7_9 force_hw_bkpts enable
set language c
break main
set remotetimeout 10
continue