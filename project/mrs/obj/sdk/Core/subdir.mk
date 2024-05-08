################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/飞卡智能视觉/v5.0/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: F:/飞卡智能视觉/v5.0/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\飞卡智能视觉\v5.0\Libraries\doc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_components" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Core" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Ld" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Peripheral" -I"F:\飞卡智能视觉\v5.0\libraries\sdk\Startup" -I"F:\飞卡智能视觉\v5.0\project\user\inc" -I"F:\飞卡智能视觉\v5.0\libraries\zf_common" -I"F:\飞卡智能视觉\v5.0\libraries\zf_device" -I"F:\飞卡智能视觉\v5.0\project\code" -I"F:\飞卡智能视觉\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

