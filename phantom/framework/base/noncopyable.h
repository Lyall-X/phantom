#pragma once

namespace base {

class NonCopyable
{
 protected:
    NonCopyable()  = default;
    ~NonCopyable() = default;

 private:
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&)                 = delete;
    NonCopyable& operator=(NonCopyable&&)      = delete;
};

};  // namespace base