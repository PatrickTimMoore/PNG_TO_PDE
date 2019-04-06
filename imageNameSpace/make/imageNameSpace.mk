#
# This is a generic Makefile designed to compile a sample directory of code.
# This file depends on variables having been set before calling:
#   EXE: The name of the result file
#   OBJS: Array of objects files (.o) to be generated
#   CLEAN_RM: Optional list of additional files to delete on `make clean`
#
# @author Wade Fagen-Ulmschneider, <waf@illinois.edu>
# @author Jeffrey Tolar
#

# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
OBJS_DIR = .objs

# Add standard object files
OBJS += imageNameSpace/HSLAPixel.o imageNameSpace/PNG.o imageNameSpace/lodepng/lodepng.o

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

# Flags for compile:
CXXFLAGS += $(imageNameSpace) -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c

# Flags for linking:
LDFLAGS += $(imageNameSpace) -std=c++1y -stdlib=libc++

# Rule for `all` (first/default rule):
all: $(EXE)

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
# - `patsubst` function adds the directory name $(OBJS_DIR) before every object file
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
	$(LD) $^ $(LDFLAGS) -o $@

# Ensure .objs/ exists:
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/imageNameSpace
	@mkdir -p $(OBJS_DIR)/imageNameSpace/catch
	@mkdir -p $(OBJS_DIR)/imageNameSpace/lodepng

# Rules for compiling source code.
# - Every object file is required by $(EXE)
# - Generates the rule requiring the .cpp file of the same name
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Additional dependencies for object files are included in the clang++
# generated .d files (from $(DEPFILE_FLAGS)):
-include $(OBJS_DIR)/*.d
-include $(OBJS_DIR)/imageNameSpace/*.d
-include $(OBJS_DIR)/imageNameSpace/catch/*.d
-include $(OBJS_DIR)/imageNameSpace/lodepng/*.d


# Standard C++ Makefile rules:
clean:
	rm -rf $(EXE) $(OBJS_DIR) $(CLEAN_RM) *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean
