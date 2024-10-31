#ifndef KEY_SUMMER_HPP
#define KEY_SUMMER_HPP

#include <utility>
#include <string>

namespace poleleyko
{
    struct KeySummer
    {
    public:
        KeySummer();
        void operator()(const std::pair<int, std::string>& element);
        int getKeySum() const;
        std::string getValueString() const;

    private:
        std::string concatenatedValues;
        int keySum;
    };
}

#endif
