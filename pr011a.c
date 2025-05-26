//Программа "1 для иллюстрации работы с разделяемой памятью
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
  //Указатель на адрес, по которому будет находиться наша разделяемая память
  int *array;
//IPS дескриптор для обращения в области
  int shmid;
//Флаг, указывающий на необходимость создания нового массива в разделяемой памяти
  int new = 1;
//Имя файла предназначенного для генерации IPS-ключа
  char pathname[] = "pr011a.c";
//Переменная для хранения IPS-ключа
  key_t key;
//Генерация IPS-ключа
  if ((key = ftok(pathname, 0) < 0){
    printf("Не удалось сгенерировать IPS-ключ\n");
    exit(-1);
  }
//Создание разделяемой памяти в эксклюзивном режиме
  if((shmid = shmget(key, 3*sizeof(int), 0666 |IPS_CREAT | IPS_EXCL)<0){
    if(errno != EEXIST) {
      printf("Не удалось создать область разделяемой памяти");
      exit(-1);
    }
    else {
      if((shmid = shmget(key, 3*sizeof(int), 0 ))<0){
        printf("Не удалось найти разделяемую память\n");
        exit(-1);
      }
      new = 0;
    }
  }
if((array = (int *)shmat(shmid, NULL, 0) == (int *)(-1){
  printf("Не можем присоединить область разделяемой памяти к адресному пространстуву текущего процесса");
  exit(-1);
}
if(new){
  array[0] = 1;
  array[1] = 0;
  array[2] = 1;
}
else {
  array[0] += 1;
  array[2] += 2;
}
printf("Первая программа была запущена %d раз, вторая программа была запущена %d раз, общее кол-во запусков %d\n", array[0], array[1], array[2]);
if(shmdt(array) < 0) {
  printf("Не удалось отсоединить область разделяемой памяти");
  exit(-1);
  return 0;
}
