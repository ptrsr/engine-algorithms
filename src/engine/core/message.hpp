#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

class Object;

class Message {
    public:
        virtual void Execute(Object& object) const = 0;

};

#endif //MESSAGE_HPP_
