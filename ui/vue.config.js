const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  chainWebpack: (config) => {
    config.externals({
    });
  },
  devServer: {
    proxy: {
      '/sendVideo': {
        // target: 'https://t2.ainfinit.com/',
        // target: 'https://test.ainfinit.com/',
        target: 'http://192.168.0.104:4396/',
        changeOrigin: true, // target是域名的话，需要这个参数，
        secure: true, // 设置支持https协议的代理
        pathRewrite: {
          '^/sendVideo': ''
        }
      },
      '/uploads': {
        // target: 'https://t2.ainfinit.com/',
        // target: 'https://test.ainfinit.com/',
        target: 'http://192.168.0.104:4396/',
        changeOrigin: true, // target是域名的话，需要这个参数，
        secure: true, // 设置支持https协议的代理
        pathRewrite: {
          '^/uploads': ''
        }
      },
    }
  },
})
