################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/飞卡智能视觉/v5.0/project/user/src/Encoder_c.c \
F:/飞卡智能视觉/v5.0/project/user/src/Gyroscope_c.c \
F:/飞卡智能视觉/v5.0/project/user/src/PID.c \
F:/飞卡智能视觉/v5.0/project/user/src/cam.c \
F:/飞卡智能视觉/v5.0/project/user/src/isr.c \
F:/飞卡智能视觉/v5.0/project/user/src/main.c \
F:/飞卡智能视觉/v5.0/project/user/src/yj901s.c 

OBJS += \
./user_c/Encoder_c.o \
./user_c/Gyroscope_c.o \
./user_c/PID.o \
./user_c/cam.o \
./user_c/isr.o \
./user_c/main.o \
./user_c/yj901s.o 

C_DEPS += \
./user_c/Encoder_c.d \
./user_c/Gyroscope_c.d \
./user_c/PID.d \
./user_c/cam.d \
./user_c/isr.d \
./user_c/main.d \
./user_c/yj901s.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/Encoder_c.o: F:/飞卡智能视觉/v5.0/project/user/src/Encoder_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/Gyroscope_c.o: F:/飞卡智能视觉/v5.0/project/user/src/Gyroscope_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/PID.o: F:/飞卡智能视觉/v5.0/project/user/src/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/cam.o: F:/飞卡智能视觉/v5.0/project/user/src/cam.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: F:/飞卡智能视觉/v5.0/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: F:/飞卡智能视觉/v5.0/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/yj901s.o: F:/飞卡智能视觉/v5.0/project/user/src/yj901s.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

