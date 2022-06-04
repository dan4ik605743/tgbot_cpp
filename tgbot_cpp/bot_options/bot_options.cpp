#include "bot_options/bot_options.hpp"
#include "tgbot/types/BotCommand.h"

#include <boost/locale.hpp>

void bot_options::init_commands(TgBot::Bot& bot) {
    std::vector<TgBot::BotCommand::Ptr> commands;

    TgBot::BotCommand::Ptr cmdArray(new TgBot::BotCommand);
    cmdArray->command = "start";
    cmdArray->description = "Начать общение";
    commands.push_back(cmdArray);

    cmdArray = TgBot::BotCommand::Ptr(new TgBot::BotCommand);
    cmdArray->command = "help";
    cmdArray->description = "Посмотреть что умеет бот";
    commands.push_back(cmdArray);

    cmdArray = TgBot::BotCommand::Ptr(new TgBot::BotCommand);
    cmdArray->command = "weather";
    cmdArray->description = "Посмотреть прогноз погоды";
    commands.push_back(cmdArray);

    cmdArray = TgBot::BotCommand::Ptr(new TgBot::BotCommand);
    cmdArray->command = "course";
    cmdArray->description = "Посмотреть курс валюты";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);

    std::vector<TgBot::BotCommand::Ptr> vectCmd;
    vectCmd = bot.getApi().getMyCommands();

    for (std::vector<TgBot::BotCommand::Ptr>::iterator it = vectCmd.begin();
         it != vectCmd.end(); ++it) {
        printf("cmd: %s -> %s\r", (*it)->command.c_str(),
               (*it)->description.c_str());
    }
}

void bot_options::start_command(TgBot::Bot& bot) {
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Привет! Вызови /help и "
                                 "посмотри что я могу.");
    });
}

void bot_options::help_command(TgBot::Bot& bot) {
    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(
            message->chat->id,
            "Могу показать погоду по твоему городу. Вызови /weather"
            "\nМогу показать курс валюты которую хочешь "
            "Вызови /course");
    });
}

void bot_options::weather_comamnd(TgBot::Bot& bot,
                                  TgBot::TgLongPoll& long_poll,
                                  bool& get_weather_city,
                                  const std::string& weather_city,
                                  weather& weather) {
    bot.getEvents().onCommand("weather", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Введите название города");

        get_weather_city = true;
        long_poll.start();
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
    });
}

void bot_options::course_command(TgBot::Bot& bot,
                                 TgBot::TgLongPoll& long_poll,
                                 bool& get_course_valute,
                                 const std::string& course_valute,
                                 course& course) {
    bot.getEvents().onCommand("course", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Введите валюту.\nНапример: usd");

        get_course_valute = true;
        long_poll.start();
        course.set_valute(course_valute);
        course.refresh();

        if (course.check_valute()) {
            bot.getApi().sendMessage(message->chat->id,
                                     course_valute + ": " +
                                         std::to_string(course.get_course()) +
                                         " ₽");
            get_course_valute = false;
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Введена неверная валюта");
            get_course_valute = false;
        }
    });
}

void bot_options::check_input(TgBot::Bot& bot,
                              bool& get_weather_city,
                              bool& get_course_valute,
                              std::string& weather_city,
                              std::string& course_valute,
                              const std::vector<std::string>& bot_commands) {
    bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
        if (get_weather_city) {
            weather_city = message->text;
            return;
        }

        if (get_course_valute) {
            course_valute = boost::locale::to_upper(message->text);
            return;
        }

        for (const auto& command : bot_commands) {
            if ("/" + command == message->text) {
                return;
            }
        }

        bot.getApi().sendMessage(message->chat->id,
                                 "Не знаю такой команды. Вызови "
                                 "/help и посмотри что я могу.");
    });
}
