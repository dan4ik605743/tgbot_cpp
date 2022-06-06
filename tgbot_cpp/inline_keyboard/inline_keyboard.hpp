#ifndef INLINE_KEYBOARD_HPP
#define INLINE_KEYBOARD_HPP

#include "course/course.hpp"
#include "tgbot/Bot.h"
#include "tgbot/net/TgLongPoll.h"
#include "tgbot/types/InlineKeyboardButton.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "weather/weather.hpp"

#include <string>
#include <vector>

struct inline_keyboard {
    static void weather_comamnd(
        TgBot::Bot& bot,
        TgBot::TgLongPoll& long_poll,
        TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
        bool& get_weather_city,
        bool& get_weather_with_buttons,
        const std::string& weather_city,
        weather& weather);

    static void course_command(
        TgBot::Bot& bot,
        TgBot::TgLongPoll& long_poll,
        TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
        bool& get_course_valute,
        bool& get_course_with_buttons,
        const std::string& course_valute,
        course& course);

    static void init_keyboard(
        TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
        TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
        TgBot::InlineKeyboardButton::Ptr& button_weather,
        TgBot::InlineKeyboardButton::Ptr& button_course,
        std::vector<TgBot::InlineKeyboardButton::Ptr>& row_weather,
        std::vector<TgBot::InlineKeyboardButton::Ptr>& row_course);

    static void check_input(TgBot::Bot& bot,
                            TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
                            TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
                            bool& get_weather_with_buttons,
                            bool& get_course_with_buttons,
                            weather& weather,
                            course& course);
};

#endif
