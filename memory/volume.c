// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of uint16_ts in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    // TODO: Copy header from input file to output file

    uint16_t header[HEADER_SIZE];
    if (fread(header, sizeof(uint16_t), HEADER_SIZE, input) != HEADER_SIZE) {
        printf("Could not read file.\n");
        return 1;
    }

    if (fwrite(header, sizeof(uint16_t), HEADER_SIZE, output) != HEADER_SIZE) {
        printf("Could not write file.\n");
        return 1;
    }

    // TODO: Read samples from input file and write updated data to output
    // file
    int16_t sample = 0;
    while (fread(&sample, sizeof(int16_t), 1, input) == 1) {
        sample *= factor;
        if (fwrite(&sample, sizeof(int16_t), 1, output) != 1) {
            printf("Could not write file.\n");
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);
}
