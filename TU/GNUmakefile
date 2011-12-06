tidy.tu: 

TIDY_SRC_DIR=$(HOME)/Projects/tidy

CFLAGS= -I$(TIDY_SRC_DIR)/include

%.tu: %.c
	$(CC) -fdump-translation-unit -o /dev/null -c $(CFLAGS) $< 

