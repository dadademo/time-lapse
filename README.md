# time-lapse
esp32-cam延时摄影

### ui可以查看最近一次的上传的图片信息

### server 
1. email是将生成的文件发送到邮箱
2. merege将本地的uploads文件下所有的文件生成视频
3. node 主入口，承接图片接收存储，和一下指令的接口（api）

#### sketch_nov19a 是esp32-cam拍照发送图片的代码
> 因为这个网卡不太好，就没搞长连接，用的http方式发送的

ps 这个自己看看就行，如果遇到了问题，可以加qq：1298175585，或者邮件：1298175585@qq.com

效果：https://www.cnblogs.com/niexianda/p/18059452 
![be96e8c05e25acea709fc86ede2edb8](https://github.com/dadademo/time-lapse/assets/40522607/c43edd06-1228-41f0-8d9c-bb0b6b0c1b92)
