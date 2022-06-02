#include <tgbot/tgbot.h>
#include <boost/json/src.hpp>
#include <boost/locale.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "course/course.hpp"
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

    weather weather(weather_api_str);
    bool get_weather_city = false;
    string weather_city;

    course course;
    bool get_course_valute = false;
    string course_valute;

    Bot bot(bot_token_str);
    TgLongPoll long_poll(bot);

    // Commands setup
    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmdArray(new BotCommand);
    cmdArray->command = "start";
    cmdArray->description = "Начать общение";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "help";
    cmdArray->description = "Посмотреть что умеет бот";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "weather";
    cmdArray->description = "Посмотреть прогноз погоды";
    commands.push_back(cmdArray);

    cmdArray = BotCommand::Ptr(new BotCommand);
    cmdArray->command = "course";
    cmdArray->description = "Посмотреть курс валюты";
    commands.push_back(cmdArray);

    bot.getApi().setMyCommands(commands);

    vector<BotCommand::Ptr> vectCmd;
    vectCmd = bot.getApi().getMyCommands();

    for (vector<BotCommand::Ptr>::iterator it = vectCmd.begin();
         it != vectCmd.end(); ++it) {
        printf("cmd: %s -> %s\r", (*it)->command.c_str(),
               (*it)->description.c_str());
    }

    // Commands settings
    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Привет! Вызови /help и "
                                 "посмотри что я могу.");
    });

    bot.getEvents().onCommand("help", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(
            message->chat->id,
            "Могу показать погоду по твоему городу. Вызови /weather"
            "\nМогу показать курс валюты которую хочешь "
            "Вызови /course");
    });

    bot.getEvents().onCommand("weather", [&](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Введите название города");

        get_weather_city = true;
        long_poll.start();
        weather.set_city(weather_city);
        weather.refresh();

        if (weather.check_city()) {
            bot.getApi().sendMessage(
                message->chat->id,
                "Погода в городе: " + weather.get_city() + '\n' +
                    weather.get_weath() + "\nтемпература " +
                    to_string(weather.get_temp()) + "°C\nветер " +
                    to_string(weather.get_wind()) + " m/h");
            get_weather_city = false;
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Введен неверный город");
            get_weather_city = false;
        }
    });

    bot.getEvents().onCommand("course", [&](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Введите валюту.\nНапример: usd");

        get_course_valute = true;
        long_poll.start();
        course.set_valute(course_valute);
        course.refresh();

        if (course.check_valute()) {
            bot.getApi().sendMessage(
                message->chat->id,
                course_valute + ": " + to_string(course.get_course()) + " ₽");
            get_course_valute = false;
        } else {
            bot.getApi().sendMessage(message->chat->id,
                                     "Введена неверная валюта");
            get_course_valute = false;
        }
    });

    // Check input
    bot.getEvents().onAnyMessage([&](Message::Ptr message) {
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
