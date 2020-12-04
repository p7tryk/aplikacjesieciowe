#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 6// Rozmiar bufora
typedef struct
{
  int type; // Typ komunikatu
  char text[SIZE]; // Tekst komunikatu
} msg_tp;

#define STEPS 6 // Liczba krokow

int main(int argc, char *argv[])
{
  int stat, pid;
  msg_tp *buf;
  char name[16];
  int fd; // Deskryptor segmentu
  strcpy(name, "Bufor1");
  // Allokacja pamieci dzielonej na bufor -------------
  // Utworzenie segmentu pamieci ---------------------
  if ((fd = shm_open(name, O_RDWR | O_CREAT, 0664)) == -1)
    {
      printf("Blad otwarcia obszaru pamieci\n");
      exit(-1);
    }
  // Okreslenie rozmiaru obszaru pamieci ---------------
  if (ftruncate(fd, sizeof(msg_tp)) < 0)
    {
      printf("Blad ustawienia obszaru pamieci\n");
      exit(-1);
    }
  // if (ftruncate(fd, B_SIZE, SEEK_SET) != B_SIZE) exit(-1);
  // Odwzorowanie segmentu fd w obszar pamieci procesow
  buf = (msg_tp *) mmap(0, sizeof(msg_tp), PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
  if (buf == NULL) exit(-1);
  // Proces potomny P2 - pisze do pamieci wspolnej -----
  if (fork() == 0)
    {
      buf->type = 10;
      sprintf(buf->text, "Proces 1 komunikat %d", 1);
      exit(0);
    }
  else
    {
      // Proces mac5ierzysty P1 – czyta z pamięci wspólnej -
      printf("%d:%s", buf->type, buf->text);
      fflush(stdout);
      sleep(1);

    }
  pid = wait(&stat);
  printf("%d:%s", buf->type, buf->text);
  // Zwolnienie nazwy -----
  shm_unlink(name);
  return 0;
}
