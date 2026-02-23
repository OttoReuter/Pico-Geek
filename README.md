# Pico-Geek
## Waveshare RP2040-GEEK development board with RP2040 Mikrocontroller

![geek_050](https://github.com/user-attachments/assets/0098c464-c5df-4417-907b-5dc661d3a6c0)

Das Waveshare RP2040-GEEK Entwicklungsboard basiert auf dem RP2040 Mikrocontroller, mit 1.14 Zoll 65K Farb-LCD, TF-Kartensteckplatz, USB-Debugging-Downloader, im weißen Kunststoffgehäuse. Darüber hinaus ist es ausgestattet mit einem USB-A-Interface. Es bietet verschiedene Firmware für SWD-Port, UART-Port und I2C-Port. An der vierpoligen I2C/ADC Buchse ist z.B. der GPIO 28 nach außen geführt. Was der Pico-Geek nicht besitzt, sind Tasten für direkte Eingaben. Damit könnte man z.B. einen Pin eingeben, um etwas freizuschalten o.ä.
Ich zeige, wie Sie mit einer analogen Tastatur (5 Tasten) über eine Widerstandsleiter den Pico-Geek entsprechend erweitern.
Am Ende dieses Beitrags sollen Sie in der Lage sein, einen von Ihnen gewählten sechsstelligen Pin in den EEPROM des Pico-Geek zu schreiben, der bei jeder Inbetriebnahme ausgelesen wird. Damit autorisieren Sie sich für die Anwendung.
Als 'Aktion' für die Tasten werden Windows-Shortcuts festgelegt, die Sie per HID senden.
