#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE original = image[i][j];
            BYTE average =
                (original.rgbtBlue + original.rgbtGreen + original.rgbtRed) / 3;
            RGBTRIPLE now = {average, average, average};
            image[i][j] = now;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < (width / 2); j++) {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][(width - 1) - j]; // index should -1
            image[i][(width - 1) - j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width]; /* store in stack, may overflow */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r = 0;
            int g = 0;
            int b = 0;
            int count = 0;
            int min_row = (i - 1 < 0) ? 0 : i - 1;
            int min_col = (j - 1 < 0) ? 0 : j - 1;
            int max_row = (i + 1 > height - 1) ? height - 1 : i + 1;
            int max_col = (j + 1 > width - 1) ? width - 1 : j + 1;

            for (int row = min_row; row <= max_row; row++) {
                for (int col = min_col; col <= max_col; col++) {
                    r += copy[row][col].rgbtRed;
                    g += copy[row][col].rgbtGreen;
                    b += copy[row][col].rgbtBlue;
                    count++;
                }
            }
            image[i][j].rgbtRed = r / count;
            image[i][j].rgbtGreen = g / count;
            image[i][j].rgbtBlue = b / count;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int rx = 0;
            int gx = 0;
            int bx = 0;
            int ry = 0;
            int gy = 0;
            int by = 0;

            const int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            const int GY[3][3] = {{-1, -2, -1}, {-0, 0, 0}, {1, 2, 1}};

            for (int left_index = 0, row = i - 1; left_index < 3;
                 left_index++, row++) {
                for (int right_index = 0, col = j - 1; right_index < 3;
                     right_index++, col++) {
                    BYTE r;
                    BYTE g;
                    BYTE b;
                    if (row < 0 || col < 0 || row == height || col == width) {
                        continue;
                    } else {
                        r = copy[row][col].rgbtRed;
                        g = copy[row][col].rgbtGreen;
                        b = copy[row][col].rgbtBlue;
                    }
                    rx += r * GX[left_index][right_index];
                    gx += g * GX[left_index][right_index];
                    bx += b * GX[left_index][right_index];
                    ry += r * GY[left_index][right_index];
                    gy += g * GY[left_index][right_index];
                    by += b * GY[left_index][right_index];
                }
            }
            image[i][j].rgbtRed =
                sqrt(rx * rx + ry * ry) < 256 ? sqrt(rx * rx + ry * ry) : 255;
            image[i][j].rgbtGreen =
                sqrt(gx * gx + gy * gy) < 256 ? sqrt(gx * gx + gy * gy) : 255;
            image[i][j].rgbtBlue =

                sqrt(bx * bx + by * by) < 256 ? sqrt(bx * bx + by * by) : 255;
        }
    }
}
