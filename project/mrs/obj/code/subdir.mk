################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/网页下载/CHV307_Library-master/Seekfree_CH32V307VCT6_Opensource_Library/project/code/class.c 

OBJS += \
./code/class.o 

C_DEPS += \
./code/class.d 


# Each subdirectory must supply rules for building sources it contributes
code/class.o: D:/网页下载/CHV307_Library-master/Seekfree_CH32V307VCT6_Opensource_Library/project/code/class.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\Libraries\doc" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_components" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Core" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Ld" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Peripheral" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Startup" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\project\user\inc" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_common" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_device" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"D:\网页下载\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

