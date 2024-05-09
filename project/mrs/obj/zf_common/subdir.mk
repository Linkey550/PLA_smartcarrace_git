################################################################################
# MRS Version: 1.9.1
# ×Ô¶¯Éú³ÉµÄÎÄ¼þ¡£²»Òª±à¼­£¡
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
<<<<<<< HEAD
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c 
=======
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c \
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c \
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c \
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c \
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c \
E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c 
>>>>>>> main

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
<<<<<<< HEAD
zf_common/zf_common_clock.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
=======
zf_common/zf_common_clock.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: E:/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
>>>>>>> main
	@	@

