################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/��ҳ����/CHV307_Library-master/Seekfree_CH32V307VCT6_Opensource_Library/project/code/class.c 

OBJS += \
./code/class.o 

C_DEPS += \
./code/class.d 


# Each subdirectory must supply rules for building sources it contributes
code/class.o: D:/��ҳ����/CHV307_Library-master/Seekfree_CH32V307VCT6_Opensource_Library/project/code/class.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\Libraries\doc" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_components" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Core" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Ld" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Peripheral" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Startup" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\project\user\inc" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_common" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_device" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"D:\��ҳ����\CHV307_Library-master\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

