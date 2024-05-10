################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/Encoder_c.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/Gyroscope_c.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/PID.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/cam.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/isr.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/main.c \
C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/yj901s.c 

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
user_c/Encoder_c.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/Encoder_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/Gyroscope_c.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/Gyroscope_c.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/PID.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/cam.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/cam.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/isr.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/yj901s.o: C:/Users/user/Desktop/新建文件夹/PLA_smartcarrace_git_o.5/project/user/src/yj901s.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\Libraries\doc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_components" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Core" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Ld" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Peripheral" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\sdk\Startup" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\user\inc" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_common" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_device" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\project\code" -I"C:\Users\user\Desktop\新建文件夹\PLA_smartcarrace_git_o.5\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

