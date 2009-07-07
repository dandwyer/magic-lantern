ARM_PATH=/opt/local/bin
CC=$(ARM_PATH)/arm-elf-gcc-4.3.2
OBJCOPY=$(ARM_PATH)/arm-elf-objcopy
LD=$(CC)
HOST_CC=gcc
HOST_CFLAGS=-g -O3 -W -Wall
VERSION=0.1.5


# 5D memory map
# RESTARTSTART is selected to be just above the end of the bss
#
ROMBASEADDR		= 0xFF810000
RESTARTSTART		= 0x00048000


all: \
	5d2_dumper.fir \
	magiclantern.fir \

install: magiclantern.fir magiclantern.cfg
	cp $^ /Volumes/KINGSTON/
	hdiutil unmount /Volumes/KINGSTON/


zip: magiclantern-$(VERSION).zip

# zip.txt must be the first item on the list!
magiclantern-$(VERSION).zip: \
	zip.txt \
	magiclantern.fir \
	magiclantern.cfg \
	README \
	LICENSE \

	-rm $@
	zip -z $@ < $^


FLAGS=\
	-Wp,-MMD,.$@.d \
	-Wp,-MT,$@ \
	-nostdlib \
	-fomit-frame-pointer \
	-fno-strict-aliasing \
	-DRESTARTSTART=$(RESTARTSTART) \
	-DROMBASEADDR=$(ROMBASEADDR) \
	-DVERSION=\"$(VERSION)\" \

NOT_USED_FLAGS=\
	-march=armv5te \
	-mthumb \
	-mthumb-interwork \

CFLAGS=\
	$(FLAGS) \
	-O3 \
	-Wall \
	-W \


AFLAGS=\
	$(FLAGS) \


%.s: %.c
	$(call build,CC -S,$(CC) $(CFLAGS) -S -o $@ $<)
%.o: %.c
	$(call build,CC,$(CC) $(CFLAGS) -c -o $@ $<)
%.i: %.c
	$(call build,CPP,$(CC) $(CFLAGS) -E -c -o $@ $<)
%: %.c
	$(call build,LD,$(CC) $(CFLAGS) -o $@ $<)
%.o: %.S
	$(call build,AS,$(CC) $(AFLAGS) -c -o $@ $<)
%.bin: %
	$(call build,OBJCOPY,$(OBJCOPY) -O binary $< $@)

dumper: dumper_entry.o dumper.o
	$(call build,LD,$(LD) \
		-o $@ \
		-nostdlib \
		-mthumb-interwork \
		-march=armv5te \
		-e _start \
		$^ \
	)

dumper_entry.o: flasher-stubs.S

reboot.o: reboot.c magiclantern.bin
5d-hack.bin: 5d-hack

magiclantern.lds: magiclantern.lds.S
	$(call build,CPP,$(CPP) $(CFLAGS) $< | grep -v '^#' > $@)

# magiclantern.lds script MUST be first
# entry.o MUST be second
magiclantern: \
	magiclantern.lds \
	entry.o \
	5d-hack.o \
	gui.o \
	audio.o \
	lens.o \
	zebra.o \
	hotplug.o \
	config.o \
	menu.o \
	bmp.o \
	font-large.o \
	font-med.o \
	font-small.o \
	stubs-5d2.110.o \
	version.o \

	$(call build,LD,$(LD) \
		-o $@ \
		-N \
		-nostdlib \
		-mthumb-interwork \
		-march=armv5te \
		-T \
		$^ \
	)


# These do not need to be run.  Since bigtext is not
# a standard program, the output files are checked in.
font-large.in: generate-font
	$(call build,'GENFONT',./$< > $@ \
		'-*-helvetica-*-r-*-*-34-*-100-100-*-*-iso8859-*' \
		19 25 \
	)
font-med.in: generate-font
	$(call build,'GENFONT',./$< > $@ \
		'-*-helvetica-*-r-*-*-17-*-100-100-*-*-iso8859-*' \
		10 16 \
	)
font-small.in: generate-font
	$(call build,'GENFONT',./$< > $@ \
		'-*-helvetica-*-r-*-*-10-*-100-100-*-*-iso8859-*' \
		6 8 \
	)

font-large.c: font-large.in mkfont
	$(call build,MKFONT,./mkfont \
		< $< \
		> $@ \
		-width 28 \
		-height 32 \
		-name font_large \
	)

