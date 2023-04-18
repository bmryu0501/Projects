<template>
  <div>
    <div class="form-wrapper">
      <div>메뉴 이름: <input v-model="name"></div>
      <div>메뉴 설명: <input v-model="description"></div>
      <input @change="fileChange" type="file">
      <div v-if="$route.params.id">
        <button @click="update">메뉴 수정하기</button>
        <button @click="updateImage">이미지 수정하기</button>
      </div>
      <button v-else @click="create">메뉴 추가하기</button>
    </div>

    <div class="image-wrapper" v-if="file">
      <img width="100%" :src="setURL(file)">
    </div>
  </div>
</template>

<script>
import {api} from "../../utils/api"

export default {
  data() {
    return {
      name:"",
      description: "",
      file: null
    }
  },
  async created() {
    // 수정 모드는 this.$route.params.id가 존재한다.
    if(this.$route.params.id) {
      this.$store.commit("SET_TITLE", "메뉴 수정");
      const result = await api.menus.findOne(this.$route.params.id);
      this.name = result.data[0].name;
      this.description = result.data[0].description;
    } else {
      this.$store.commit("SET_TITLE", "메뉴 추가");
    }
  },
  methods: {
    fileChange(e) {
      console.log(e);
      console.log(e.target.files);
      this.file = e.target.files[0];
    },
    setURL(file) {
      const imageURL = URL.createObjectURL(file);
      return imageURL;
    },
    async create() {
      if(!this.name || !this.description || !this.file) {
        alert("빈 정보를 입력해 주세요!");
        return;
      }

      const result = await api.menus.create(this.name, this.description, this.file);

      // result.data.success가 true인 경우에만 성공적으로 업로드
      if(result.data.success) {
        alert(result.data.message);
        this.$router.push("/admin/menus");
      } else {
        alert(result.data.message);
      }
    },
    async update() {
      // update;
      const result = await api.menus.update(this.$route.params.id, this.name, this.description);
      console.log(result);
      alert(result.data.message);
      this.$router.push(`/admin/menus/${this.$route.params.id}`)
    },

    async updateImage(){
      const result = await api.menus.updateImage(this.$route.params.id,this.file);
      console.log(result);
      alert(result.data.message);
      this.$router.push(`/admin/menus/${this.$route.params.id}`)
    }
  }
}
</script>

<style>
.form-wrapper {
  display: flex;
  flex-direction: column;
  margin-top: 50px;
  border: 1px solid black;
  padding: 20px;
}

.form-wrapper > * {
  margin: 10px;
}

.image-wrapper {
  margin-top: 30px;
}
</style>