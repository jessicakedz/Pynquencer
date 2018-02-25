# Pynquencer
A drum machine sample sequencer project on the Xilinx PYNQ board

It uses a KEDZIG Cool Button Keypad, two rotary encoders (connected to an Arduino Micro), and an oled 128x64 (connected to an arduino uno)

check out: https://www.youtube.com/watch?v=i4FZH2y2e4U

The Python notebook file is Pynquencer_final_mod_13Feb18.ipynb

Use ENCODER_Slave_read_only.ino on the Arduino Micro. 

Use OLED_SPI_Slave.ino on the Arduino Uno

The sound files are generated from wav files using:
* PDM_generator.m
* combine_files.m
which requires
* dec2twos.m
* https://github.com/kwikteam/npy-matlab/blob/master/readNPY.m

Example sound files are in the \output_npy folder

The keypad columns wires are on the low 4 bits of the Pynq Arduino and the row wires are on the bits 4-7. The backlight is controlled via SPI on the Arduino SPI port. 

Contributers on this project are:

* Jessica Kedziora: system design, hardware build, encoder and OLED spi interface, interface, Keypad design, ipython microblaze code, delta-sigma modulation in matlab, demo sequence. 

* David Pottinger: OLED display code, Python run and program loops, ipython microblaze GPIO code

* Shandon Campbell: Sound files, sound file conversion and assembly, misc taks on integreation, demo sequence.

Want cool buttons? 
WWW.KEDZIG.COM
