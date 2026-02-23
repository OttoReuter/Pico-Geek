## Pico-Geek
# Waveshare RP2040-GEEK developmentboard with RP2040 Mikrocontroller

Das Waveshare RP2040-GEEK Entwicklungsboard basiert auf dem RP2040 Mikrocontroller, mit 1.14 Zoll 65K Farb-LCD, TF-Kartensteckplatz, USB-Debugging-Downloader, im weißen Kunststoffgehäuse. Darüber hinaus ist es ausgestattet mit einem USB-A-Interface. Es bietet verschiedene Firmware für SWD-Port, UART-Port und I2C-Port. An der vierpoligen I2C/ADC Buchse ist der GPIO 28 nach außen geführt. Was der Pico-Geek nicht besitzt, sind Tasten für direkte Eingaben. Damit könnte man z.B. einen Pin eingeben, um etwas freizuschalten o.ä.
Am Ende dieses Beitrags sollen Sie in der Lage sein, einen selbst gewählten sechsstelligen Pin in den EEPROM des Pico-Geek zu schreiben, der bei jeder Inbetriebnahme ausgelesen wird. Sie merken sich den, nur Ihnen bekannten Pin, und geben ihn auf Anforderung ein. Stimmt er mit dem abgespeicherten überein, dann wird eine 'Aktion' freigeschaltet.
