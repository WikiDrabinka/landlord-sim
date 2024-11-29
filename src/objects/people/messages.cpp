#include "../../../headers/objects/people/messages.h"

namespace messages {
    Conversation::Conversation(std::shared_ptr<tenant::Tenant> messageSender, std::string message, int messageTime) {
        sender = messageSender;
        messages.push_back(message);
        read = false;
        time = messageTime;
    }
    void Conversation::sendMessage(std::string message, int messageTime, bool response) {
        messages.push_back(message);
        read = false;
        time = messageTime;
        if (response) {
            responses.push_back(messages.size()-1);
            read = true;
        }
    }
    std::shared_ptr<tenant::Tenant> Conversation::getSender() { return sender; }
    std::vector<std::string> Conversation::getMessages() { return messages; }
}