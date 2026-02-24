Zuerst zeige ich, wie Sie den EEPROM beschreiben bzw. auslesen. Der Raspberry Pi Pico RP2040 hat keinen integrierten EEPROM-Speicher, sondern nutzt dafür einen Teil des Flash-Speichers. Deshalb muss dieser Bereich zunächst festgelegt werden. Ausserdem ist es wichtig, dass man den Schreibvorgang mit 'EEPROM.commit()' abschließt.

Mit dem Quellcode wird also einmalig ein Pin in den Speicher geschrieben, den Sie später durch einen eigenen ersetzen. Immer wenn Sie den Pin ändern wollen, führen Sie diesen kurzen Sketch aus.
Nun zum Auslesen. Wichtig ist, dass der gleiche EEPROM Bereich wie beim Schreiben genutzt wird. Damit die Zuordnung der gelesenen Werte funktioniert, wird ein 'leerer' Pin definiert. Der Lesevorgang wird später in einen Sketch integriert, der mit einem einzugebenden Pin vergleicht und den Geek freischaltet bzw. sperrt. 

Im Sketch 'geek_tastatur_mit_shortcuts.ino' autorisieren Sie sich durch den vorher von Ihnen vergebenen sechstelligen Pin.
Danach stehen Ihnen mit Hilfe der 5 Analogtasten folgende Shortcuts zur verfügung:

Taste 1: Explorer öffnen 'WINDOWS + e',
Taste 2: Desktop anzeigen 'WINDOWS + d',
Taste 3: Fenster schließen 'ALT + F4',
Taste 4: Screenshot 'WINDOWS + SHIFT + s',
Taste 5: PC sperren 'WINDOWS + l',
