################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c \
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c 

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
zf_common/zf_common_clock.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

