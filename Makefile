
all:
	@$(MAKE) -C sml
	@$(MAKE) -C examples

.PHONY: clean
clean :
	@$(MAKE) -C sml clean
	@$(MAKE) -C examples clean

