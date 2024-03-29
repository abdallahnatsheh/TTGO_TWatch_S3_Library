# 1 "C:\\Users\\abdna\\AppData\\Local\\Temp\\tmp6yxujpj6"
#include <Arduino.h>
# 1 "C:/Users/abdna/Desktop/TTGO_TWatch_Library/examples/sensor/BAM423_Temperature/BAM423_Temperature.ino"
# 9 "C:/Users/abdna/Desktop/TTGO_TWatch_Library/examples/sensor/BAM423_Temperature/BAM423_Temperature.ino"
#include <LilyGoLib.h>
#include <LV_Helper.h>

uint32_t lastMillis;
lv_obj_t *label1;
void setup();
void loop();
#line 15 "C:/Users/abdna/Desktop/TTGO_TWatch_Library/examples/sensor/BAM423_Temperature/BAM423_Temperature.ino"
void setup()
{

    Serial.begin(115200);

    watch.begin();

    beginLvglHelper();

    label1 = lv_label_create(lv_scr_act());
    lv_label_set_recolor(label1, true);
    lv_obj_center(label1);
}


void loop()
{
    if (lastMillis < millis()) {
        lastMillis = millis() + 1000;

        float accel_celsius = watch.readAccelTemp();

        float core_celsius = watch.readCoreTemp();
        lv_label_set_text_fmt(label1, "Accel: %.2f°C \nESP32: %.2f°C", accel_celsius, core_celsius);
    }
    lv_task_handler();
    delay(5);
}