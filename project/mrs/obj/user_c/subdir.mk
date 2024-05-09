################################################################################
# MRS Version: 1.9.1
# ×Ô¶¯Éú³ÉµÄÎÄ¼þ¡£²»Òª±à¼­£¡
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
<<<<<<< HEAD
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/Encoder_c.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/Gyroscope_c.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/PID.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/cam.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/isr.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/main.c \
F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/yj901s.c 
=======
E:/PLA_smartcarrace_git/project/user/src/Encoder_c.c \
E:/PLA_smartcarrace_git/project/user/src/Gyroscope_c.c \
E:/PLA_smartcarrace_git/project/user/src/PID.c \
E:/PLA_smartcarrace_git/project/user/src/cam.c \
E:/PLA_smartcarrace_git/project/user/src/isr.c \
E:/PLA_smartcarrace_git/project/user/src/main.c \
E:/PLA_smartcarrace_git/project/user/src/yj901s.c 
>>>>>>> main

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
<<<<<<< HEAD
user_c/Encoder_c.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/Encoder_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/Gyroscope_c.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/Gyroscope_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/PID.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/cam.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/cam.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/yj901s.o: F:/·É¿¨ÖÇÄÜÊÓ¾õ/git_smartcar/PLA_smartcarrace_git/project/user/src/yj901s.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\Libraries\doc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_components" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Core" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Ld" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\sdk\Startup" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\user\inc" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_common" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_device" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\project\code" -I"F:\·É¿¨ÖÇÄÜÊÓ¾õ\git_smartcar\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
=======
user_c/Encoder_c.o: E:/PLA_smartcarrace_git/project/user/src/Encoder_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/Gyroscope_c.o: E:/PLA_smartcarrace_git/project/user/src/Gyroscope_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/PID.o: E:/PLA_smartcarrace_git/project/user/src/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/cam.o: E:/PLA_smartcarrace_git/project/user/src/cam.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: E:/PLA_smartcarrace_git/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: E:/PLA_smartcarrace_git/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/yj901s.o: E:/PLA_smartcarrace_git/project/user/src/yj901s.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\PLA_smartcarrace_git\Libraries\doc" -I"E:\PLA_smartcarrace_git\libraries\zf_components" -I"E:\PLA_smartcarrace_git\libraries\sdk\Core" -I"E:\PLA_smartcarrace_git\libraries\sdk\Ld" -I"E:\PLA_smartcarrace_git\libraries\sdk\Peripheral" -I"E:\PLA_smartcarrace_git\libraries\sdk\Startup" -I"E:\PLA_smartcarrace_git\project\user\inc" -I"E:\PLA_smartcarrace_git\libraries\zf_common" -I"E:\PLA_smartcarrace_git\libraries\zf_device" -I"E:\PLA_smartcarrace_git\project\code" -I"E:\PLA_smartcarrace_git\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
>>>>>>> main
	@	@

