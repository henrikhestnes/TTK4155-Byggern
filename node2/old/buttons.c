#include "buttons.h"
#include "can/can_controller.h"


int buttons_status_recieve(int* status) {
    CAN_MESSAGE status_message;
    if(!(can_receive(&status_message, 0))) {
        if (status_message.id == 3) {
            *status = status_message.data[0];

            return 0;
        }
    }

    return 1;
}