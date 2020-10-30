#include "slider.h"
#include "can/can_controller.h"


int slider_pos_recieve(slider_t* slider_pos){
  CAN_MESSAGE slider_message;
  if(!(can_recieve(&slider_message, 0))){
    if(slider_message.id == 2){
      slider_pos->left = slider_scale_value(slider_message.data[0], LEFT_OFFSET, MAX_VALUE);
      slider_pos->right = slider_scale_value(slider_message.data[1], RIGHT_OFFSET, MAX_VALUE);

      return 0;
    }
  }
  return 1;
}


int slider_send_to_can(){
  slider_t slider_pos = slider_pos_read();

  CAN_MESSAGE slider_message = {
    2,
    2,
    {slider_pos.left, slider_pos.right}
  };

  can_tracieve(&slider_message);
}