#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <map>

namespace notification
{
    template<typename T>
    class NotificationInfo {
    public:
        NotificationInfo(const T& data) : data_(data) {}

        T getData() const {
            return data_;
        }

    private:
        T data_;
    };
    
    template<typename T>
    using NotificationObserver = std::function<void(const NotificationInfo<T>&)>;

    template<typename T>
    using CallbackArray = std::vector<NotificationObserver<T>>;
    
    template<typename T>
    using NotificationObject = std::map<std::string, CallbackArray<T>>;

    template<typename T>
    NotificationObject<T> observers;

    class NotificationCenter
    {
    public:
    // 获取单例实例
    static NotificationCenter& getInstance() {
        static NotificationCenter instance;
        return instance;
    }

    // 添加观察者
    template<typename T>
    void addObserver(const std::string &name, NotificationObserver<T> callback) {
        std::cout<<"addObserver name:"<<name<<std::endl;
        std::lock_guard<std::mutex> lock(mutex_);
        CallbackArray<T> arr = observers<T>[name];
        arr.push_back(callback);
        observers<T>[name] = arr;
    };

    // 发送通知
    template<typename T>
    void postNotification(const std::string &name,const NotificationInfo<T>& notification) {
        std::cout<<"postNotification name:"<<name<<std::endl;
        std::lock_guard<std::mutex> lock(mutex_);
        CallbackArray<T> notificationVec = observers<T>[name];
        
        if (notificationVec.size() > 0) {
            for (auto& observer : notificationVec) {
                if (observer) {
                    observer(notification);
                }
            }
        } else {
            std::cout<<"not find name:"<<name<<std::endl;
        }
    };

private:
    NotificationCenter() {} // 构造函数私有化，防止外部创建对象
    NotificationCenter(const NotificationCenter&) = delete; // 禁止拷贝构造
    NotificationCenter& operator=(const NotificationCenter&) = delete; // 禁止赋值操作

    std::mutex mutex_; // 互斥锁，用于保护观察者列表
};
    
} // namespace notification

#endif //NOTIFICATION_H
