const { exec } = require('child_process');
const path = require('path');


function initVideo() {
    return new Promise((resolve, reject) => {
        const videoName = `${new Date().getTime()}.mp4`
        // 假设您的图片序列文件在 uploads 文件夹下，命名为 00000001.jpeg、00000002.jpeg 等
        const inputPattern = path.join(__dirname, 'uploads', '%08d.jpg');
        const outputVideo = path.join(__dirname, 'video', videoName);

        // 构建 ffmpeg 命令
        const ffmpegCommand = `ffmpeg -framerate 30 -i ${inputPattern} -c:v libx264 -r 30 -pix_fmt yuv420p ${outputVideo}`;

        // 执行命令
        exec(ffmpegCommand, (error, stdout, stderr) => {
            if (error) {
                console.error(`Error: ${error.message}`);
                return;
            }
            console.log('成功')
            resolve(outputVideo)
        });
    })
}



module.exports = {
    initVideo
}
