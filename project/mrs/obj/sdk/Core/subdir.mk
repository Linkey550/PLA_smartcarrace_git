################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/�ɿ������Ӿ�/v5.0/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: F:/�ɿ������Ӿ�/v5.0/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\v5.0\Libraries\doc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_components" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\v5.0\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\v5.0\project\user\inc" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_common" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_device" -I"F:\�ɿ������Ӿ�\v5.0\project\code" -I"F:\�ɿ������Ӿ�\v5.0\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

