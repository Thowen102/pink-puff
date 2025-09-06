include $(DEVKITPRO)/pvsneslib/mkfiles/snes_rules
PROJ     := pink_puff_adv
SOURCES  := source
INCLUDES := source data
DATA     := data
GRAPHICS := gfx
OBJS := \
	source/main.o \
	source/player.o \
	source/level.o \
	source/hud.o \
	source/title.o

all: $(PROJ).sfc

$(PROJ).sfc: $(OBJS)
	$(LINK) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) -f $(OBJS) $(PROJ).sfc
