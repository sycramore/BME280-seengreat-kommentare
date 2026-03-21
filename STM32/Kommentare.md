## Erste Uebersicht

* Was liegt in all diesen Ordnern und wer erzeugt so etwas Großes fuer die Anbindung eines Sensors an einen Mikrocontroller?
* Was davon braucht man wirklich und was davon sind Dateien, die eine IDE erzeugt hat?

## OBJ

* diverse Dateien, die die Github-Browser-Oberflaeche nicht anzeigt. Vermutlich Konfigurationsdateien oder Ausgabedateien einer IDE?

## STM32F10x_FWLib

* zwei Ordner
    * inc
    * src
 
* Beide Ordner enthalten C-Code. Sauber getrennt nach Header-Dateien, .h in inc und .c in src. Variablendefinitionen von dem Code zu trennen, kenne ich aus Libraries, die VHDL um diverse Funktionen ergaenzen. Scheint good practice zu sein?
* Datum in dem Header-Kommentar von Misc - 2011, Copyright STMicroelectronics. Vermutlich Code des Herstellers des STM32 und zu alt, um fuer den Sensor relevant zu sein. Vermutlich Firmware fuer einen bestimmten STM32-Mikrocontroller?

## HARDWARE

* Unterordner BME280 enthaelt 3 Dateien aus der offiziellen Library fuer den BME280 von Bosch.
* Dateien fuer eigene Version kopieren oder die offizielle Library von Bosch als Fork in eigene Version integrieren?


