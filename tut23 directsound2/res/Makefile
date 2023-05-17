TXTFILES	= $(wildcard *.txt)
BINFILES	= $(wildcard *.bin)
BMPFILES	= $(wildcard *.bmp)
PNGFILES	= $(wildcard *.png)
WAVFILES	= $(wildcard *.wav)
MODFILES	= $(wildcard *.mod)
HFILES	= $(wildcard *.h)

SFILES	= \
	$(TXTFILES:.txt=.s) \
	$(BINFILES:.bin=.s) \
	$(BMPFILES:.bmp=.s) \
	$(PNGFILES:.png=.s) \
	soundbank.s

#=============================================================================
all: $(SFILES);

clean:
	rm -f $(SFILES) $(HFILES) soundbank.bin

.SUFFIXES: .S .s .c .o .a .d .bmp .png .txt .bin .wav .mod

%.s: %.txt
	@echo \# converting $<
	@bin2s $< > $@

%.s: %.bin
	@echo \# converting $<
	@bin2s $< > $@

%.s: %.bmp
	@echo \# converting $<
	@grit $< -ff$*.grit

%.s: %.png
	@echo \# converting $<
	@grit $< -ff$*.grit

soundbank.s : $(WAVFILES) $(MODFILES)
	@echo \# converting $(WAVFILES) $(MODFILES)
	@mmutil $^ -osoundbank.bin -hsoundbank.h
	@bin2s soundbank.bin > $@

