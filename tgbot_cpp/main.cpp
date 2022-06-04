#include <boost/json/src.hpp>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef TGBOT_ENABLE_INLINE_KEYBOARD
#include "inline_keyboard/inline_keyboard.hpp"
#endif

#include "bot_options/bot_options.hpp"
#include "currency/currency.hpp"
#include "tgbot/tgbot.h"
#include "weather/weather.hpp"

using namespace std;
using namespace TgBot;

vector<string> bot_commands = {"start", "help", "weather", "course"};

int main(int argc, char* argv[]) {
    // Bot setup
    boost::locale::generator gen;
    std::locale::global(gen(""));

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

#ifdef TGBOT_ENABLE_INLINE_KEYBOARD
    bool get_weather_with_buttons = false;
    bool get_course_with_buttons = false;
#endif

    weather weather(weather_api_str);
    bool get_weather_city = false;
    string weather_city;

    course course;
    bool get_course_valute = false;
    string course_valute;

    Bot bot(bot_token_str);
    TgLongPoll long_poll(bot);

    // Commands init
    bot_options::init_commands(bot);

    // Inline_keyboard setup
#ifdef TGBOT_ENABLE_INLINE_KEYBOARD
    InlineKeyboardMarkup::Ptr keyboard_weather(new InlineKeyboardMarkup);
    InlineKeyboardMarkup::Ptr keyboard_course(new InlineKeyboardMarkup);
    InlineKeyboardButton::Ptr button_weather(new InlineKeyboardButton);
    InlineKeyboardButton::Ptr button_course(new InlineKeyboardButton);
    vector<InlineKeyboardButton::Ptr> row_weather;
    vector<InlineKeyboardButton::Ptr> row_course;

    inline_keyboard::init_keyboard(keyboard_weather, keyboard_course,
                                   button_weather, button_course, row_weather,
                                   row_course);
#endif

    // Commands setup
    bot_options::start_command(bot);
    bot_options::help_command(bot);

#ifndef TGBOT_ENABLE_INLINE_KEYBOARD
    bot_options::weather_comamnd(bot, long_poll, get_weather_city, weather_city,
                                 weather);
#else
    inline_keyboard::weather_comamnd(bot, long_poll, keyboard_weather,
                                     get_weather_city, get_weather_with_buttons,
                                     weather_city, weather);
#endif

#ifndef TGBOT_ENABLE_INLINE_KEYBOARD
    bot_options::course_command(bot, long_poll, get_course_valute,
                                course_valute, course);
#else
    inline_keyboard::course_command(bot, long_poll, keyboard_course,
                                    get_course_valute, get_course_with_buttons,
                                    course_valute, course);
#endif

    // Check input
#ifdef TGBOT_ENABLE_INLINE_KEYBOARD
    inline_keyboard::check_input(bot, keyboard_weather, keyboard_course,
                                 get_weather_with_buttons,
                                 get_course_with_buttons, weather, course);
#endif
    bot_options::check_input(bot, get_weather_city, get_course_valute,
                             weather_city, course_valute, bot_commands);

    // Start bot
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        while (true) {
            printf("Long poll started\n");
            long_poll.start();
        }
    } catch (TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
