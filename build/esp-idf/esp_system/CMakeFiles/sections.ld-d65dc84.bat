@echo off
cd /D C:\Users\tiago\OneDrive\Documentos\REPOSITORIOS\MCPWM-CLI\build\esp-idf\esp_system || (set FAIL_LINE=2& goto :ABORT)
E:\Espressif\Espressif\python_env\idf5.2_py3.11_env\Scripts\python.exe E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/tools/ldgen/ldgen.py --config C:/Users/tiago/OneDrive/Documentos/REPOSITORIOS/MCPWM-CLI/sdkconfig --fragments-list E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/xtensa/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_ringbuf/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_mm/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/gpio/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/gptimer/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/i2c/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/ledc/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/mcpwm/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/rmt/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/twai/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/driver/uart/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_pm/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/spi_flash/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_system/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_system/app.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_rom/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/hal/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/log/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/heap/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/soc/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_hw_support/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_hw_support/dma/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/freertos/linker_common.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/freertos/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/newlib/newlib.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/newlib/system_libs.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_common/common.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_common/soc.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/app_trace/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_event/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_phy/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/vfs/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/lwip/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_netif/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/wpa_supplicant/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_wifi/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_adc/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_eth/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_gdbstub/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_psram/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_lcd/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/espcoredump/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/ieee802154/linker.lf;E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/openthread/linker.lf --input E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/components/esp_system/ld/esp32s3/sections.ld.in --output C:/Users/tiago/OneDrive/Documentos/REPOSITORIOS/MCPWM-CLI/build/esp-idf/esp_system/ld/sections.ld --kconfig E:/Espressif/Espressif/frameworks/esp-idf-v5.2.1/Kconfig --env-file C:/Users/tiago/OneDrive/Documentos/REPOSITORIOS/MCPWM-CLI/build/config.env --libraries-file C:/Users/tiago/OneDrive/Documentos/REPOSITORIOS/MCPWM-CLI/build/ldgen_libraries --objdump E:/Espressif/Espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/bin/xtensa-esp32s3-elf-objdump.exe || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%