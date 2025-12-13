CC = gcc
# -Iinclude позволяет писать #include "first.h" вместо "../include/first.h", 
# но ваши текущие пути тоже будут работать.
CFLAGS = -Wall -O2 -Iinclude 

# Папки
SRCDIR = src
OBJDIR = build
BINDIR = bin

# Целевой файл (исполняемый)
TARGET = $(BINDIR)/AlgLabs

# Находим все .c файлы в папке src
SRCS = $(wildcard $(SRCDIR)/*.c)
# Создаем список объектных файлов: src/file.c -> build/file.o
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Главная цель
all: directories $(TARGET)

# Линковка (сборка всех .o файлов в одну программу)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Компиляция каждого .c файла в .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Создание папок build и bin, если их нет
directories:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean directories
