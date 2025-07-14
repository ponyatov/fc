# npm install -g yo generator-code ; yo code
$(NPM):
	sudo apt install -uy npm nodejs
$(TSC): $(NPM)
	npm install -g typescript
