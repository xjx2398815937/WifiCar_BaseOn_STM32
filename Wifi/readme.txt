��Files decriptions��

----------------------------HARDWARE INTERFACE------------------------------------------
- M8266WIFIHostIf.c -- example source of MCU inteface to M8266WIFI Module              -
- M8266WIFIHostIf.h -- example header of MCU inteface to M8266WIFI Module              -
Notes:                                                                                 -
  1. Hardware Layer fundamental control/query operations including GPIO/UART/SPI       -
     Operations                                                                        -
  2. Should be adjust according to the specific hardware logic                         -
----------------------------------------------------------------------------------------

----------------------------DRIVER------------------------------------------------------
- M8266WIFIDRV.lib  -- Driver.lib of MCU to perform SPI-WIFI transparent transception
��Ƭ�����������ʵ��SPI-wifi͸������
- M8266WIFIHostIf.h -- example header of MCU inteface to M8266WIFI Module
m8266wifiģ�鵥Ƭ���ӿ�ʵ��ͷ 
Notes:                                                                                 -
  1. Driver Layer operations mainly for High-Speed SPI-WIFI Operations,                -
     including High-Speed SPI-WIFI transparent transception, timing, hands-shaking etc 
	 �����������Ҫ���ڸ���spi-wifi��������������spi-wifi͸�����䡢��ʱ�����ֵȡ�-
  2. PLEASE DO NOT MODIFY THEM. Just embed them into your project work bentch
�벻Ҫ�޸����ǣ�ֻ�轫����Ƕ�뵽������Ŀ�����м���   -
----------------------------------------------------------------------------------------


----------------------------HAL OPERATIONS----------------------------------------------
- M8266WIFI_ops.c   -- example source of MCU HAL operations to M8266WIFI module
m8266wifiģ��ĵ�Ƭ��Hal����ʵ�� -
- M8266WIFI_ops.h   -- example header of MCU HAL operations to M8266WIFI module        -
Notes:                                                                                 -
  1. Hardare Abtraction Layer operations for MCU to config and communication with      -
     M8266WIFI module
��Ƭ����Ӳ�������������-m8266wifiģ������ú�ͨ�� 	 -
  2. You may please extend the operations following these example functions 
�밴������ʾ��������չ����   -
----------------------------------------------------------------------------------------

----------------------------APPLICATIONS__----------------------------------------------
- test_m8266wifi.c  -- example application source of test M8266WIFI module
ʾ��Ӧ�ó���Դ������M8266WiFiģ�� -
Notes:                                                                                 -
  1. example testing application to test speed of MCU-WIFI transparent transception 
��Ƭ������͸�������ٶȲ���Ӧ��ʵ��   -
  2. You may please modify or reference it for your own application
  ������Ϊ���Լ���Ӧ�ó����޸Ļ�������
----------------------------------------------------------------------------------------
 
��Architecture��

  ------------
 |APPLICATIONS|
  ------------
        \
         \
          \
       ----------------
      | HAL OPERATIONS |
       ----------------
             \
              \
               \
           ---------
          | DRIVER  |
           ---------
                 \
                  \
                   \
            --------------------
           | HARDWARE INTERFACE |
            --------------------

��Usage��
       
 1. Implement the sources of hardware interface according to your hardware design
��������Ӳ�����ʵ��Ӳ���ӿڵ���Դ
    Maily including 
     - GPIO initialization and operations for nCS and nRESER
	 NCS��nRESER��GPIO��ʼ���Ͳ���
     - SPI  initialization and read/write operations
	 SPI��ʼ���Ͷ�д����
     - UART initialization and read/write operations
	 UART��ʼ���Ͷ�д����
    You are recommended to uses the manner of macros following brd_cfg.h
����BRD_CFG.H֮��ʹ�ú�ķ�ʽ
 2. Add Driver Lib into your project
����������Lib��ӵ���Ŀ��
 3. Copy sources of HAL OPERATION to your project
��������Ŀִ��HAL�����Ķ��Դ
    If necessary, you may modify or extend your own HAL operations according to 
    AT commands and other related protocols 
�����Ҫ�����Ը���AT������������Э���޸Ļ���չ�Լ���HAL������
 4. Compose your applications referencing to APPLICATION SOURCE
��д����Ӧ�ó���Դ��Ӧ�ó���




AnyLinkin!
Link anytime, anywhere, and anyhow!
IoT@anylinkin.com
http://www.anylinkin.com
htpp://anylinkin.taobao.com
              