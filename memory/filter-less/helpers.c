#include "helpers.h"
#include <stdint.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE original = image[i][j];
            int sepiaRed = .393 * original.rgbtRed + .769 * original.rgbtGreen +
                           .189 * original.rgbtBlue;
            int sepiaGreen = .349 * original.rgbtRed +
                             .686 * original.rgbtGreen +
                             .168 * original.rgbtBlue;
            int sepiaBlue = .272 * original.rgbtRed +
                            .534 * original.rgbtGreen +
                            .131 * original.rgbtBlue;
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
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
