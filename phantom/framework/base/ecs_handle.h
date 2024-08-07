/**
 *
 * @file entity.h
 * @author lyall (lyall.liu@gmail.com)
 * @date 2024-08-07
 * @brief
 *
 */
#include <stdint.h>

#include "noncopyable.h"

namespace base {

struct Handle : public NonCopyable
{
    union
    {
        uint64_t uid = 0;
        struct
        {
            unsigned short flg : 12;  // Object type
            uint32_t tid : 20;        // timestamp
            uint32_t sid : 32;        // auto increment id
        };
    };

    Handle()
    {
        static uint32_t auto_increment_id = 0;
        sid                               = auto_increment_id;
    }
};

};  // namespace base
