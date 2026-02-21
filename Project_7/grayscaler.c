#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ppm.h"

typedef struct {
    struct ppm *img;
    int thread_id;
    int start_y;
    int rows;

    long r_sum;
    long g_sum;
    long b_sum;
} thread_data_t;

void *run(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;

    int width = data->img->width;
    int end_y = data->start_y + data->rows;

    data->r_sum = 0;
    data->g_sum = 0;
    data->b_sum = 0;

    for (int y = data->start_y; y < end_y; y++) {
        for (int x = 0; x < width; x++) {

            int pixel = ppm_get_pixel(data->img, x, y);

            int r = PPM_PIXEL_R(pixel);
            int g = PPM_PIXEL_G(pixel);
            int b = PPM_PIXEL_B(pixel);

            data->r_sum += r;
            data->g_sum += g;
            data->b_sum += b;

            int gray = (299*r + 587*g + 114*b) / 1000;
            int gray_pixel = PPM_PIXEL(gray, gray, gray);

            ppm_set_pixel(data->img, x, y, gray_pixel);
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <threads> <input.ppm> <output.ppm>\n", argv[0]);
        return 1;
    }

    int thread_count = atoi(argv[1]);
    char *input_file = argv[2];
    char *output_file = argv[3];

    struct ppm *img = ppm_read(input_file);
    if (!img) {
        fprintf(stderr, "Failed to read input image\n");
        return 1;
    }

    pthread_t threads[thread_count];
    thread_data_t thread_data[thread_count];

    int height = img->height;
    int base_rows = height / thread_count;
    int remainder = height % thread_count;

    int current_y = 0;

    for (int i = 0; i < thread_count; i++) {
        thread_data[i].img = img;
        thread_data[i].thread_id = i;
        thread_data[i].start_y = current_y;
        thread_data[i].rows = base_rows;

        if (i == thread_count - 1) {
            thread_data[i].rows += remainder;
        }

        printf("Thread %d: %d %d\n",
               i,
               thread_data[i].start_y,
               thread_data[i].rows);

        pthread_create(&threads[i], NULL, run, &thread_data[i]);

        current_y += thread_data[i].rows;
    }

    long total_r = 0;
    long total_g = 0;
    long total_b = 0;

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);

        total_r += thread_data[i].r_sum;
        total_g += thread_data[i].g_sum;
        total_b += thread_data[i].b_sum;
    }

    long total_pixels = (long)img->width * img->height;

    printf("Average R: %ld\n", total_r / total_pixels);
    printf("Average G: %ld\n", total_g / total_pixels);
    printf("Average B: %ld\n", total_b / total_pixels);

    if (ppm_write(img, output_file) != 0) {
        fprintf(stderr, "Failed to write output image\n");
    }

    ppm_free(img);
    return 0;
}