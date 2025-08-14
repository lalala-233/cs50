#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t JPEG_HEADER[4] = {
    0xff, 0xd8, 0xff, 0x0e}; // 0x0e is the first four bits of the fourth byte.
const int BLOCK_SIZE = 512;
const int FILENAME_SIZE = 7;
bool contains_jpeg_header(uint8_t buffer[BLOCK_SIZE]);
void increase_filename(char filename[FILENAME_SIZE]);
int main(int argc, char *argv[]) {
    FILE *raw;
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    raw = fopen(argv[1], "r");
    if (raw == NULL) {
        printf("Cannot open %s\n", argv[1]);
        return 1;
    }
    uint8_t buffer[BLOCK_SIZE];
    char filename[] = "000.jpg";
    bool should_copy = false;
    FILE *jpeg = NULL;
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, raw)) {
        if (contains_jpeg_header(buffer)) {
            if (jpeg != NULL) {
                fclose(jpeg);
            }
            jpeg = fopen(filename, "w");
            increase_filename(filename);
            if (jpeg == NULL) {
                printf("Cannot open %s\n", filename);
            }
            should_copy = true;
        }
        if (should_copy) {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, jpeg);
        }
    }
    fclose(raw);
}

bool contains_jpeg_header(uint8_t buffer[BLOCK_SIZE]) {
    return JPEG_HEADER[0] == buffer[0] && JPEG_HEADER[1] == buffer[1] &&
           JPEG_HEADER[2] == buffer[2] && ((buffer[3] >> 4) == JPEG_HEADER[3]);
}
void increase_filename(char filename[FILENAME_SIZE]) {
    if (filename[2] == '9') {
        filename[2] = '0';
        if (filename[1] == '9') {
            filename[1] = '0';
            filename[0]++;
        } else {
            filename[1]++;
        }
    } else {
        filename[2]++;
    }
}
