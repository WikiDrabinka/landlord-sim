#pragma once
#include "tenant.h"

namespace messages {
    class Conversation {
        private:
        std::shared_ptr<tenant::Tenant> sender;
        std::vector<std::string> messages;
        public:
        bool read;
        int time;
        std::vector<int> responses;
        Conversation(std::shared_ptr<tenant::Tenant> messageSender, std::string message, int messageTime);
        void sendMessage(std::string message, int messageTime,bool response=false);
        std::shared_ptr<tenant::Tenant> getSender();
        std::vector<std::string> getMessages();
        std::string getTimeStr();
    };
}