font-med.c: font-med.in mkfont
	$(call build,MKFONT,./mkfont \
		< $< \
		> $@ \
		-width 12 \
		-height 16 \
		-name font_med \
	)

font-small.c: font-small.in mkfont
	$(call build,MKFONT,./mkfont \
		< $< \
		> $@ \
		-width 8 \
		-height 12 \
		-name font_small \
	)

version.c: FORCE
	$(call build,VERSION,( \
		echo 'const char build_version[] = "$(VERSION)";' ; \
		echo 'const char build_id[] = "'`hg id`'";' ; \
		echo 'const char build_date[] ="'`date -u "+%Y-%m-%d %H:%M:%S"`'";' ; \
		echo 'const char build_user[] = "'`whoami`@`hostname`'";' ; \
	) > $@)

reboot: reboot.o
	$(call build,LD,$(LD) \
		-o $@ \
		-nostdlib \
		-mthumb-interwork \
		-march=armv5te \
		-e _start \
		-Ttext=0x800000 \
		$^ \
	)

%-stubs.S: %.map
	perl -ne > $@ < $< '\
		BEGIN { print "#define SYM(a,n) n=a; .global n;\n" } \
		s/[\r\n]//g; \
		s/^\s*0001:([0-9A-Fa-f]+)\s+([^\s]+)$$/SYM(0x\1,\2)\n/ \
			and print; \
	'


%.dis: %.bin
	$(ARM_PATH)/arm-linux-objdump \
		-b binary \
		-m arm \
		-D \
		$< \
	> $@

BASE=0xFF800000
#BASE=0
#BASE=0xFF000000

1.1.0/ROM0.elf: 1.1.0/ROM0.bin 1.1.0/ROM0.map
	./remake-elf \
		--base $(BASE) \
		--cc $(CC) \
		--relative \
		-o $@ \
		$^


strings: ROM0.bin
	strings -t x $^

ROM0.bin: FORCE
FORCE:


#
# Fetch the firmware archive from the Canon website
# and unpack it to generate the pristine firmware image.
#
eos5d2107.exe:
	wget http://web.canon.jp/imaging/eosd/firm-e/eos5dmk2/data/eos5d2107.exe

5d200107.fir: eos5d2107.exe
	-unzip -o $< $@
	touch $@

# Extract the flasher binary file from the firmware image
# and generate an ELF from it for analysis.

ifdef FETCH_FROM_CANON
%.1.flasher.bin: %.fir dissect_fw
	./dissect_fw $< . $(basename $<)
endif

flasher.elf: 5d200107.1.flasher.bin flasher.map
	./remake-elf \
		--cc $(CC) \
		--base 0x800120 \
		-o $@ \
		$^

dumper.elf: 5d2_dump.fir flasher.map
	./remake-elf \
		--cc $(CC) \
		--base 0x800000 \
		-o $@ \
		$^

#
# Generate a new firmware image suitable for dumping the ROM images
#
5d2_dumper.fir: dumper.bin 5d200107.1.flasher.bin
	./assemble_fw \
		--output $@ \
		--user $< \
		--offset 0x5ab8 \

magiclantern.fir: reboot.bin 5d200107.1.flasher.bin
	$(call build,ASSEMBLE,./assemble_fw \
		--output $@ \
		--user $< \
		--offset 0x120 \
		--zero \
	)

dummy_data_head.bin:
	perl -e 'print chr(0) x 24' > $@

#ROM0.bin: 5d200107.fir

# Use the dump_toolkit files
# deprectated; use the dumper.c program instead
5d2_dump.fir:
	-rm $@
	cat \
		5d200107.0.header.bin \
		5d200107.1.flasher.bin \
		dump_toolkit/repack/dummy_data_head.bin \
	> $@
	./patch-bin $@ < dump_toolkit/diffs/5d2_dump.diff


# Firmware manipulation tools
dissect_fw: dissect_fw.c
	$(HOST_CC) $(HOST_CFLAGS) -o $@ $<

# Quiet the build process
build = \
	@if [ "$V" == 1 ]; then \
		echo '$2'; \
	else \
		printf "[ %-8s ]   %s\n"  $1 $@; \
	fi; \
	$2


clean:
	-rm -f *.o *.a font-*.c

-include .*.o.d
