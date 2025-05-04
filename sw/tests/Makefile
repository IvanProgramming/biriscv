
include ../common/Makefile.common

EXE      = .elf
SRC      = main.c addi.S and.S sub.S simple.S or.S
CFLAGS  += -L../common
LDFLAGS += -T ../common/$(LINKSCR)
TARGET   = tests
OUTPUT   = $(TARGET)$(EXE)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC) $(LDFLAGS)
	$(OBJDUMP) -d $(OUTPUT) > $(TARGET).dis
	$(READELF) -a $(OUTPUT) > $(TARGET).symbol

clean:
	$(RM) *.o $(OUTPUT) $(TARGET).dis $(TARGET).symbol

run:
	@echo "Running $(TARGET)..."
	../../tb/tb_top/build/test.x --elf $(OUTPUT)