#include <boost/json/src.hpp>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef TGBOT_ENABLE_INLINE_KEYBOARD
#include "bot/bot.hpp"
#else
#include "bot_inline_keyboard/bot_inline_keyboard.hpp"
#endif

#include "course/course.hpp"
#include "tgbot/tgbot.h"
#include "weather/weather.hpp"

using namespace std;
using namespace TgBot;

vector<string> bot_commands = {"start", "help", "weather", "course"};

int main(int argc, char* argv[]) {
    // Bot setup
    boost::locale::generator gen;
    locale::global(gen(""));

    string bot_token_str;
    string weather_api_str;

    try {
        boost::program_options::options_description desc("Allowed Options");
        boost::program_options::variables_map vm;

        desc.add_options()("help,h", "Get allowed options")(
            "token,t", boost::program_options::value<string>()->required(),
            "Set path to bot_token.txt")(
            "api,a", boost::program_options::value<string>()->required(),
            "Set path to openweathermap_api.txt");

        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << "Usage: tgbot [options...]\n\n" << desc;
            return 1;
        }

        if (vm.count("token")) {
            ifstream bot_token_file(vm["token"].as<string>());
            bot_token_file >> bot_token_str;
        }

        if (vm.count("api")) {
            ifstream weather_api_file(vm["api"].as<string>());
            weather_api_file >> weather_api_str;
        }

        boost::program_options::notify(vm);
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << '\n';
        return 1;
    }

#ifndef TGBOT_ENABLE_INLINE_KEYBOARD
    bot bot(bot_token_str, weather_api_str);
    bot.start();
#else
    bot_inline_keyboard bot(bot_token_str, weather_api_str);
    bot.start();
#endif

    return 0;
}
