#ifndef INUMREADER_H
#define INUMREADER_H

class INumReader {
public:
    virtual void readFrom(const std::string& filename) = 0;
    virtual int getCount() const = 0;
};

#endif // INUMREADER_H
