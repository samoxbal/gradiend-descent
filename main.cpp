#include <iostream>
#include <inumreader.h>
#include <fstream>
#include <vector>
#include <cmath>

class Reader: public INumReader {
public:
    Reader() {
        count = 0;
    }
    int count;
    std::vector<std::pair<float, float>> data;
    void readFrom(const std::string& filename) {
        std::ifstream file(filename);
        std::string line, x_str, y_str;
        while(std::getline(file, line) >> x_str >> y_str) {
            count++;
            float x, y;
            x = std::stof(x_str);
            y = std::stof(y_str);
            this->data.push_back({ x, y });
        }
        file.close();
    }
    int getCount() const {
        return this->count;
    }
    std::vector<std::pair<float, float>> getData() {
        return this->data;
    }
    std::pair<float, float> getCoefficients(std::vector<std::pair<float, float>>& points) {
        float k = 100.0f, b = 100.0f;

        float alpha_k = 0.0001;
        float alpha_b = 0.005;
        int N = points.size();
        float err = 1000000.0f;
        float dk = 0.0f;// -- dE/dk
        float db = 0.0f;// -- dE/db
        while (err > 0.05) {
            dk = 0.0f;
            db = 0.0f;
            for (auto& p : points) {
                dk += -p.first * (p.second - (k * p.first + b));
                db += -(p.second - (k * p.first + b));
            }
            dk /= N;
            dk *= 2;
            db /= N;
            db *= 2;

            //cout << dk << ", " << db << endl;

            k = k - alpha_k * dk;
            b = b - alpha_b * db;

            err = 0.0f;
            for (auto& p : points) {
                err += pow(p.second - (p.first * k + b), 2);
            }
            err /= N;
            std::cout << "err: " << err << ", k: " << k << ", b: " << b << std::endl;
        }

        return {k, b};
    }
};

int main()
{
    Reader* reader = new Reader();
    const std::string filename = "/home/admin/gradient_descent/dataset1.txt";
    reader->readFrom(filename);
    auto points = reader->getData();
    reader->getCoefficients(points);
    delete reader;
    return 0;
}
