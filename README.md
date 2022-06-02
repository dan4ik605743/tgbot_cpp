[![Ubuntu](https://github.com/dan4ik605743/tgbot_cpp/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/dan4ik605743/tgbot_cpp/actions/workflows/ubuntu.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/dan4ik605743/tgbot_cpp/badge/master)](https://www.codefactor.io/repository/github/dan4ik605743/tgbot_cpp/overview/master)

# tgbot_cpp

Бот для телеграма написанный на с++ с использованием библиотеки для работы с api телеграма <a href="https://github.com/reo7sp/tgbot-cpp">tgbot-cpp</a>.
Умеет высылать данные о <a href="https://openweathermap.org/">погоде</a> и <a href="https://www.cbr.ru/currency_base/daily/">курса валют</a>.

# Зависимости для сборки
Зависимости для сборки:
* boost(>=1.76) 
* cmake 
* openssl 
* curl 
* zlib 

# Сборка
```
git clone https://github.com/dan4ik605743/tgbot_cpp
cd tgbot_cpp
mkdir build && cd build
cmake ../
cmake --build .
```

# Запуск
При запуске нужно ввести 2 параметра, ключ апи от openweathermap и сам токен бота.
Пример использование:
```
./tgbot -a ~/api.txt -t ~/token.txt
```

Бот запущен, теперь можно им пользоваться.
