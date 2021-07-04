CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
SRC_PATH = src
TYPES_PATH = $(SRC_PATH)/types
OBJS = main.o frontier.o map.o segment.o
 
# regra default (primeira regra)
all: build
 
# regras de ligacao
build: $(OBJS)
 
# regras de compilação
main.o: $(SRC_PATH)/main.c $(TYPES_PATH)/map.h 
map.o: $(TYPES_PATH)/map.c $(TYPES_PATH)/map.h $(TYPES_PATH)/segment.h
segment.o: $(TYPES_PATH)/segment.c $(TYPES_PATH)/segment.h $(TYPES_PATH)/frontier.h
frontier.o: $(TYPES_PATH)/frontier.c $(TYPES_PATH)/frontier.h $(TYPES_PATH)/segment.h 
 
# remove arquivos temporários
clean:
	-rm -f $(OBJS) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f build