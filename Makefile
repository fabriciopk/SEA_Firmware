
# Flashing
OCDFLAGS = -f openocd.cfg
BINDIR = .pioenvs/genericSTM32F103C8

OCD = openocd
RM = rm -rf

flash: $(BINDIR)/firmware.bin
	$(OCD) $(OCDFLAGS)

cleanBuild: clean

clean:
	$(RM) $(BINDIR)
	$(RM) $(OBJDIR)
