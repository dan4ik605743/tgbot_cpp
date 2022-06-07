#include "inline_keyboard/inline_keyboard.hpp"
#include "tgbot/types/CallbackQuery.h"

namespace inline_keyboard {
void init_keyboard(TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
                   TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
                   TgBot::InlineKeyboardButton::Ptr& button_weather,
                   TgBot::InlineKeyboardButton::Ptr& button_course,
                   std::vector<TgBot::InlineKeyboardButton::Ptr>& row_weather,
                   std::vector<TgBot::InlineKeyboardButton::Ptr>& row_course) {
    button_weather->text = "Красноярск";
    button_weather->callbackData = "krasnoyarsk_weather";
    button_course->text = "USD";
    button_course->callbackData = "usd_valute";

    row_weather.push_back(button_weather);
    row_course.push_back(button_course);

    keyboard_weather->inlineKeyboard.push_back(row_weather);
    keyboard_course->inlineKeyboard.push_back(row_course);
}

void weather_comamnd(TgBot::Bot& bot,
                     TgBot::TgLongPoll& long_poll,
                     TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
                     bool& get_weather_city,
                     bool& get_weather_with_buttons,
                     const std::string& weather_city,
                     weather& weather) {
    bot.getEvents().onCommand("weather", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Введите название города",
                                 false, 0, keyboard_weather, "Markdown");
        get_weather_city = true;
        long_poll.start();
        if (get_weather_with_buttons) {
            get_weather_city = false;
            get_weather_with_buttons = false;
        } else {
            weather.set_city(weather_city);
            weather.refresh();

            if (weather.check_city()) {
                bot.getApi().sendMessage(
                    message->chat->id,
                    "Погода в городе: " + weather.get_city() + '\n' +
                        weather.get_weather() + "\nтемпература " +
                        std::to_string(weather.get_temp()) + "°C\nветер " +
                        std::to_string(weather.get_wind()) + " m/h");
                get_weather_city = false;
            } else {
                bot.getApi().sendMessage(message->chat->id,
                                         "Введен неверный город");
                get_weather_city = false;
            }
        }
    });
}

void course_command(TgBot::Bot& bot,
                    TgBot::TgLongPoll& long_poll,
                    TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
                    bool& get_course_valute,
                    bool& get_course_with_buttons,
                    const std::string& course_valute,
                    course& course) {
    bot.getEvents().onCommand("course", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Введите валюту.\nНапример: usd", false, 0,
                                 keyboard_course, "Markdown");
        get_course_valute = true;
        long_poll.start();
        if (get_course_with_buttons) {
            get_course_valute = false;
            get_course_with_buttons = false;
        } else {
            course.set_valute(course_valute);
            course.refresh();

            if (course.check_valute()) {
                bot.getApi().sendMessage(
                    message->chat->id, course.get_valute() + ": " +
                                           std::to_string(course.get_course()) +
                                           " ₽");
                get_course_valute = false;
            } else {
                bot.getApi().sendMessage(message->chat->id,
                                         "Введена неверная валюта");
                get_course_valute = false;
            }
        }
    });
}

void check_input(TgBot::Bot& bot,
                 TgBot::InlineKeyboardMarkup::Ptr& keyboard_weather,
                 TgBot::InlineKeyboardMarkup::Ptr& keyboard_course,
                 bool& get_weather_with_buttons,
                 bool& get_course_with_buttons,
                 weather& weather,
                 course& course) {
    bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "krasnoyarsk_weather")) {
            get_weather_with_buttons = true;
            weather.set_city("Красноярск");
            weather.refresh();
            bot.getApi().sendMessage(
                query->message->chat->id,
                "Погода в городе: " + weather.get_city() + '\n' +
                    weather.get_weather() + "\nтемпература " +
                    std::to_string(weather.get_temp()) + "°C\nветер " +
                    std::to_string(weather.get_wind()) + " m/h",
                false, 0, keyboard_weather, "Markdown");
        } else if (StringTools::startsWith(query->data, "usd_valute")) {
            get_course_with_buttons = true;
            course.set_valute("USD");
            course.refresh();
            bot.getApi().sendMessage(
                query->message->chat->id,
                "USD : " + std::to_string(course.get_course()) + " ₽", false,
                0, keyboard_course, "Markdown");
        }
    });
}
}  // namespace inline_keyboard
