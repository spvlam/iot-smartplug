#include "Payload.h"

// Constructor implementation
Payload::Payload(String action) : _action(action) {}

// Member function implementation
Payload Payload::fromJson(const String &jsonString)
{
    DynamicJsonDocument doc(256); // Adjust the size based on your JSON data size
    deserializeJson(doc, jsonString);

    String action = doc["action"];
    return Payload(action);
}

String Payload::getAction() const
{
    return _action;
}
// Implementation for RemotePayload class

// Default constructor
RemotePayload::RemotePayload() : data_(0)
{
}

// Parameterized constructor
RemotePayload::RemotePayload(String dev, int dat) : device_(dev), data_(dat) {}

// Getter and Setter for Device Name
String RemotePayload::getDeviceName() const
{
    return device_;
}

void RemotePayload::setDeviceName(const String &device)
{
    device_ = device;
}

// Getter and Setter for Data
int RemotePayload::getData() const
{
    return data_;
}

void RemotePayload::setData(int data)
{
    data_ = data;
}
String RemotePayload::toJson() const
{
    StaticJsonDocument<256> doc;
    doc["device"] = device_;
    doc["data"] = data_;

    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

RemotePayload RemotePayload::fromJson(const String &jsonString)
{
    DynamicJsonDocument doc(256); // Adjust the size based on your JSON data size
    deserializeJson(doc, jsonString);

    String device = doc["device"];
    int data = doc["data"];

    return RemotePayload(device, data);
}

std::vector<RemotePayload> RemotePayload::fromListJson(const String &jsonString)
{
    std::vector<RemotePayload> result;

    DynamicJsonDocument doc(1024); // Adjust the size as needed
    deserializeJson(doc, jsonString);

    if (doc.containsKey("list") && doc["list"].is<JsonArray>())
    {
        JsonArray array = doc["list"].as<JsonArray>();
        for (JsonVariant value : array)
        {
            if (value.is<JsonObject>())
            {
                RemotePayload payload;
                JsonObject obj = value.as<JsonObject>();

                if (obj.containsKey("device") && obj.containsKey("data"))
                {
                    payload.setDeviceName(obj["device"].as<String>());
                    payload.setData(obj["data"].as<int>());
                    result.push_back(payload);
                }
                // You may want to handle other cases or provide error handling here
            }
        }
    }

    return result; // Add this line to ensure a return statement at the end
}
// ---------------------------------------------------------------------------------------------------------------------------------

// Implementation for TimeSetPayload class

// Default constructor