#include "slider.h"
#include "can/can_controller.h"


int slider_pos_recieve(slider_t* slider_pos) {
    CAN_MESSAGE slider_message;
    if (!(can_receive(&slider_message, 0))) {
        if (slider_message.id == 2) {
            slider_pos->left = slider_message.data[0];
            slider_pos->right = slider_message.data[1];

            return 0;
        }
    }
    return 1;
}