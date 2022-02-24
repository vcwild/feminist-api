# /* Pretty imports */

YELLOW := $(shell tput -Txterm setaf 3)
BLUE := $(shell tput -Txterm setaf 6)
RESET := $(shell tput -Txterm sgr0)


# /* Binary settings */

NAME ?= feminist_api


# /* Compilation args */

CFLAGS ?= -W -Wall -DMG_ENABLE_LINES=1
ifneq ($(MBEDTLS_DIR),)
CFLAGS += -DMG_ENABLE_MBEDTLS=1 -I$(MBEDTLS_DIR)/include -I/usr/include
CFLAGS += -L$(MBEDTLS_DIR)/lib -lmbedtls -lmbedcrypto -lmbedx509
else ifneq ($(OPENSSL_DIR),)
CFLAGS += -DMG_ENABLE_OPENSSL=1 -I$(OPENSSL_DIR)/include
CFLAGS += -L$(OPENSSL_DIR)/lib -lssl -lcrypto
endif


# /* Server settings */

ENDPOINT = http://localhost:8000
START_MSG = "$(YELLOW)-> Now running the \`$(NAME)\` live at 👉 $(BLUE)$(ENDPOINT)$(RESET)"

# /* Rules */

all: $(NAME)

run: $(NAME)
	@echo $(START_MSG)
	@$(DEBUGGER) ./$(NAME) $(ARGS)

$(NAME): main.c
	$(CC) ./libs/mongoose/mongoose.c -I./libs/mongoose $(CFLAGS) $(EFLAGS) -o $(NAME) main.c

clean:
	rm -rf $(NAME) *.o *.dSYM *.gcov *.gcno *.gcda *.obj *.exe *.ilk *.pdb

.PHONY: run clean all