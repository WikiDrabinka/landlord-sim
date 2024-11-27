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
        Conversation(std::shared_ptr<tenant::Tenant> messageSender, std::string message, int messageTime);
        void sendMessage(std::string message, int messageTime);
        std::shared_ptr<tenant::Tenant> getSender();
        std::vector<std::string> getMessages();
    };
}
