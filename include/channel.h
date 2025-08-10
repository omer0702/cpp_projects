#pragma once
#include<string>

class Channel{
public:
    virtual ~Channel();
    virtual bool open()=0;
    virtual void close()=0;

    virtual bool write(const std::string& message)=0;
};