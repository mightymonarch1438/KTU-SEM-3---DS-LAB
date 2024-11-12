#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }
    
    char line[100];
    int start_addr, load_addr;

    if (fscanf(input, "%s", line) == 1 && line[0] == 'H') {
        char name[20], addr[5];
        int i = 2, j = 0;
        
        // Extract the program name
        while (line[i] != '^') {
            name[j++] = line[i++];
        }
        name[j] = '\0';
        i++;
        
        // Extract and convert the start address
        for (j = 0; j < 4; ++j) {
            addr[j] = line[i++];
        }
        addr[4] = '\0';  // Null-terminate for strtol
        start_addr = strtol(addr, NULL, 16);

        printf("THE NAME OF THE FILE IS: %s\n", name);
        printf("THE STARTING ADDRESS IS: %04X\n", start_addr);
    }

    // Read and process text records
    while (fscanf(input, "%s", line) == 1) {
        if (line[0] == 'T') {
            char load[5];

            // Extract and convert load address
            for (int i = 0; i < 4; ++i) {
                load[i] = line[i + 2];
            }
            load[4] = '\0';
            load_addr = strtol(load, NULL, 16);
            printf("THE STARTING ADDRESS OF TEXT RECORD IS: %04X\n", load_addr);

            int i = 10;
            while (line[i] != '\0') {
                if (line[i] == '^') {
                    i++;
                } else {
                    printf("ADDRESS %04X: %c%c\n", load_addr++, line[i], line[i + 1]);
                    i += 2;
                }
            }
        } else if (line[0] == 'E') {
            break;
        }
    }

    printf("THE EXECUTION ADDRESS IS: %04X\n", start_addr);
    fclose(input);
    return 0;
}