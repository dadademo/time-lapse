const nodemailer = require('nodemailer');

/**
 * 发送邮件
 * @param {*} html  发送的信息支持html
 * @param {*} toEmail  1298175585@qq.com
 * @param {*} title  恭喜发财
 */
function sendMail(path) {
    console.log('准备发送今日好心情qwq')
    let transporter = nodemailer.createTransport({
        host: 'smtp.qq.com',
        port: 465,
        secure: true,
        auth: {
            user: '你的邮箱@qq.com',
            pass: '你的邮箱key'
        }
    });

    let mailOptions = {
        from: '你的邮箱@qq.com',
        to: '你的邮箱@qq.com',
        subject: '视频信息已经到位了',
        html: '<h2>今天的视频信息</h2>',
        attachments: [
            {
                filename: '视频.mp4',
                path
            }
        ]
    };
    transporter.sendMail(mailOptions, (error, info) => {
        if (error) {
            return console.log(error);
        }
        console.log('信息已送达!')
    });
}
module.exports = { sendMail }



