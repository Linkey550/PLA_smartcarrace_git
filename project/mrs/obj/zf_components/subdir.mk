################################################################################
# MRS Version: 1.9.1
# ×Ô¶¯Éú³ÉµÄÎÄ¼þ¡£²»Òª±à¼­£¡
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
<<<<<<< HEAD
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c 
=======
E:/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c \
E:/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c 
>>>>>>> main

OBJS += \
./zf_components/seekfree_assistant.o \
./zf_components/seekfree_assistant_interface.o 

C_DEPS += \
./zf_components/seekfree_assistant.d \
./zf_components/seekfree_assistant_interface.d 


# Each subdirectory must supply rules for building sources it contributes
<<<<<<< HEAD
zf_components/seekfree_assistant.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_components/seekfree_assistant_interface.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
=======
zf_components/seekfree_assistant.o: E:/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_components/seekfree_assistant_interface.o: E:/PLA_smartcarrace_git/libraries/zf_components/seekfree_assistant_interface.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
>>>>>>> main
	@	@

