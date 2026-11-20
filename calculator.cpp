#include <cmath>
#include <complex>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string_view>

#include "command.hpp"
#include "repl.hpp"

namespace repl
{
namespace calculator
{

class Multiply : public repl::BaseCommand<Multiply, float, float, float>
{
public:
    const std::string_view longName = "multiply";
    const std::string_view shortName = "mul";
    Multiply() = default;
    float operator()(const float lhs, const float rhs) const
    {
        return lhs * rhs;
    }
};

class SquareRoot : public repl::BaseCommand<SquareRoot, float, float>
{
public:
    const std::string_view longName = "squareroot";
    const std::string_view shortName = "sqrt";
    SquareRoot() = default;
    float operator()(const float number) const
    {
        return std::sqrt(number);
    }
};

class ComplexAdd : public repl::BaseCommand<ComplexAdd, std::complex<float>, std::complex<float>, std::complex<float>>
{
public:
    const std::string_view longName = "ca";
    const std::string_view shortName = "cadd";
    ComplexAdd() = default;
    std::complex<float> operator()(const std::complex<float>& lhs, const std::complex<float>& rhs)
    {
        return lhs + rhs;
    }
};

class ComplexMul : public repl::BaseCommand<ComplexAdd, std::complex<float>, std::complex<float>, std::complex<float>>
{
public:
    const std::string_view longName = "cm";
    const std::string_view shortName = "cmul";
    ComplexMul() = default;
    std::complex<float> operator()(const std::complex<float>& lhs, const std::complex<float>& rhs)
    {
        return lhs * rhs;
    }
};

class ComplexAbs : public repl::BaseCommand<ComplexAdd, float, std::complex<float>>
{
public:
    const std::string_view longName = "abs";
    const std::string_view shortName = "cabs";
    ComplexAbs() = default;
    float operator()(const std::complex<float>& cmx)
    {
        return std::hypot(cmx.imag(), cmx.real());
    }
};
// TODO: добавьте команды для работы с комплексными числами

using Repl = ::repl::Repl<Multiply, SquareRoot, ComplexAdd, ComplexMul, ComplexAbs>;

} // namespace calculator
} // namespace repl

int main()
{
    using namespace repl::calculator;

    try
    {
        Repl repl{std::cin, std::cout, "calc"};
        repl.Run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& err)
    {
        std::cerr << "Error: " << err.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Error: unknown\n";
    }
    return EXIT_FAILURE;
}
