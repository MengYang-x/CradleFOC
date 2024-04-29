//
// Created by User on 2024/4/29.
//

#ifndef CRADLEFOC_USERMAIN_H
#define CRADLEFOC_USERMAIN_H

#ifdef __cplusplus
extern "C" {
#endif
/**********包含C的H文件**************/
#include "Serial.h"

/**********C++文件中的函数声明**************/
void setup();
void loop();

#ifdef __cplusplus
}
/**********包含C++的H文件**************/
#include "MT6701.h"
#endif

#endif //CRADLEFOC_USERMAIN_H
