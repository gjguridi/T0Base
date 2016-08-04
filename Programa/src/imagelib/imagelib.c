#include <stdlib.h>
#include <string.h>
#include "imagelib.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

const char *get_filetype(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot + 1;
}

Image_rgb *load_image_rgb(char const *path) {
  Image_rgb *image = calloc(1, sizeof(Image_rgb));
  int n; // number of channels given by the original format
  uint8_t *data = stbi_load(path, &image->width, &image->height, &n, 3);

  if (data == NULL) {
    puts("ERROR: Could not read image file");
    exit(EXIT_FAILURE);
  }

  image->pixels = calloc(image->width, sizeof(Pixel_rgb*));
  for (int x = 0; x < image->width; x++) {
    image->pixels[x] = calloc(image->height, sizeof(Pixel_rgb));
    for (int y = 0; y < image->height; y++) {

      // Create new pixel from the image's data
      uint8_t *pixel_data = &data[x * 3 + y * image->width * 3];
      Pixel_rgb pixel = {pixel_data[0], pixel_data[1], pixel_data[2]};

      image->pixels[x][y] = pixel;
    }
  }

  stbi_image_free(data);

  return image;
}

void write_image_rgb(char const *path, Image_rgb *image) {
  const char *filetype = get_filetype(path);
  if (strcmp(filetype, "png") != 0 && strcmp(filetype, "bmp") != 0) {
    puts("ERROR: output filename should end in .png or .bmp");
    exit(EXIT_FAILURE);
  }

  int size = image->width * image->height * 3;
  uint8_t *data = calloc(size, sizeof(uint8_t));

  unsigned long index = 0;
  for (int y = 0; y < image->height; y++) {
    for (int x = 0; x < image->width; x++) {
      data[index++] = image->pixels[x][y].R;
      data[index++] = image->pixels[x][y].G;
      data[index++] = image->pixels[x][y].B;
    }
  }

  int result = 0;
  if (strcmp(filetype, "png") == 0) {
    result = stbi_write_png(path, image->width, image->height, 3, data, 0);
  } else if (strcmp(filetype, "bmp") == 0) {
    result = stbi_write_bmp(path, image->width, image->height, 3, data);
  }

  if (result == 0) {
    puts("ERROR: could not write data");
    exit(EXIT_FAILURE);
  }

  free(data);
}
