#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Get the original RGB values (rgbtBlue, rgbtGreen, rgbtRed)
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Get the average, rounded to the nearest int
            int average = round((float)(image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3);

            // Set the new pixel to this number
            image[r][c].rgbtBlue = average;
            image[r][c].rgbtGreen = average;
            image[r][c].rgbtRed =  average;
        }
    }

    return;
}

int limit(int n)
{
    if (n >= 255)
    {
        return 255;
    }

    return n;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory instead?
    // Copy the image to have an unmodified version
    RGBTRIPLE original_image[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Reach for the opposite side pixel
            original_image[r][c].rgbtBlue = image[r][c].rgbtBlue;
            original_image[r][c].rgbtGreen = image[r][c].rgbtGreen;
            original_image[r][c].rgbtRed = image[r][c].rgbtRed;
        }
    }

    // Get the original RGB values (rgbtBlue, rgbtGreen, rgbtRed)
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int red_sepia = round((0.393 * original_image[r][c].rgbtRed) + (0.769 * original_image[r][c].rgbtGreen) +
                                  (0.189 * original_image[r][c].rgbtBlue));
            int green_sepia  = round((0.349 * original_image[r][c].rgbtRed) + (0.686 * original_image[r][c].rgbtGreen) +
                                     (0.168 * original_image[r][c].rgbtBlue));
            int blue_sepia = round((0.272 * original_image[r][c].rgbtRed) + (0.534 * original_image[r][c].rgbtGreen) +
                                   (0.131 * original_image[r][c].rgbtBlue));

            // Set the new pixel to this number
            image[r][c].rgbtBlue = limit(blue_sepia);
            image[r][c].rgbtGreen = limit(green_sepia);
            image[r][c].rgbtRed =  limit(red_sepia);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory instead?
    // Copy the image to have an unmodified version
    RGBTRIPLE original_image[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Reach for the opposite side pixel
            original_image[r][c].rgbtBlue = image[r][c].rgbtBlue;
            original_image[r][c].rgbtGreen = image[r][c].rgbtGreen;
            original_image[r][c].rgbtRed = image[r][c].rgbtRed;
        }
    }

    // Get the original RGB values (rgbtBlue, rgbtGreen, rgbtRed)
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Reach for the opposite side pixel
            image[r][c].rgbtBlue = original_image[r][(width - 1) - c].rgbtBlue;
            image[r][c].rgbtGreen = original_image[r][(width - 1) - c].rgbtGreen;
            image[r][c].rgbtRed = original_image[r][(width - 1) - c].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the image to have an unmodified version
    RGBTRIPLE original_image[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Reach for the opposite side pixel
            original_image[r][c].rgbtBlue = image[r][c].rgbtBlue;
            original_image[r][c].rgbtGreen = image[r][c].rgbtGreen;
            original_image[r][c].rgbtRed = image[r][c].rgbtRed;
        }
    }

    // Access this pixel
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int pixel_sum_b = 0;
            int pixel_sum_g = 0;
            int pixel_sum_r = 0;
            int surrounding_pixels = 0;

            // Find the pixels surrounding this one
            for (int y = r - 1; y < r + 2; y++)
            {
                for (int x = c - 1; x < c + 2; x++)
                {
                    // If not in the array, assume its black
                    if (!(x < 0 || y < 0 || x > width - 1 || y > height - 1))
                    {
                        // Assume this is not black
                        pixel_sum_b += original_image[y][x].rgbtBlue;
                        pixel_sum_g += original_image[y][x].rgbtGreen;
                        pixel_sum_r += original_image[y][x].rgbtRed;
                        surrounding_pixels += 1;
                    }
                }
            }

            image[r][c].rgbtBlue = round((float) pixel_sum_b / (surrounding_pixels));
            image[r][c].rgbtGreen = round((float) pixel_sum_g / (surrounding_pixels));
            image[r][c].rgbtRed = round((float) pixel_sum_r / (surrounding_pixels));
        }
    }
    return;
}
