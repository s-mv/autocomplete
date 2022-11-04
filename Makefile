TITLE = autocomplete

CC = clang
# hehe shortcut, don't try this at home kids
CFILES = src/*.c
INCLUDE = src/include
DEBUG = true

smv: test

test:
	@$(CC) $(CFILES) -I $(INCLUDE) -DDEBUG=$(DEBUG) -o $(TITLE)

new:
	@printf "#ifndef smv_$(TITLE)_$(name)_h\n#define smv_$(TITLE)_$(name)_h\n\n\n#endif" > src/include/$(name).h
	@printf "#include \"$(name).h\"" > src/$(name).c