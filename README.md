# notification

# Notification Component

A lightweight C++ library for implementing an observer pattern with notifications.

## Installation

Clone the repository and include the `notification.h` header file in your project.

## Usage

When calling the postNotification function, you can pass parameters of any type. Please refer to the usage demo for details.

```cpp
#include "notification.h"

notification::NotificationCenter::getInstance().addObserver<int>("event1", [](const notification::NotificationInfo<int>& notification) {
    // Handle event1 notification
});

notification::NotificationInfo<int> eventData(42);
notification::NotificationCenter::getInstance().postNotification("event1", eventData);
