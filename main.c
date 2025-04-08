#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SURAS 100
#define MAX_NAME 50
#define FILENAME "suralar.txt"

typedef struct
{
      char name[MAX_NAME];
      int ayat_count;
} Sura;

int load_data(Sura *suras)
{
      FILE *file = fopen(FILENAME, "r");
      int count = 0;

      if (file == NULL)
      {
            return 0;
      }

      while (count < MAX_SURAS && fscanf(file, "%49[^:]:%d\n", suras[count].name, &suras[count].ayat_count) == 2)
      {
            count++;
      }

      fclose(file);
      return count;
}

void save_data(Sura *suras, int count)
{
      FILE *file = fopen(FILENAME, "w");
      for (int i = 0; i < count; i++)
      {
            fprintf(file, "%s:%d\n", suras[i].name, suras[i].ayat_count);
      }
      fclose(file);
}

void sort_suras(Sura *suras, int count)
{
      for (int i = 0; i < count - 1; i++)
      {
            for (int j = 0; j < count - i - 1; j++)
            {
                  if (strcmp(suras[j].name, suras[j + 1].name) > 0)
                  {
                        Sura temp = suras[j];
                        suras[j] = suras[j + 1];
                        suras[j + 1] = temp;
                  }
            }
      }
}

int main()
{
      Sura suras[MAX_SURAS];
      int sura_count = load_data(suras);
      char select[10];

      printf("1) + Yangi sura qoshish\n");
      printf("2) + Barcha suralarni korish\n");
      printf("3) + Sura malumotlarini ozgartirish\n");
      printf("4) + Surani ochirish\n");

      while (1)
      {
            printf(">>> ");
            fgets(select, sizeof(select), stdin);
            select[strcspn(select, "\n")] = 0;

            if (strcmp(select, "1") == 0)
            {
                  if (sura_count >= MAX_SURAS)
                  {
                        printf("Suralar soni chegaraga yetdi!\n");
                        sleep(1);
                        continue;
                  }

                  printf("Yangi sura nomini kiriting: ");
                  fgets(suras[sura_count].name, MAX_NAME, stdin);
                  suras[sura_count].name[strcspn(suras[sura_count].name, "\n")] = 0;

                  printf("%s surasidan nechta oyat yodladiniz? ", suras[sura_count].name);
                  while (scanf("%d", &suras[sura_count].ayat_count) != 1 || suras[sura_count].ayat_count < 0)
                  {
                        printf("Iltimos, 0 yoki undan katta son kiriting!\n");
                        while (getchar() != '\n')
                              ;
                        printf("%s surasidan nechta oyat yodladiniz? ", suras[sura_count].name);
                  }
                  while (getchar() != '\n')
                        ;

                  sura_count++;
                  sort_suras(suras, sura_count);
                  save_data(suras, sura_count);
                  printf("'%s' surasi %d oyat bilan qo'shildi!\n", suras[sura_count - 1].name, suras[sura_count - 1].ayat_count);
                  sleep(1);
            }
            else if (strcmp(select, "2") == 0)
            {
                  if (sura_count == 0)
                  {
                        printf("Hozircha suralar mavjud emas!\n");
                  }
                  else
                  {
                        printf("\nBarcha suralar:\n");
                        for (int i = 0; i < sura_count; i++)
                        {
                              printf("%d. %s - %d oyat yodlangan\n", i + 1, suras[i].name, suras[i].ayat_count);
                        }
                  }
                  sleep(1);
            }
            else if (strcmp(select, "3") == 0)
            {
                  if (sura_count == 0)
                  {
                        printf("Ozgartirish uchun suralar mavjud emas!\n");
                  }
                  else
                  {
                        printf("\nOzgartiriladigan surani tanlang:\n");
                        for (int i = 0; i < sura_count; i++)
                        {
                              printf("%d. %s\n", i + 1, suras[i].name);
                        }

                        int choice;
                        printf("Sura raqamini kiriting: ");
                        while (scanf("%d", &choice) != 1 || choice < 1 || choice > sura_count)
                        {
                              printf("1 dan %d gacha raqam kiriting!\n", sura_count);
                              while (getchar() != '\n')
                                    ;
                              printf("Sura raqamini kiriting: ");
                        }
                        while (getchar() != '\n')
                              ;

                        printf("%s uchun yangi oyat sonini kiriting: ", suras[choice - 1].name);
                        while (scanf("%d", &suras[choice - 1].ayat_count) != 1 || suras[choice - 1].ayat_count < 0)
                        {
                              printf("Iltimos, 0 yoki undan katta son kiriting!\n");
                              while (getchar() != '\n')
                                    ;
                              printf("%s uchun yangi oyat sonini kiriting: ", suras[choice - 1].name);
                        }
                        while (getchar() != '\n')
                              ;

                        save_data(suras, sura_count);
                        printf("'%s' surasi uchun oyat soni %d ga yangilandi!\n", suras[choice - 1].name, suras[choice - 1].ayat_count);
                        sleep(1);
                  }
            }
            else if (strcmp(select, "4") == 0)
            {
                  if (sura_count == 0)
                  {
                        printf("Ochirish uchun suralar mavjud emas!\n");
                  }
                  else
                  {
                        printf("\nOchiriladigan surani tanlang:\n");
                        for (int i = 0; i < sura_count; i++)
                        {
                              printf("%d. %s\n", i + 1, suras[i].name);
                        }

                        int choice;
                        printf("Sura raqamini kiriting: ");
                        while (scanf("%d", &choice) != 1 || choice < 1 || choice > sura_count)
                        {
                              printf("1 dan %d gacha raqam kiriting!\n", sura_count);
                              while (getchar() != '\n')
                                    ;
                              printf("Sura raqamini kiriting: ");
                        }
                        while (getchar() != '\n')
                              ;

                        for (int i = choice - 1; i < sura_count - 1; i++)
                        {
                              suras[i] = suras[i + 1];
                        }
                        sura_count--;
                        save_data(suras, sura_count);
                        printf("Sura o'chirildi!\n");
                        sleep(1);
                  }
            }
            else
            {
                  printf("Faqat 1, 2, 3 yoki 4 ni tanlang!\n");
                  sleep(1);
            }
      }

      return 0;
}