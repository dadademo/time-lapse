#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"
#include <vector>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <sstream>

const char *ssid = "nxd";
const char *password = "niexianda123";  //192.168.100.16 laptop

// 定义远程服务器的 URL
const char *server_url = "http://example.com/image_upload";



//CAMERA_MODEL_AI_THINKER类型摄像头的引脚定义
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

static camera_config_t camera_config = {
  .pin_pwdn = PWDN_GPIO_NUM,
  .pin_reset = RESET_GPIO_NUM,
  .pin_xclk = XCLK_GPIO_NUM,
  .pin_sscb_sda = SIOD_GPIO_NUM,
  .pin_sscb_scl = SIOC_GPIO_NUM,

  .pin_d7 = Y9_GPIO_NUM,
  .pin_d6 = Y8_GPIO_NUM,
  .pin_d5 = Y7_GPIO_NUM,
  .pin_d4 = Y6_GPIO_NUM,
  .pin_d3 = Y5_GPIO_NUM,
  .pin_d2 = Y4_GPIO_NUM,
  .pin_d1 = Y3_GPIO_NUM,
  .pin_d0 = Y2_GPIO_NUM,
  .pin_vsync = VSYNC_GPIO_NUM,
  .pin_href = HREF_GPIO_NUM,
  .pin_pclk = PCLK_GPIO_NUM,

  .xclk_freq_hz = 4000000,
  .ledc_timer = LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0,

  .pixel_format = PIXFORMAT_JPEG,
  .frame_size = FRAMESIZE_QSXGA,
  .jpeg_quality = 10,
  .fb_count = 1,
};

// 开启wifi
void wifi_init() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected!");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
}

// 关闭 WiFi
void closeWiFi() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

// 初始化摄像头
esp_err_t camera_init() {
  //initialize the camera
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.println("Camera Init Failed");
    return err;
  }
  sensor_t *s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV5640_PID) {
    //        s-&gt;set_vflip(s, 1);//flip it back
    //        s-&gt;set_brightness(s, 1);//up the blightness just a bit
    //        s-&gt;set_contrast(s, 1);
  }
  Serial.println("Camera Init OK!");
  return ESP_OK;
}

// 发送图片信息
void sendImg() {
  // 获取图片信息
  camera_fb_t *fb = esp_camera_fb_get();
  if (fb == NULL) {
    printf("Failed to get camera frame buffer\n");
    return;
  }


  char *beginText = "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"file\"; filename=\"img.jpeg\"\r\nContent-Type: image/jpeg\r\n\r\n";
  size_t beginSize = strlen(beginText);

  // 数据的长度
  uint8_t *imgData = fb->buf;
  size_t fb_len = fb->len;

  char *endText = "\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW--\r\n";
  size_t endSize = strlen(endText);

  // 计算总大小，包括空终止符
  size_t sizeAll = beginSize + fb_len + endSize + 1;

  // 分配内存并复制数据
  uint8_t *data = (uint8_t *)malloc(sizeAll);
  memcpy(data, beginText, beginSize);
  memcpy(data + beginSize, imgData, fb_len);
  memcpy(data + beginSize + fb_len, endText, endSize + 1);  // +1 for null terminator

  printf("Size: %zu\n", sizeAll);
  char Length[64];  // 用于存储转换后的字符串
  sprintf(Length, "%zu", sizeAll);

  HTTPClient http;
  http.begin("http://192.168.0.104:4396/upload");  // 指定URL
  http.addHeader("Content-Type", "multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW");
  http.addHeader("Content-Length", Length);

  int http_response_code = http.POST(data, sizeAll);

  if (http_response_code > 0)  // 如果状态码大于0说明请求过程无异常
  {
    if (http_response_code == HTTP_CODE_OK)  // 请求被服务器正常响应，等同于httpCode == 200
    {
      Serial.print("Content-Type = ");
      Serial.println(http.header("Content-Type"));

      Serial.print("Content-Length = ");
      Serial.println(http.header("Content-Length"));
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(http_response_code).c_str());
  }

  http.end();  // 结束当前连接
  free(data);                                                                 
  esp_camera_fb_return(fb);  //这一步在发送完毕后要执行&#xff0c;具体作用还未可知。
}

void setup() {
  Serial.begin(115200);
  wifi_init();
  camera_init();
}

void loop() {
  delay(60*1000);
  Serial.print("获取手机号码");
  sendImg();
}
