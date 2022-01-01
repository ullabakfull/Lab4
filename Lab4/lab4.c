#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myhead.h"

#define MAX_SIZE 10
#define MAX_MEM 20

//BUGS
//Saving a full file causes it to remove all vehicles inside file


void ask(Vehicle *v, unsigned c, unsigned size)
{
  if (c < size)
  {
    printf("\nEnter Vehicle |%d|\n", c+1);
    printf("\nType of car:\t");
    scanf("%s", v[c].type);
    printf("\nEnter Brand:\t");
    scanf("%s", v[c].brand);
    printf("\nLicense Plate Name:\t");
    scanf("%s", v[c].license_plate);
    printf("\nEnter Owner Name:\t");
    scanf("%s", v[c].owner.name);
    printf("\nEnter Owner Age:\t");
    while (scanf("%d", &v[c].owner.age) != 1)
    {
      printf("Please enter a number instead\n");
      for (int ch; (ch = getchar()) != EOF && ch != '\n';){ }
    }
  }
  else
  {
    printf("no more space");
  }
}
void display(Vehicle *v, unsigned length)
{
  int i;

  for (i = 0; i < length; i++)
  {
    printf("\n\n--|Vehicle number %d|--", i + 1);
    printf("\nType: %s", v[i].type);
    printf("\nBrand: %s", v[i].brand);
    printf("\nLicense plate: %s", v[i].license_plate);
    printf("\nOwner name: %s", v[i].owner.name);
    printf("\nOwner age: %d", v[i].owner.age);
  }
}
void remove_ask(Vehicle *v, unsigned length, unsigned position)
{
  int i = position;
  while (i <= length)
  {
    v[i - 1] = v[i];
    i++;
  }
}

void sort(Vehicle *v, unsigned length)
{
  int i, j;
  Vehicle temp;
  for (i = 0; i < length - 1; i++)
    for (j = i + 1; j < length; j++)
      if (strcmp(v[i].brand, v[j].brand) < 0)
      {
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
      }
}

void display_one(Vehicle *v, unsigned position)
{
  int i = position - 1, j = position;
  printf("\n\n--|Vehicle number %d|--", j);
  printf("\nType: %s", v[i].type);
  printf("\nBrand: %s", v[i].brand);
  printf("\nLicense plate: %s", v[i].license_plate);
  printf("\nOwner name: %s", v[i].owner.name);
  printf("\nOwner age: %d", v[i].owner.age);
}

int main()
{
  int choice, i, d = 0, pos;
  bool end = false, counted = false, isRead = false;
  Vehicle *v;
  v = (Vehicle *)calloc(MAX_MEM, sizeof(Vehicle));
  if (!access("vehicle_info.dat", F_OK))
  {
    read_file(v, MAX_SIZE);
    isRead = true;
  }
  while (!end)
  {
    printf("\n\nMenu\n");
    printf("====\n\n");
    printf("1. add Vehicle\n");
    printf("2. remove Vehicle\n");
    printf("3. sort by brand\n");
    printf("4. print Vehicle info\n");
    printf("5. print all vehicles\n");
    printf("6. end\n\n");
    printf("Enter your choice:");

    while (scanf("%d", &choice) != 1)
    {
      printf("Please enter a number instead\n");
      for (int ch; (ch = getchar()) != EOF && ch != '\n';){ }
    }
    switch (choice)
    {
    case 1:
    {
      if (counted == false && isRead == true)
      {
        d = v[0].owner.count;
        if (d >= MAX_SIZE)
        {
          printf("Out of space");
          break;
        }
        ask(v, d, MAX_SIZE);
        for (int i = 0; i < MAX_SIZE; i++)
          v[i].owner.count = d + 1;
        d = v[0].owner.count;
        //d = d + 1;
        counted = true;
      }
      else
      {
        if (d >= MAX_SIZE)
        {
          printf("Out of space");
          break;
        }
        ask(v, d, MAX_SIZE);
        d = d + 1;
        for (i = 0; i < MAX_SIZE; i++)
        {
          v[i].owner.count = d;
        }
      }
    }
    break;
    case 2:
    {
      if (v[0].owner.count == 0)
      {
        printf("No Vehicles to remove");
        break;
      }

      printf("\nEnter Vehicle to remove: ");
      scanf("%d", &pos);
      while (pos > v[0].owner.count || pos == 0)
      {
        printf("\nEnter valid Vehicle to remove: ");
        scanf("%d", &pos);
      }
      remove_ask(v, v[0].owner.count, pos);
      for (i = 0; i < MAX_SIZE; i++)
      {
        --v[i].owner.count;
      }
      d = v[0].owner.count;
      printf("\nVehicle has been removed");
    }
    break;
    case 3:
    {
      sort(v, MAX_SIZE);
    }
    break;
    case 4:
    {
      if (v[0].owner.count == 0)
      {
        printf("%d", v[0].owner.count);
        printf("No Vehicles to display");
        break;
      }
      printf("\nEnter Vehicle to display: ");
      if (d == MAX_SIZE - 1)
      {
        d = MAX_SIZE - 1;
      }
      else
      {
        d = d - 1;
      }
      scanf("%d", &pos);
      while (pos > v[0].owner.count || pos == 0)
      {
        printf("\nEnter valid Vehicle to display: ");
        scanf("%d", &pos);
      }
      display_one(v, pos);
    }
    break;
    case 5:
    {
      if (v[0].owner.count == 0)
      {
        printf("No Vehicles found");
      }
      else
      {
        display(v, v[0].owner.count);
      }
    }
    break;
    case 6:
    {
      write_file(v, MAX_SIZE);
      free(v);
      end = true;
    }
    }
  }
}