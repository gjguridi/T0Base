#pragma once
#include <stdint.h>

typedef struct pixel_rgb {
  uint8_t R; // Red component
  uint8_t G; // Green component
  uint8_t B; // Blue component
} Pixel_rgb;

typedef struct image_rgb {
  int width; // The width of the image in pixels
  int height; // The height of the image in pixels
  Pixel_rgb **pixels; // Pixel data
} Image_rgb;

/* 
 * Loads an image located in "path". Each pixel contains red, green and blue components (RGB).
 */
Image_rgb *load_image_rgb(char const *path);

/*
 * Receives a struct of type Image_rgb, and writes it in "path".
 * "path" should end with .png or .bmp (i.e. "../hello.png").
 */
void write_image_rgb(char const *path, Image_rgb *image);
