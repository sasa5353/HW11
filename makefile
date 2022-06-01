project:=prog
dirNamePostfix:=Dir
dir:=$(project)$(dirNamePostfix)
CC:=g++
ext:=*.cpp
opt:=-O0
dirs = $(wilcard ./$(dir) ./$(dir)/quad)
files:=$(shell find $(dirs) -name $(ext))
obj:=$(patsubst $(ext), %.o, $(files))
run: $(project)
	@./$(project) 0
	@echo "LeftShoot done!"
	@./$(project) 1
	@echo "RightShoot done!"
	@./$(project) 2
	@echo "All done!"
$(project): $(obj)
	@$(CC) $(opt) $^ -o $@
%.o : %.cpp
	@$(CC) -c $(opt) $<
clean:
	@rm -f *.o
clear: clean
	rm -f $(project)
delete: clear
	@rm -f *.dat
parralel: $(project)
	@./$(project) 0&
	@./$(project) 1&
	@./$(project) 2
	@echo "All done!"
