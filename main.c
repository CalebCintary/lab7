#include "stdlib.h"
#include "stdio.h"
#include "ncurses.h"
#include "MatrixType.h"
#include "TV.h"


struct TV* array;
struct TV* pStart;
size_t size;

void add_new_tv() {
    clear();
    pStart = realloc(pStart, ++size*sizeof(struct TV));
    if (pStart == NULL) {
        fprintf(stderr, "Failed to reallocate array");
    }
    array = pStart + (size - 1) * sizeof(struct TV);
    printw("Input model name: "); scanw("%s", &array->model);
    printw("Input manufacturer name: "); scanw("%s", &array->manufacturer);
    printw("Input matrix resolution: "); scanw("%s", &array->resolution);
    printw("Input refresh rate: "); scanw("%s", &array->refreshRate);
    printw("Select matrix type: \n");
    printw("1. LED\n");
    printw("2. AMOLED\n");
    printw("3. TN\n");
    printw("4. TNFILM\n");
    printw("5. VA");
    int matrixtype = 0;
    scanw("%d", &matrixtype);
    array->matrixType = matrixtype - 1;
}

int select_id() {
    clear();
    int id = 0;
    printw("Select TV id (0..%d): ", size - 1); scanw("%d", &id);
    return id;
}
void display_tv() {
    int id = select_id();
    clear();
    array = pStart + id * sizeof(struct TV);
    
    printw("Model name is %s\n", &array->model);
    printw("Manufacturer is %s\n", &array->manufacturer);
    
    char* matrixType;
    switch (array->matrixType)
    {
    case 0:
        matrixType = "LED";
        break;
    case 1: 
        matrixType = "AMOLED";
        break;
    case 2:
        matrixType = "TN";
        break;
    case 3: 
        matrixType = "TNFILM";
        break;
    case 4: 
        matrixType = "VA";
        break;
    default:
        matrixType = "unknown matrixType";
        break;
    }
    printw("Matrix type is %s\n", matrixType);

    printw("Resolution is %s\n", &array->resolution);
    printw("Refresh rate is %s\n", &array->refreshRate);

    printw("Press any key to continue...");
    getch();
}

void remove_tv() {
    clear();
    int id = select_id();
    clear();
    array = pStart;
    struct TV* newArray = malloc((size - 1) * sizeof(struct TV));
    struct TV* pNewStart = newArray;
    if (newArray == NULL) {
        printw("Failed to allocate memory\n");
        printw("Press any key to exit");
        getch();
        exit(-1);
    }

    for (int i = 0; i < size; ++i) {
        if (i != id) {
            newArray->model = array->model;
            newArray->manufacturer = array->manufacturer;
            newArray->matrixType = array->matrixType;
            newArray->resolution = array->resolution;
            newArray->refreshRate = array->refreshRate;
            newArray += sizeof(struct TV);
        }
        array += sizeof(struct TV);
    }

    free(pStart);
    array = pNewStart;
    pStart = pNewStart;
    --size;
    clear();
}





int main(int argc, char** argv) {

    size = 0;
    array = malloc(0);
    pStart = array;

    initscr();
    int WindowShouldClose = 0;

    while (!WindowShouldClose)
    {
        printw("Select menu entry: \n 1. Add new TV\n 2. Display TV info \n 3. Remove TV \n 4. Exit\n");
        refresh();
        int key = getch();
        if ((key >= 49) && (key <= 52)) {
            switch (key)
            {
            case 49: 
                add_new_tv();
                break;
            case 50: 
                display_tv();
                break;
            case 51: 
                remove_tv();
                break;
            case 52:
                endwin();
                free(array);
                exit(0);
                break;
            default:
                break;
            }
        }
        clear();
    }
    

    endwin();
    array = pStart;
    free(array);

    return 0;
}




