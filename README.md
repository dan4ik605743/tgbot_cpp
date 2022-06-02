# tgbot_cpp

Бот для телеграма написанный на с++ с использованием библиотеки для работы с api телеграма <a href="https://github.com/reo7sp/tgbot-cpp">tgbot-cpp</a>.
Умеет высылать данные о <a href="https://openweathermap.org/">погоде</a> и <a href="https://www.cbr.ru/currency_base/daily/">курса валют</a>.

# Использование
Для начало нужно поставить зависимости для сборки в систему.
```
sudo pacman -S boost cmake openssl curl 
```

Затем нужно собрать бота.
```
git clone https://github.com/dan4ik605743/tgbot_cpp
cd tgbot_cpp
mkdir build && cd build
cmake ../
cmake --build .
```
Бот собран, осталось его запустить, при запуске нужно ввести 2 параметра, ключ апи от openweathermap и сам токен бота.
Пример использование:
```
./tgbot -a ~/api.txt -t ~/token.txt
```

Бот запущен, теперь можно им пользоваться.
