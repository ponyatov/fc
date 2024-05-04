# format
.PHONY: format
format: tmp/format_f
tmp/format_f: $(F)
	$(DOTNET) fantomas --force $? && touch $@

.PHONY: install
install: .config/dotnet-tools.json
	dotnet tool install fantomas
	dotnet tool update -v d \
		--ignore-failed-sources \
		--global Microsoft.dotnet-interactive \
		--add-source https://api.nuget.org/v3/index.json
.config/dotnet-tools.json:
	dotnet new  tool-manifest
