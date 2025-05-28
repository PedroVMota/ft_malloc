

# Check HOSTTYPE environment variable
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Project configuration
NAME = libft_malloc
TARGET = $(NAME)_$(HOSTTYPE).so
SYMLINK = $(NAME).so
CC = gcc

# Directories
SRCDIR = Source
OBJDIR = Obj
LIBDIR = .

# Find all .c files recursively in Source directory
SOURCES = $(shell find $(SRCDIR) -name '*.c' -type f)

# Generate object file paths (preserving directory structure)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Generate dependency file paths
DEPS = $(OBJECTS:.o=.d)

# Compiler flags for shared library
CFLAGS_COMMON = -Wall -Wextra -std=c99 -fPIC -MMD -MP
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2 -DNDEBUG

# Linker flags for shared library
LDFLAGS = -shared

# Default build is debug
BUILD_TYPE ?= debug

# Set flags based on build type
ifeq ($(BUILD_TYPE),release)
    CFLAGS = $(CFLAGS_RELEASE)
else
    CFLAGS = $(CFLAGS_DEBUG)
endif

# Default target
.PHONY: all debug release clean fclean re help show-config

all: debug

debug:
	$(MAKE) BUILD_TYPE=debug $(TARGET)

release:
	$(MAKE) BUILD_TYPE=release $(TARGET)

# Main target - shared library
$(TARGET): $(OBJECTS) | $(LIBDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@if [ -L $(SYMLINK) ]; then rm -f $(SYMLINK); fi
	@ln -sf $(TARGET) $(SYMLINK)
	@echo "Built $(TARGET) successfully"
	@echo "Created symbolic link: $(SYMLINK) -> $(TARGET)"

# Pattern rule for object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./Source/ -c $< -o $@

# Create directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBDIR):
	@mkdir -p $(LIBDIR)

# Include dependency files
-include $(DEPS)

# Clean targets
clean:
	rm -rf $(OBJDIR)
	@echo "Cleaned object files and dependencies"

fclean: clean
	rm -f $(NAME)_*.so $(SYMLINK)
	@echo "Cleaned library files and symbolic links"

re: fclean all

# Configuration display
show-config:
	@echo "Build Configuration:"
	@echo "  HOSTTYPE: $(HOSTTYPE)"
	@echo "  TARGET: $(TARGET)"
	@echo "  SYMLINK: $(SYMLINK)"
	@echo "  BUILD_TYPE: $(BUILD_TYPE)"
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(CFLAGS)"
	@echo "  LDFLAGS: $(LDFLAGS)"
	@echo ""
	@echo "Detected source files:"
	@echo "$(SOURCES)" | tr ' ' '\n'

# Help target
help:
	@echo "libft_malloc Makefile"
	@echo "===================="
	@echo ""
	@echo "Available targets:"
	@echo "  all (default) - Build debug version of shared library"
	@echo "  debug         - Build debug version with DEBUG defined"
	@echo "  release       - Build release version with optimizations"
	@echo "  clean         - Remove object files and dependencies"
	@echo "  fclean        - Remove all build files including libraries"
	@echo "  re            - Clean and rebuild (fclean + all)"
	@echo "  show-config   - Display build configuration and detected files"
	@echo "  help          - Show this help message"
	@echo ""
	@echo "Current configuration:"
	@echo "  HOSTTYPE: $(HOSTTYPE)"
	@echo "  Target library: $(TARGET)"
	@echo "  Symbolic link: $(SYMLINK)"
	@echo ""
	@echo "Debug flags: $(CFLAGS_DEBUG)"
	@echo "Release flags: $(CFLAGS_RELEASE)"

# Test target to verify the library is working
test: $(TARGET)
	@echo "Testing library creation..."
	@ls -la $(TARGET) $(SYMLINK)
	@echo "Library built successfully!"

# Install target (optional)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/lib/"
	@sudo cp $(TARGET) /usr/local/lib/
	@sudo ln -sf /usr/local/lib/$(TARGET) /usr/local/lib/$(SYMLINK)
	@echo "Installation complete"


run: 
	cc libft_malloc_arm64_Darwin.so main.c && ./a.out 71
