#include "myhead.h"
#define fname "vehicle_info.dat"

void write_file(Vehicle *v, unsigned size) {
  FILE *fp = NULL;

  if ((fp = fopen(fname, "wb")) == NULL) {
    puts("File could not be opened.");
  } else {
    for (int i = 0; i < size; ++i) {
      fwrite(&v[i], sizeof(Vehicle), 1, fp);
    }
  }

  fclose(fp);
}

void read_file(Vehicle *v, unsigned size) {
  FILE *fp = NULL;

  if ((fp = fopen(fname, "rb")) == NULL) {
    puts("File could not be opened.");
  } else {
    while (!feof(fp)) {
      for (int i = 0; i < size; ++i) {
        fscanf(fp, "%s", &v[i]);
      }
      puts("File copied");
    }

    fclose(fp);
  }
}
 