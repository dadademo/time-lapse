<template>
  <div>
    <div class="temp-ecahrs">
      <img
        :src="currentUrl"
        style="width: 100%; max-height: 50vh; object-fit: contain;transform: rotateX(180deg)"
      />
    </div>
    <!-- <div class="ctrl-item-body">
      <div class="ctrl-item ctrl-item-row">20℃</div>
    </div> -->

    <div class="ctrl-item-body">
      <div class="ctrl-item ctrl-item-row" @click="getLastImgData()">刷新</div>
    </div>
    <div class="ctrl-item-body">
      <div class="ctrl-item ctrl-item-row" @click="getVideoInfo()">
        生成视频
      </div>
    </div>
  </div>
</template>

<script>
import { Slider, Field, Popup, Picker } from "vant";
import { getlastImg, getVideo } from "@/api/fan";
export default {
  name: "homeComp",
  components: {
    [Slider.name]: Slider,
    [Field.name]: Field,
    [Popup.name]: Popup,
    [Picker.name]: Picker,
  },
  data() {
    return {
      currentUrl: "",
    };
  },
  mounted() {
    this.getLastImgData();
    setInterval(() => {
      this.getLastImgData();
    }, 13000);
  },
  methods: {
    getLastImgData() {
      getlastImg().then((res) => {
        const imageUrl = res.imageUrl.split("uploads");

        this.currentUrl = `${window.location.href}/uploads${imageUrl[1]}`;
      });
    },
    getVideoInfo() {
      getVideo().then((res) => {
        console.log(res);
      });
    },
  },
};
</script>

<style scoped>
.temp-ecahrs {
  border-radius: 12px;
  width: calc(100vw - 40px);
  background-color: white;
  height: 50vh;
  margin: 10px auto 0 auto;
  padding: 10px;
}
.ctrl-item-body {
  display: flex;
  flex-wrap: wrap;
  border-radius: 12px;
  width: calc(100vw - 20px);
  background-color: white;
  margin: 10px auto 0 auto;
}
.ctrl-item {
  width: calc(50% - 1px);
  height: 12vh;
  font-size: 20px;
  text-align: center;
  line-height: 12vh;
}
.input-style {
  border: 0px solid black;
  width: 150px;
  height: 100%;
  text-align: center;
  font-size: 40px;
  padding: 0;
  margin: 0;
  border-radius: 12px;
}
.ctrl-item:not(:last-child) {
  border-right: 1px solid #d7dae2;
}
.ctrl-item-row {
  flex: 1;
}
.item-slider {
  width: 40vw;
  margin: 0 auto;
}
.temp-ecahrs-info {
  height: calc(50vh - 50px);
}
</style>