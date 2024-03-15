# notification

# Notification Component

A lightweight C++ library for implementing an observer pattern with notifications.

## Installation

Clone the repository and include the `notification.h` header file in your project.

```cpp
#include "notification.h"

notification::NotificationCenter::getInstance().addObserver<int>("event1", [](const notification::NotificationInfo<int>& notification) {
    // Handle event1 notification
});

notification::NotificationInfo<int> eventData(42);
notification::NotificationCenter::getInstance().postNotification("event1", eventData);
