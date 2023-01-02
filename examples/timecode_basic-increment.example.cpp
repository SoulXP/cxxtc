#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <cstring>
#include "timecode.hpp"
#include "common.hpp"

int main(int argc, char** argv)
{
    constexpr auto arg1 = ArgumentParserBuilder::new_argument("timecode1", "string", "positional");
    constexpr auto arg2 = ArgumentParserBuilder::new_argument("timecode2", "string", "positional");

    constexpr auto config = ArgumentParserBuilder::new_configuration("cxxtc timecode example: increment",
                                                                     "simple toy program that demonstrates incrementing a cxxtc timecode by another timecode.",
                                                                     arg1, arg2);

    constexpr auto parser = ArgumentParserBuilder::new_parser(config);

    try {
        const auto parsed_arguments = parser(argc, argv);
        parsed_arguments.print_usage();
    } catch (const std::exception& error) {
        std::cout << "error: " << error.what() << '\n';
        std::exit(EXIT_FAILURE);
    }

    // cxxtc::timecode tc2 = 0;
    // for (std::size_t i = 0; i < 3601; ++i) {
    //     auto fps = cxxtc::fps::to_unsigned(tc2.fps());
    //     std::cout << "value: " << tc2 << " fps: " << fps << '\n';
    //     tc2 += (100 * fps);
    // }

    return 0;
}
