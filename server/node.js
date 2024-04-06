const express = require('express');
const multer = require('multer');
const app = express();
const path = require('path');
const fs = require('fs');
var objFunc = require('./merege')   // 目录名/文件名
const email = require('./email');

let counter = 1;
const currentPath = path.join(__dirname, 'uploads');
const files = fs.readdirSync(currentPath);
if (files && files.length) {
  if (files[files.length - 1] && files[files.length - 1].split) {
    counter = Number(files[files.length - 1].split('.')[0])
    counter += 1
  }
}


const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    const uploadPath = path.join('uploads/');
    fs.mkdirSync(uploadPath, { recursive: true });
    cb(null, uploadPath);
  },
  filename: (req, file, cb) => {
    const filename = `${String(counter).padStart(8, '0')}.jpg`;
    counter++;
    cb(null, filename);
  },
});

const upload = multer({ storage: storage });

// 静态文件服务，用于访问uploads目录下的图片
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));

// 新增的路由，用于获取最后一条图片的地址
app.get('/latest-image', (req, res) => {
  const uploadPath = path.join(__dirname, 'uploads');
  const files = fs.readdirSync(uploadPath);

  if (files.length === 0) {
    return res.status(404).send('No images found.');
  }

  const latestFile = files[files.length - 1];
  const imageUrl = `http://${req.hostname}:${req.socket.localPort}/uploads/${latestFile}`;
  res.status(200).json({ imageUrl });
});

app.post('/upload', upload.single('file'), (req, res) => {
  const file = req.file;
  console.log(file);

  if (!file) {
    return res.status(400).send('No file uploaded.');
  }

  console.log(`File saved as ${file.path}`);
  res.status(200).send('File uploaded!');
});

// 新增的路由，用于初始化视频
app.get('/initVideo', (req, res) => {
  objFunc.initVideo().then(videoName => {
    email.sendMail(videoName)
    res.status(200).json({ videoName });
  })
});

app.listen(4396, () => {
  console.log('Server is running on port 4396');
});
