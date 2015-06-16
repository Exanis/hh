BUILD_DIR=	build
BUILD_DIR_SHARED=	$(BUILD_DIR)/shared
BUILD_DIR_STATIC=	$(BUILD_DIR)/static
BUILD_DIR_TEST=		$(BUILD_DIR)/tests
NAME=	objects
NAME_SHARED=	$(BUILD_DIR_SHARED)/lib$(NAME).so
NAME_STATIC=	$(BUILD_DIR_STATIC)/lib$(NAME).a

SRC=	$(wildcard core/*.c)
OBJ=	$(SRC:.c=.o)

LIBS=	$(wildcard libs/*)

TEST_SRC=	$(wildcard tests/*.c)
TEST_OBJ=	$(TEST_SRC:.c=.o)
TEST_NAME=	tests_
TEST_NAME_STATIC=	$(BUILD_DIR_TEST)/$(TEST_NAME)static
TEST_NAME_SHARED=	$(BUILD_DIR_TEST)/$(TEST_NAME)shared

CFLAGS+=	-fplan9-extensions -O2 -Iheaders

$(NAME_STATIC): $(OBJ) $(BUILD_DIR_STATIC)
	@echo "[LD] Linking " $@
	@ar rc $(NAME_STATIC) $(OBJ)
	@ranlib $(NAME_STATIC)

$(NAME_SHARED): CFLAGS+= -fPIC -Wl,-export-dynamic
$(NAME_SHARED):	$(OBJ) $(BUILD_DIR_SHARED)
	@echo "[LD] Linking " $@
	@$(CC) $(OBJ) $(LDFLAGS) -shared -o $(NAME_SHARED)

$(BUILD_DIR_SHARED):
	@mkdir -p $(BUILD_DIR_SHARED)

$(BUILD_DIR_STATIC):
	@mkdir -p $(BUILD_DIR_STATIC)

$(BUILD_DIR_TEST):
	@mkdir -p $(BUILD_DIR_TEST)

all:	$(NAME_STATIC) $(NAME_SHARED)

clean:
	@rm -rf $(OBJ) $(TEST_OBJ)

fclean:	clean
	@rm -rf $(BUILD_DIR)

static: $(NAME_STATIC)

shared: $(NAME_SHARED)

tests:	CFLAGS+= -ggdb
tests:
	@$(MAKE) clean
	@env CFLAGS=-ggdb $(MAKE) static
	@$(MAKE) $(TEST_NAME_STATIC)
	@$(MAKE) clean
	@env CFLAGS=-ggdb $(MAKE) shared
	@$(MAKE) $(TEST_NAME_SHARED)
	@echo "[[===== STATIC TEST =====]]"
	@./$(TEST_NAME_STATIC)
	@echo "[[===== SHARED TEST =====]]"
	@env LD_LIBRARY_PATH=$(BUILD_DIR_SHARED) ./$(TEST_NAME_SHARED)

$(TEST_NAME_STATIC):	CFLAGS+= -ggdb
$(TEST_NAME_STATIC):	LDFLAGS+= -l$(NAME)
$(TEST_NAME_STATIC):	$(BUILD_DIR_TEST) $(TEST_OBJ)
	@echo "[LD] Linking " $@
	@$(CC) $(TEST_OBJ) $(LDFLAGS) -L$(BUILD_DIR_STATIC) -o $(TEST_NAME_STATIC)

$(TEST_NAME_SHARED):	CFLAGS+= -ggdb
$(TEST_NAME_SHARED):	LDFLAGS+= -l$(NAME)
$(TEST_NAME_SHARED):	$(BUILD_DIR_TEST) $(TEST_OBJ)
	@echo "[LD] Linking " $@
	@$(CC) $(TEST_OBJ) $(LDFLAGS) -L$(BUILD_DIR_SHARED) -o $(TEST_NAME_SHARED)

%.o:%.c
	@echo "[CC] " $@
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean tests static shared