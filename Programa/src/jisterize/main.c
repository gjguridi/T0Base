#include "../imagelib/imagelib.h"
#include <stdio.h>
#include <stdlib.h>

Pixel_rgb *get_pixel(Image_rgb *image, int x, int y) {
  /*
   * Acá vean los casos borde!
   */
  return &image->pixels[x][y];
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: example source target");
    return 1;
  }

  Image_rgb *image = load_image_rgb(argv[1]);

  /*
   * En este ejemplo invertimos el color de cada pixel de la imagen original.
   * Si lo prefieren, pueden crear una nueva imagen e ir trabajando con ella.
   */
  for (int x = 0; x < image->width; x++) {
    for (int y = 0; y < image->height; y++) {
      Pixel_rgb *pixel = get_pixel(image, x, y);
      pixel->R = 255 - pixel->R;
      pixel->G = 255 - pixel->G;
      pixel->B = 255 - pixel->B;
    }
  }

  /*
   * Escribimos la "misma" imagen, pero que ahora tiene los colores invertidos
   */
  write_image_rgb(argv[2], image);

  /*
   * OJO: en el ejemplo no se libera memoria, esta es TU pega :)
   */

  return 0;
}
