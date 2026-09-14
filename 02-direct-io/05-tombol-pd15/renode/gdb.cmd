set pagination off
set confirm off
target remote localhost:3333
printf "\n== CPU registers (awal) ==\n"
info registers r0 r1 r2 r3 sp pc lr
printf "\n== RCC AHB1ENR @0x40023830 ==\n"
x/1xw 0x40023830
printf "== GPIOD MODER  @0x40020C00 ==\n"
x/1xw 0x40020C00
printf "== GPIOD ODR    @0x40020C14 ==\n"
x/1xw 0x40020C14
break main
continue
printf "\n== berhenti di main() ==\n"
info registers pc
x/1xw 0x40020C00
detach
quit
