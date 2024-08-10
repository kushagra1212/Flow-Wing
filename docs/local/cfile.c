
#include <stdio.h>
#include <stdlib.h>

// int x= 1;
int main() {
    FILE *file;
    char *filename = "temp.txt";
    char *data = "Hello, LLVM!\n";
    
    // Open the file for writing ("w" mode)
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }
   

    
    // Write data to the file
    if (fwrite(data, sizeof(char), sizeof(data), file) != sizeof(data)) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    
    // Close the file after writing
    fclose(file);

    // Open the file for reading ("r" mode)
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }
    
    // Allocate buffer to read the data
    char buffer[100];
    
    // Read the data from the file
    if (fread(buffer, sizeof(char), sizeof(buffer) - 1, file) > 0) {
        buffer[sizeof(buffer) - 1] = '\0';  // Ensure null-termination
        printf("Data read from file: %s", buffer);
    } else {
        perror("Error reading from file");
    }

    // Close the file after reading
    fclose(file);
    
    return EXIT_SUCCESS;
}

// void setX(int getX());
