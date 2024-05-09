################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
<<<<<<< HEAD
F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/sdk/Startup/startup_ch32v30x_D8C.S 
=======
E:/PLA_smartcarrace_git/libraries/sdk/Startup/startup_ch32v30x_D8C.S 
>>>>>>> main

OBJS += \
./sdk/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
<<<<<<< HEAD
sdk/Startup/startup_ch32v30x_D8C.o: F:/飞卡智能视觉/git_smartcar/PLA_smartcarrace_git/libraries/sdk/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\飞卡智能视觉\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
=======
sdk/Startup/startup_ch32v30x_D8C.o: E:/PLA_smartcarrace_git/libraries/sdk/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
>>>>>>> main
	@	@

