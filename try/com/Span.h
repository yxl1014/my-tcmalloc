//
// Created by yxl on 22-11-16.
//

#ifndef MY_TCMALLOC_SPAN_H
#define MY_TCMALLOC_SPAN_H

#include <cstdlib>
#include <cstring>
#include "common.h"
#include "page.h"

namespace MyTCMalloc {
    namespace Common {
        size_t min_page_size = MyTCMalloc::kMinPages;

        class Span {
        public:
            int getPageNum() const;

            void *getStart() const;

            static ClassSizeInfo getPageSize(size_t malloc_size);

            Span() {
                Span(0);
            }

            Span(size_t malloc_size) {
                ClassSizeInfo csi = getPageSize(malloc_size);
                void *start_addr = (void *) malloc(csi.num * min_page_size * 1024);
                memset(start_addr, 0, csi.size);
                for (int i = 0; i < csi.num; ++i) {

                }
            }

        private:
            int page_num;//包含page的个数
            void *start;//page的起始地址

        };
    }
}


#endif //MY_TCMALLOC_SPAN_H
