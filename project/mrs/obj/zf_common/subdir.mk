################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_clock.c \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_debug.c \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_fifo.c \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_font.c \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_function.c \
F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_interrupt.c 

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
zf_common/zf_common_clock.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: F:/�ɿ������Ӿ�/v5.0/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

