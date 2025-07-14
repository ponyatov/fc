.PHONY : install update ref gz
install: $(WS)_install doc ref gz
	$(MAKE) update
update : $(WS)_update
	$(RUSTUP) self update && $(RUSTUP) update
	$(PIP) install -U -r requirements.txt
	$(NPM) update
ref    : $(RF)
gz     : $(GZ)

Debian_install:
# sudo dpkg --add-architecture i386
Debian_update:
	sudo apt update
	sudo apt install -uy `cat apt.$(WS)` $(APT)
