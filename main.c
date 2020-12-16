//
// Created by CalebCintary 15.12.2020
//
/**
 * FIXME Found exception when closing program
 *      When program shutdown free call exception with invalid pointer also with
 *      returning pointer to start value. After it, i can think that free methods inside program
 *      also doesnt work.
 *
 * Program works on
 *  ArchLinux amd64 linux 5.10.1.arch1-1 gcc 10.2.0-4 gdb 10.1-4 ncurses 6.2-1
 */

#include "stdlib.h"
#include "stdio.h"
#include "ncurses.h"
#include "MatrixType.h"
#include "TV.h"


struct TV* array;
struct TV* pStart;
size_t size;

void add_new_tv() { // Function for adding object into dynamic array
    clear(); // Clear screen from previous messages
    pStart = realloc(pStart, ++size*sizeof(struct TV)); //Realloc memory for inserting new object
    if (pStart == NULL) { // Check for null
        fprintf(stderr, "Failed to reallocate array");
    }
    array = pStart + (size - 1) * sizeof(struct TV); // move pointer to last object and inputing data from terminal
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
    clear(); //Clear screen from previous messages
    int id = 0;
    printw("Select TV id (0..%d): ", size - 1); scanw("%d", &id);
    return id;
}
void display_tv() {
    int id = select_id(); //Getting needed id
    clear();
    array = pStart + id * sizeof(struct TV); //Moving pointer to needed object

    //Output
    printw("Model name is %s\n", &array->model);
    printw("Manufacturer is %s\n", &array->manufacturer);
    
    char* matrixType;
    switch (array->matrixType) //Selecting needed enum object because we do not have enum.getName().toUpperCase()
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
    clear(); //Clear screen from previous messages
    int id = select_id(); //Getting needed id
    clear(); // Clear screen from previous messages
    array = pStart; //Moving array to start
    struct TV* newArray = malloc((size - 1) * sizeof(struct TV)); //Allocating memory for new data
    struct TV* pNewStart = newArray;
    if (newArray == NULL) {
        printw("Failed to allocate memory\n");
        printw("Press any key to exit");
        getch();
        exit(-1);
    }

    for (int i = 0; i < size; ++i) { //Copying data except removed
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

    free(pStart); // removing previous array and updating current to buffer
    array = pNewStart;
    pStart = pNewStart;
    --size;
    clear();
}





int main(int argc, char** argv) {

    size = 0;
    array = malloc(0); //Allocating dynamic array
    pStart = array;

    initscr(); //Initializing ncurses terminal screen
    int WindowShouldClose = 0;

    while (!WindowShouldClose) //Main loop
    {

        //Getting action id and invoke selected function
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
                WindowShouldClose = 1;
                break;
            }
        }
        clear();
    }
    

    endwin(); //Freeing memory and terminating ncurses
    array = pStart;
    free(array);

    return 0;
}




