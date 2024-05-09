################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_adc.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_delay.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_dvp.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_encoder.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_exti.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_flash.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_gpio.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_iic.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_pit.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_pwm.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_soft_iic.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_soft_spi.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_spi.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_timer.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_uart.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_usb_cdc.c 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_iic.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_soft_spi.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_iic.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_soft_spi.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

