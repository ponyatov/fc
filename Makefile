# var
MODULE = $(notdir $(CURDIR))

# version
KAITAI_VER = 0.10

# dir
CWD   = $(CURDIR)
DISTR = $(HOME)/distr

# tool
CURL = curl -L -o

# package
KAITAI_DEB = kaitai-struct-compiler_$(KAITAI_VER)_all.deb

# src
F += $(wildcard lib/*.fs)

# all
.PHONY: all
all: $(F) $(MODULE).*proj
	dotnet build

.PHONY: test
test: $(F) $(MODULE).*proj
	dotnet test

# format
.PHONY: format
format: tmp/format_f
tmp/format_f: $(F)
	dotnet fantomas --force $? && touch $@

.PHONY: install
install: .config/dotnet-tools.json
	dotnet tool install fantomas
	dotnet tool update -v d \
		--ignore-failed-sources \
		--global Microsoft.dotnet-interactive \
		--add-source https://api.nuget.org/v3/index.json
.config/dotnet-tools.json:
	dotnet new  tool-manifest


.PHONY: kaitai
kaitai: $(DISTR)/SDK/$(KAITAI_DEB)
	sudo apt-get install $<

$(DISTR)/SDK/$(KAITAI_DEB):
	$(CURL) $@ https://github.com/kaitai-io/kaitai_struct_compiler/releases/download/0.10/$(KAITAI_DEB)
