#pragma once

#include <algorithm>
#include <complex>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace repl
{

template<class T>
struct ArgParser;

template<>
struct ArgParser<std::complex<float>>
{
    static float parse_float(std::string_view str, std::size_t begin, std::size_t end) {
        return std::stof(std::string(str.substr(begin, end - begin)));
    }

    static std::size_t find_sign(std::string_view str) {
        char pos_sign = '+';
        char neg_sign = '-';
        std::size_t plus_count = std::count(str.begin(), str.end(), pos_sign);
        std::size_t minus_count = std::count(str.begin(), str.end(), neg_sign);
        if (plus_count + minus_count > 1) {
            throw std::invalid_argument("Sign was more than one");
        }
        const char* sign_ptr = str.end();
        if (plus_count) {
            sign_ptr = std::find(str.begin(), str.end(), pos_sign);
        }
        if (minus_count) {
            sign_ptr = std::find(str.begin(), str.end(), neg_sign);
        }
        return sign_ptr - str.begin();
    }

    static std::complex<float> parse(std::string_view str) {
        std::complex<float> out;
        try {
            auto sign = find_sign(str);
            std::size_t i_pos = std::find(str.begin(), str.end(), 'i') - str.begin();
            std::size_t real_begin = 0;
            std::size_t real_end = sign;
            std::size_t imag_begin = sign + 1;
            std::size_t imag_end = i_pos; 
            float real = parse_float(str, real_begin, real_end);
            float imag = 0;
            if(imag_begin < str.size() && imag_end == i_pos) { 
                imag = parse_float(str, imag_begin, imag_end);
            }
            out.real(real);
            out.imag(str[i_pos] == '-' ? -imag : imag);
            return out;
        }
        catch(...)
        {
            std::ostringstream msg{};
            msg << "failed to parse complex from '" << str << '\'';
            throw std::invalid_argument(msg.str());   
        }
    }

    static void set_complex(std::string_view out, const char* del, bool was_min, bool is_real, std::complex<float>& res) {
        if (del = out.end()) {

        }
        auto r_val = std::stof(std::string(out.substr(0, del - out.begin() - 1)));
        auto i_val = std::stof(std::string(out.substr(del - out.begin() + 1, out.size())));
        i_val = was_min ? -i_val : i_val;
        res.real(r_val);
        res.imag(i_val);

    }
};

template<>
struct ArgParser<float>
{
    static float parse(std::string_view str)
    {
        try
        {
            return std::stof(std::string{str});
        }
        catch (const std::invalid_argument& err)
        {
            // std::stof message is kind of stupid,
            // we will replace it
            std::ostringstream msg{};
            msg << "failed to parse float from '" << str << '\'';
            throw std::invalid_argument(msg.str());
        }
        catch (const std::out_of_range& err)
        {
            std::ostringstream msg{};
            msg << "value is out of range for float: '" << str << '\'';
            throw std::out_of_range(msg.str());
        }
    }
};

// TODO: добавьте парсеры

} // namespace repl
