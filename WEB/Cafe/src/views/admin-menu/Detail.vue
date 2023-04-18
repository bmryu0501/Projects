<template>
  <div>
    <b-card
      v-if="data && data.image_src"
      :title="data.name"
      :img-src="setImage()"
      img-alt="Image"
      img-top
      tag="article"
      class="mb-2 detail-card"
    >
      <b-card-text>
        {{ data.description }}
      </b-card-text>

      <b-button @click="moveRegister" href="#" variant="primary"
        >수정하기</b-button
      >
      <b-button @click="deleteMenu" href="#" variant="danger">삭제</b-button>
      <b-button @click="moveList" href="#" variant="outline-primary"
        >목록</b-button
      >
    </b-card>
  </div>
</template>

<script>
import { api } from "../../utils/api";
export default {
  data() {
    return {
      data: {},
    };
  },
  async created() {
    this.$store.commit("SET_TITLE", "메뉴 조회");
    const result = await api.menus.findOne(this.$route.params.id);
    this.data = result.data[0];
  },

  methods: {
    setImage(){
            return `http://ssafy-web.kro.kr:8080/${this.data.image_src}`
    },


    moveRegister() {
      this.$router.push(`/admin/menus/register/${this.$route.params.id}`);
    },
    async deleteMenu() {
      const confirmResult = confirm("삭제하시겠습니까?");
      if (confirmResult) {
        const result = await api.menus.delete(this.$route.params.id);
        alert(result.data.message);
        this.$router.push("/admin/menus");
      }
    },
    moveList() {
      this.$router.push("/admin/menus");
    },
  },
};



</script>

<style>
</style>