include ../makefile_commun.txt

# Name of our project
# (use a single word, e.g. 'myproject')
PROJECTNAME= libjohncena

# Source files
# List C/C++/Assembly source files:
# (list all files to compile, e.g. 'a.c b.cpp as.S'):
# Use .cc, .cpp or .C suffix for C++ files, use .S
# (NOT .s !!!) for assembly source code files.
PRJSRC=can.cpp ControleDel.cpp controleMoteur.cpp bouton.cpp controleTemps.cpp PWM.cpp Memoire.cpp memoire_24.cpp

# additional includes (e.g. -I/path/to/mydir)
INC= 

# libraries to link in (e.g. -lmylib)
LIBS=

# linker
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

LCA=-rcs

##### automatic target names ####
TRG=$(PROJECTNAME).a
DUMPTRG=$(PROJECTNAME).s
disasm: $(DUMPTRG) stats

$(TRG): $(OBJDEPS)
	$(CA) crs $(TRG) $(OBJDEPS) \

stats: $(TRG)
	$(OBJDUMP) -h $(TRG)
	$(SIZE) $(TRG)

$(DUMPTRG): $(TRG)
	$(OBJDUMP) -S  $< > $@


hex: $(HEXROMTRG)


writeflash: hex
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	 -p $(MCU) -P $(AVRDUDE_PORT) -e        \
	 -U flash:w:$(HEXROMTRG)

install: writeflash

# Make targets:
# all, disasm, stats, hex, writeflash/install, clean
all: $(TRG)

#####  Generating a gdb initialisation file    #####
##### Use by launching simulavr and avr-gdb:   #####
#####   avr-gdb -x gdbinit-myproject           #####
gdbinit: $(GDBINITFILE)

$(GDBINITFILE): $(TRG)
#	@echo "file $(TRG)" > $(GDBINITFILE)

	@echo "target remote localhost:1212" \
		                >> $(GDBINITFILE)

	@echo "load"        >> $(GDBINITFILE)
	@echo "break main"  >> $(GDBINITFILE)
	@echo "continue"    >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"
#### Cleanup ####
clean:
	$(REMOVE) $(TRG).a
	$(REMOVE) $(TRG) $(TRG).map $(DUMPTRG)	
	$(REMOVE) $(OBJDEPS)
	$(REMOVE) $(LST) $(GDBINITFILE)
	$(REMOVE) $(GENASMFILES)
	$(REMOVE) $(HEXTRG)



#####                    EOF                   #####

