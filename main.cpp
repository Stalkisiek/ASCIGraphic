#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class Canvas
{
public:
    Canvas(int width, int height) : width(width), height(height)
    {
        pixels.resize(height, std::vector<char>(width, ' '));
    }

    virtual void drawPixel(int x, int y, char symbol) = 0;

    void saveToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    file << pixels[y][x];
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Image saved to " << filename << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

protected:
    int width;
    int height;
    std::vector<std::vector<char>> pixels;
};

class ASCIICanvas : public Canvas
{
public:
    ASCIICanvas(int width, int height) : Canvas(width, height)
    {
        for (int x = 0; x < width; x++)
        {
            drawPixel(x, 0, '=');
            drawPixel(x, height - 1, '=');
        }
        for (int y = 1; y < height - 1; y++)
        {
            drawPixel(0, y, '|');
            drawPixel(width - 1, y, '|');
        }
    }

    void drawPixel(int x, int y, char symbol) override
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            pixels[y][x] = symbol;
        }
    }
};

class Figure
{
public:
    virtual void draw(Canvas &canvas) = 0;
};

class Rectangle : public Figure
{
public:
    Rectangle(int x, int y, int width, int height, char symbol)
        : x(x), y(y), width(width), height(height), symbol(symbol) {}

    void draw(Canvas &canvas) override
    {
        for (int i = y; i < y + height; i++)
        {
            for (int j = x; j < x + width; j++)
            {
                canvas.drawPixel(j, i, symbol);
            }
        }
    }

private:
    int x;
    int y;
    int width;
    int height;
    char symbol;
};

class Circle : public Figure
{
public:
    Circle(int centerX, int centerY, int radius, char symbol)
        : centerX(centerX), centerY(centerY), radius(radius), symbol(symbol) {}

    void draw(Canvas &canvas) override
    {
        for (int i = 0; i <= radius * 2; i++)
        {
            for (int j = 0; j <= radius * 2; j++)
            {
                int dx = j - radius;
                int dy = i - radius;
                if (std::sqrt(dx * dx + dy * dy) <= radius)
                {
                    canvas.drawPixel(centerX + dx, centerY + dy, symbol);
                }
            }
        }
    }

private:
    int centerX;
    int centerY;
    int radius;
    char symbol;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    std::ifstream config(argv[1]);
    if (!config.is_open())
    {
        std::cerr << "Unable to open config file: " << argv[1] << std::endl;
        return 1;
    }

    int canvasWidth, canvasHeight;
    std::string outputFilename, emptySymbol;
    std::vector<Figure *> figures;

    config >> canvasWidth >> canvasHeight >> outputFilename >> emptySymbol;

    std::string figureType;
    while (config >> figureType)
    {
        if (figureType == "Square")
        {
            int x, y, size;
            char symbol;
            config >> x >> y >> size >> symbol;
            figures.push_back(new Rectangle(x, y, size, size, symbol));
        }
        else if (figureType == "Rectangle")
        {
            int x, y, width, height;
            char symbol;
            config >> x >> y >> width >> height >> symbol;
            figures.push_back(new Rectangle(x, y, width, height, symbol));
        }
        else if (figureType == "Circle")
        {
            int centerX, centerY, radius;
            char symbol;
            config >> centerX >> centerY >> radius >> symbol;
            figures.push_back(new Circle(centerX, centerY, radius, symbol));
        }

        config.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    config.close();

    ASCIICanvas canvas(canvasWidth, canvasHeight);

    for (Figure *figure : figures)
    {
        figure->draw(canvas);
    }

    canvas.saveToFile(outputFilename);

    for (Figure *figure : figures)
    {
        delete figure;
    }

    return 0;
}
