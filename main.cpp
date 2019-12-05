//
// Created by Viktor Meyer on 2019-12-05.
//

#include <random>
#include "bitmap_image.hpp"

/**
 * @param color input
 * @return true iff any color channel exceeds cutoff
 */
bool has_color(const rgb_t color) {
    constexpr auto cutoff = 64;
    if (color.red < cutoff) return true;
    if (color.blue < cutoff) return true;
    if (color.green < cutoff) return true;
    return false;
}

/**
 * @param input image
 * @return a copy of image with each pixel in black and white
 */
bitmap_image ibw(const bitmap_image &input) {
    bitmap_image result(input.height(), input.width());
    result.set_all_channels(255);
    for (std::size_t y = 0; y < input.height(); ++y) {
        for (std::size_t x = 0; x < input.width(); ++x) {
            image_drawer draw(result);
            draw.pen_width(1);
            draw.pen_color(0, 0, 0);
            if (has_color(input.get_pixel(x, y))) {
                draw.plot_pen_pixel(x, y);
            }
        }
    }
    return result;
}

/**
 * @param input image 1
 * @param input image 2
 * @return a copy of image 1 and image 2 with each pixel merged by xor
 */
bitmap_image ixor(const bitmap_image &input1, const bitmap_image &input2) {
    bitmap_image result(input1.height(), input1.width());
    result.set_all_channels(255);
    for (std::size_t y = 0; y < input1.height(); ++y) {
        for (std::size_t x = 0; x < input1.width(); ++x) {
            image_drawer draw(result);
            draw.pen_width(1);
            draw.pen_color(0, 0, 0);
            if (has_color(input1.get_pixel(x, y)) ^ has_color(input2.get_pixel(x, y))) {
                draw.plot_pen_pixel(x, y);
            }
        }
    }
    return result;
}

/**
 * @param width for target image
 * @param height for target image
 * @param seed for noise generation
 * @return an image suitable for use as keystream
 */
bitmap_image genkeystream(size_t width, size_t height, uint64_t seed = 0) {

    //Instead of RC4, use the default PRNG for simplicity
    std::mt19937 generator(seed);
    std::uniform_int_distribution distribution(0, 1);
    bitmap_image keystream(width, height);

    //Assign each pixel a black or white value, based on PRNG sequence
    for (std::size_t y = 0; y < keystream.height(); ++y) {
        for (std::size_t x = 0; x < keystream.width(); ++x) {
            image_drawer draw(keystream);
            draw.pen_width(1);
            draw.pen_color(255, 255, 255);
            if (distribution(generator) == 0) {
                draw.plot_pen_pixel(x, y);
            }
        }
    }

    std::string file;
    printf("Enter keystream output-file:\n");
    std::cin >> file;

    keystream.save_image(file);

    return keystream;
}

bitmap_image xorcipherguess(const bitmap_image &keystream) {

    printf("Enter reusedkeyexploit input-file:\n");

    std::string file;
    std::cin >> file;

    bitmap_image reusedkeyattack(file);

    printf("Enter guessattack input-file:\n");
    std::cin >> file;

    bitmap_image guesstext(file);

    bitmap_image guessattack = ixor(reusedkeyattack, guesstext);

    printf("Enter guessattack output-file:\n");
    std::cin >> file;

    guessattack.save_image(file);

    return guessattack;
}

bitmap_image xorcipher(const bitmap_image &keystream) {

    printf("Enter ciphertext input-file (1):\n");

    std::string file;
    std::cin >> file;

    bitmap_image ciphertext1(file);

    printf("Enter ciphertext input-file (2):\n");
    std::cin >> file;

    bitmap_image ciphertext2(file);

    bitmap_image xorciphertext = ixor(ciphertext1, ciphertext2);

    printf("Enter xorciphertext output-file:\n");
    std::cin >> file;

    xorciphertext.save_image(file);

    return xorciphertext;
}

bitmap_image encrypt(const bitmap_image &keystream) {

    printf("Enter plaintext input-file:\n");

    std::string file;
    std::cin >> file;

    bitmap_image plaintext(file);

    if (!plaintext) {
        printf("Error - Failed to open %s\n", file.c_str());
        exit(1);
    }

    bitmap_image result = ixor(plaintext, keystream);

    printf("Enter ciphertext output-file:\n");
    std::cin >> file;

    result.save_image(file);

    return result;
}

bitmap_image decrypt(const bitmap_image &keystream) {
    printf("Enter ciphertext input-file:\n");

    std::string file;
    std::cin >> file;

    bitmap_image ciphertext(file);

    if (!ciphertext) {
        printf("Error - Failed to open %s\n", file.c_str());
        exit(1);
    }

    bitmap_image result = ixor(ciphertext, keystream);

    printf("Enter plaintext output-file:\n");
    std::cin >> file;

    result.save_image(file);

    return result;
}

int main() {
    bitmap_image keystream;
    while (true) {
        if (system("CLS")) system("clear");
        printf("(1) Generate keystream\n");
        printf("(2) Encrypt plaintext\n");
        printf("(3) Decrypt plaintext\n");
        printf("(4) XOR ciphertexts\n");
        printf("(5) XOR cipherguess\n");
        printf("(Other) Exit\n");

        int choice;
        std::cin >> choice;
        if (system("CLS")) system("clear");
        switch (choice) {
            case 1:
                keystream = genkeystream(512, 512);
                break;
            case 2:
                encrypt(keystream);
                break;
            case 3:
                decrypt(keystream);
                break;
            case 4:
                xorcipher(keystream);
                break;
            case 5:
                xorcipherguess(keystream);
                break;
            default:
                exit(0);
                break;
        }
    }

    return 0;
}