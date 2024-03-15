#include "notification.h"
#include <vector>

using namespace notification;

struct CustomData
{
    int code;
    std::string msg;
    std::vector<int> dataV;

    CustomData(int n, std::string a, std::vector<int> h) : code(n), msg(a), dataV(h) {}
};

int main() {
    NotificationCenter& center = NotificationCenter::getInstance();

    center.addObserver<std::string>("event1", [](const notification::NotificationInfo<std::string>& notification) {
        std::cout << "Received notification for event1 with data: " << notification.getData() << std::endl;
    });

    center.addObserver<int>("event2", [](const notification::NotificationInfo<int>& notification) {
        std::cout << "Received notification for event1 with data: " << notification.getData() << std::endl;
    });

    center.addObserver<CustomData>("event3", [](const notification::NotificationInfo<CustomData>& notification) {
        std::cout << "Received notification for event1 with data: " << notification.getData().msg << std::endl;
    });

    notification::NotificationInfo<std::string> stringNotification("Hello, NotificationCenter!");
    center.postNotification("event1",stringNotification);

    notification::NotificationInfo<int> intdd(123456);
    center.postNotification("event2",intdd);

    CustomData data(1, "Hello", {2, 3, 4});

    notification::NotificationInfo<CustomData> customData(data);
    center.postNotification("event3",customData);

    return 0;
}
