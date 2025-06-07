CC := cc
TARGET = myprogram
CFLAGS_BASE = -Wall -Wextra -Werror 
CFLAGS_DEBUG = $(CFLAGS_BASE) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_BASE) -O2 -DNDEBUG

INC := -I./Lib/

SRCDIR = Source
OBJDIR = Obj
SOURCES = $(shell find $(SRCDIR) -name '*.c' -type f)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJECTS:.o=.d)


# LDFLAGS = -lft_malloc_arm64_Darwin

BUILD_TYPE ?= debug

ifeq ($(BUILD_TYPE),release)
    CFLAGS = $(CFLAGS_RELEASE)
else
    CFLAGS = $(CFLAGS_DEBUG)
endif

.PHONY: all debug release clean fclean re MLIB



ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


all: debug
	@echo ""
	@echo ""
	@echo "====== EXECUTION ===== "
	./$(TARGET)

MLIB: 
	$(MAKE) -C Lib/malloc


debug: MLIB $(TARGET)

release: MLIB $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L./Lib/malloc -lft_malloc_$(HOSTTYPE) -Wl,-rpath,./Lib/malloc -o $@

# Pattern rule for object files with dependency generation
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  $(INC)  -MMD -MP -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	@echo "Cleaned object files and dependencies"

fclean: clean
	$(MAKE) fclean -C Lib/malloc
	rm -f $(TARGET)
	@echo "Cleaned executable"

re: fclean all

# Include dependency files
-include $(DEPS)
