#ifndef BOT_OPTIONS_HPP
#define BOT_OPTIONS_HPP

#include "course/course.hpp"
#include "tgbot/Bot.h"
#include "tgbot/net/TgLongPoll.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "weather/weather.hpp"

#include <string>

namespace bot_options {
void init_commands(TgBot::Bot& bot);

void start_command(TgBot::Bot& bot);
void help_command(TgBot::Bot& bot);

void weather_comamnd(TgBot::Bot& bot,
                     TgBot::TgLongPoll& long_poll,
                     bool& get_weather_city,
                     const std::string& weather_city,
                     weather& weather);

void course_command(TgBot::Bot& bot,
                    TgBot::TgLongPoll& long_poll,
                    bool& get_course_valute,
                    const std::string& course_valute,
                    course& course);

void check_input(TgBot::Bot& bot,
                 bool& get_weather_city,
                 bool& get_course_valute,
                 std::string& weather_city,
                 std::string& course_valute,
                 const std::vector<std::string>& bot_commands);

void start(TgBot::Bot& bot, TgBot::TgLongPoll& long_poll);
}  // namespace bot_options

#endif
