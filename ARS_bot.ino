#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "Config.h"
#include "Matrix.h"
#include "HC.h"
#include "Servos.h"

bool awaitingWord = false;
String chat_id;

const unsigned long BOT_MTBS = 1000;
unsigned long bot_lasttime;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

unsigned long lastInteractionTime = 0;
unsigned long lastDelayTime = 0;
const unsigned long delayInterval = 100;

void handleNewMessages(int numNewMessages)
{
    Serial.print("handleNewMessages ");
    Serial.println(numNewMessages);
    
    for (int i = 0; i < numNewMessages; i++)
    {
      lastInteractionTime = millis();
        String chat_id = bot.messages[i].chat_id;
        String text = bot.messages[i].text;
        
        String from_name = bot.messages[i].from_name;
        if (from_name == "")
          from_name = "Guest";

        if (text == "/hi")
        {
          drawHSmile();
          hiServo();
          bot.sendMessage(chat_id, "Приветик!", "");
        }
        if (text == "/heart")
        {
          drawHeart();
          bot.sendMessage(chat_id, "Я тоже тебя люблю <3", "");
        }
        if (text == "/sad")
        {
          drawSSmile();
          bot.sendMessage(chat_id, "Грущу(", "");
        }
        if (text == "/cat")
        {
          drawCat();
          bot.sendMessage(chat_id, "Кошечка отображена", "");
        }
        if (text == "/dog")
        {
          drawDog();
          bot.sendMessage(chat_id, "Собачка отображена", "");
        }
        if (text == "/quest")
        {
          questionMark();
          bot.sendMessage(chat_id, "Вопрос отображен", "");
        }
        if (text == "/ex")
        {
          exclamationMark();
          bot.sendMessage(chat_id, "Восклицание отображено", "");
        }
        if (text == "/time"){
          DisplayTime();
          bot.sendMessage(chat_id, "Время отображено", "");
        }
        
        if (text == "/message") {
          awaitingWord = true;
          bot.sendMessage(chat_id, "Пожалуйста, отправьте слово для отображения. Слово или предложение должны быть на АНГЛИЙСКОМ ЯЗЫКЕ!", "");
        }else if (awaitingWord == true) {
          String wordToDisplay = text;
          ScrollText(wordToDisplay);
          awaitingWord = false;
          bot.sendMessage(chat_id, "Слово отображено на матрице!", "");
        }
        
        if (text == "/help")
        {
          String welcome = "Вот, что я умею!\n";
          welcome += "/hi \n";
          welcome += "/heart \n";
          welcome += "/sad \n";
          welcome += "/message \n";
          welcome += "/cat \n";
          welcome += "/dog \n";
          welcome += "/ex \n";
          welcome += "/quest\n";
          welcome += "/time\n";
          bot.sendMessage(chat_id, welcome, "Markdown");
        }

        if (text == "/start"){
          bot.sendMessage(chat_id, "Привет " + from_name + "! Я твой настольный робот. Готов к работе! Нажмите /help или зайдите в меню", "");
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println();

    configTime(0, 0, "pool.ntp.org");
    secured_client.setTrustAnchors(&cert);
    Serial.print("Connecting to Wifi SSID ");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
    {
        Serial.print(".");
        unsigned long currentAttemptTime = millis();
        while(millis() - currentAttemptTime < 500){
            //
        }
    }

    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect to WiFi within the timeout period.");
    } else {
        Serial.print("\nWiFi connected. IP address: ");
        Serial.println(WiFi.localIP());
    }

    setupMatrix();
    setupDat();
    setupServos();
}

void loop() {
    unsigned long currentMillis = millis();

    if (millis() - lastInteractionTime > 300000) { 
        DisplayTime();
    }

    if (millis() - bot_lasttime > BOT_MTBS) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages) {
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        bot_lasttime = millis();
    }

    if (getDistance() < 30 && getDistance() != 0) {
      twoHand();
    }
   
    if (currentMillis - lastDelayTime >= delayInterval) {
      lastDelayTime = currentMillis;
    }
}