//
// Created by yxl on 22-11-15.
//

#ifndef MY_TCMALLOC_MY_SPAN_H
#define MY_TCMALLOC_MY_SPAN_H

#include "common.h"

namespace MyTCMalloc {
    namespace Common {
        size_t min_page_size = MyTCMalloc::kMinPages;

        class My_Span {
        public:
            int page_num;//包含page的个数
            void *start;//page的起始地址


        private:
        };
    }
}


#endif //MY_TCMALLOC_MY_SPAN_H
