################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c \
F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c 

OBJS += \
./zf_components/seekfree_assistant.o \
./zf_components/seekfree_assistant_interface.o 

C_DEPS += \
./zf_components/seekfree_assistant.d \
./zf_components/seekfree_assistant_interface.d 


# Each subdirectory must supply rules for building sources it contributes
zf_components/seekfree_assistant.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_components/seekfree_assistant_interface.o: F:/�ɿ������Ӿ�/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\�ɿ������Ӿ�\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

