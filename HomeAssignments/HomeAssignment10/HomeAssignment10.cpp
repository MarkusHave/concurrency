/*Home Assignment 10

Take a look at the following program. It specifies pixel data as red, green and blue components, 
creates two images from them and uses *addPixelColors* function to produce a third image.

Modify this program to execute in parallel for the performance gain. Measure and note the gains in your source code.

*/

#include <iostream>
#include <chrono>
#include <future>

using namespace std;

struct Pixel
{
    float red;
    float green;
    float blue;
};


void addPixelColors(const Pixel* image1, const Pixel* image2, Pixel* result, int imageSize)
{
    for (int i = 0; i < imageSize; i++)
    {
        result[i].red = image1[i].red + image2[i].red;
        if (result[i].red > 1.0f)
        {
            result[i].red = 1.0f;
        }

        result[i].green = image1[i].green + image2[i].green;
        if (result[i].green > 1.0f)
        {
            result[i].green = 1.0f;
        }

        result[i].blue = image1[i].blue + image2[i].blue;
        if (result[i].blue > 1.0f)
        {
            result[i].blue = 1.0f;
        }
    }
}


Pixel* createPixels(int imageSize)
{
    Pixel* image = new Pixel[imageSize];
    for (int i = 0; i < imageSize; i++)
    {
        image[i].red = (float(rand()) / float((RAND_MAX)));
        image[i].green = (float(rand()) / float((RAND_MAX)));
        image[i].blue = (float(rand()) / float((RAND_MAX)));
    }
    return image;
}


int main()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    constexpr int imageSize = 4096 * 4096;
    future<Pixel*> futImage1 = async(launch::async, createPixels, imageSize);
    future<Pixel*> futImage2 = async(launch::async, createPixels, imageSize);
    Pixel* result = new Pixel[imageSize];

    Pixel* image2 = futImage2.get();
    Pixel* image1 = futImage1.get();

    addPixelColors(image1, image2, result, imageSize);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" << endl;

    delete[] result;
    delete[] image2;
    delete[] image1;

    return 0;
}

// RESULTS:
// Without concurrency: 6552ms
// With concurrency:    3540ms
