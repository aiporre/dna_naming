
#ifndef DNA_NAMING_TABLECODE_H
#define DNA_NAMING_TABLECODE_H

#endif //DNA_NAMING_TABLECODE_H


#define HEIGHT 14
#define WIDTH  24

int** getTable() {
    int** dharmaconTable = 0;

    dharmaconTable = new int*[HEIGHT];

    int cellCount = 1;
    int densities[3] = {3000, 1000, 300}, *d;
    d = densities;

    // init table with zeros
    for (int h = 0; h < HEIGHT; h++){
        dharmaconTable[h] = new int[WIDTH];
        for(int w = 0; w < WIDTH; w++)
            dharmaconTable[h][w] = 0;
    }

    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            if (cellCount < 23) {
                if (h > 1 and h % 2 == 0) {
                    if (w > 1 and w % 2 == 0) {
                        dharmaconTable[h][w] = cellCount + *d;
                        dharmaconTable[h + 1][w] = cellCount + *d;
                        dharmaconTable[h][w + 1] = cellCount + *d;
                        cellCount++;
                    }
                }
            } else {
                cellCount = 1;
                d++;
            }
        }
    }

    return dharmaconTable;
}


void printTable(int** const & table){
    for (int i=0; i<HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            std::cout << table[i][j] << "\t";
        std::cout <<";\n";
    }

}

int** const LAYOUT = getTable();
